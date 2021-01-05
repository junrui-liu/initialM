#lang rosette

; A symbolic data structure for static scheduling of statements with varying
; static and dynamic contexts.

(require "utility.rkt"
		 rosette/solver/mip/cplex
		 rosette/solver/smt/z3)

(provide rit* bit* permute iter-permuted for*/permuted debug conjoin*
		 ref? deref set-ref! break clear
		 (rename-out [new-ref ref] [solve-trace solve]))

; Activate an ILP solver (IBM CPLEX if available, otherwise Z3 in ILP mode)
; (current-solver
;   (if (cplex-available?) ; FIXME: Rosette encodes for CPLEX very slowly...
; 	  (cplex)
; 	  (z3 #:logic 'QF_LIA)))

(define dependency (make-hasheq))
;(define antidependency (make-hasheq))

; Next available location for a reference.
(define next-location 0)

; List of assumed bit-encoded conditions.
(define path-condition null)

; Generate a fresh binary integer symbol.
(define (bit*)
  (define-symbolic* b boolean?) ;; either true or false 0/1 ILP
  ; (assert (<= 0 b 1))
  b)

; symbol for readys in trees
(define (rit*)
  (define r (ref #f))
  r)

; Symbolic permutation of length at most k
(struct permuted (guards elements) #:transparent)

; Symbolically choose a permutation of length at most k.
(define (permute k elements)
  (let* ([n (length elements)]
		 [matrix (build-matrix k n (const* bit*))])
	(for ([row (matrix-rows matrix)])
	  ; (assert (<= (vector-sum row) 1))
	  ; relax
	  (void)
	) ; each hole can choose at most one statement
	(for ([column (matrix-columns matrix)])
	  ; (assert (<= (vector-sum column) 1))
	  ; relax
	  (void)
	) ; each statement can be used by at most one hole
	(permuted matrix elements)))

; Instantiate a symbolic value (to include a symbolic permutation) according
; to a solved model.
(define (concretize model)
  (define (subst value)
	(match value
	  [(permuted guard-matrix elements)
	   (for/list ([guards (matrix-rows guard-matrix)]
				  #:when #t
				  [guard guards]
				  [element elements]
				  ; #:when (= (evaluate guard model) 1))
				  #:when (evaluate guard model))
		 element)]
	  [(? list?) (map subst value)]
	  [(? vector?) (vector-map subst value)]
	  [(? struct?) (struct-map subst value)]
	  [_ (evaluate value model)]))
  subst)


; Opaque, user-facing reference to a location.
; for tree-fields, the member is "location"
; for tree-readys, the member is "ready" (boolean)
(struct ref (location) #:mutable #:transparent)

; Reset the reference for a fresh, disjoint execution path.
(struct cmd:alloc (ref) #:transparent)

; Abstract read from the reference.
(struct cmd:read (ref) #:transparent)

; Abstract write to the reference.
(struct cmd:write (ref) #:transparent)

; Compose two residual programs in parallel.
(struct cmd:join (left right) #:transparent)

; Assume a guard condition inside a body residual program.
(struct cmd:assume (guard body) #:transparent)

; Log a debugging event, to display in case of failure.
(struct cmd:debug (event) #:transparent)

; [checking only] Abstract read from the reference.
(struct ccmd:read (ref) #:transparent)

; [checking only] Abstract write to the reference.
(struct ccmd:write (ref) #:transparent)

; Reverse block of residualizing program.
(define residue null)

; Quiescence is when the program is in a concrete, sequential state.
(define quiescent? #t)

(define ((residualize do-proc) . args)
  (shadow! ([quiescent? #f]
			[residue null])
  (printf "SHADOW\n")
	(apply do-proc args)
	(reverse residue)))

; Symbolically evaluate the body for each alternative of each position of the
; permutation.
(define (iter-permuted perm do-body)
  ; Evaluate the body for each alternative of the permutation, saving
  ; the resulting residual program frames, duplicating each for each
  ; possible occurrence in a concrete permutation.
  (let ([blocks (map (residualize do-body) (permuted-elements perm))])
	(for ([guards (matrix-rows (permuted-guards perm))])
	  (for ([guard guards]
			[block blocks])
		(push! residue (cmd:assume guard block))))
	(flush-residue!)))

; Handy wrapper around for/permuted
(define-syntax-rule (for*/permuted ([name expr]) body ...)
  (let ([value expr])
	(for ([name value])
	  (if (permuted? name)
		  (iter-permuted name (λ (name) body ...))
		  (begin body ...)))))

; Create an empty reference.
(define (new-ref v)
  (let ([r (ref (void))])
	(push! residue (cmd:alloc r))
	(when v
	  (push! residue (cmd:write r)))
	(flush-residue!)
	r))

(define (deref r)
  (push! residue (ccmd:read r))
  (flush-residue!)
  ; (assert (ref-location r))
  (void))

; TODO: Perhaps use false to "de-initialize" a reference.
(define (set-ref! r v)
  (when v
  	(printf "--> pushing to residue, q is: ~a\n" quiescent?)
  	(push! residue (ccmd:write r))
  	(printf "!! insider: ~a\n" residue)
	; (assert (! (ref-location r)))
	; (set-ref-location! r #t)
	; (assert (ref-location r))
  )
  (flush-residue!)
  (void))

; Log a debugging event, to display in case of failure.
(define (debug event)
  (push! residue (cmd:debug event))
  (flush-residue!))

; Create the conjunction of a list of binary variables.
(define conjoin*
  ; Since Rosette symbolic variables are only distinguishable by `eqv?`, we use
  ; `seteqv` to key the memo table.
  (let ([memo (make-hash)])
	(match-lambda
	  ; [(list) 1]
	  [(list) #t]
	  [(list x) x]
	  [(list x xs ...)
	   (hash-ref! memo
				  (apply seteqv xs)
				  (thunk
				   (let ([y (conjoin* xs)]
						 [w (bit*)]
						 [z (bit*)])
					 ; (assert (<= z x))
					 ; (assert (<= z y))
					 ; (assert (= (+ w z) (+ x y)))
					 (assert (=> z x))
					 (assert (=> z y))
					 ; FIXME: don't know how to translate the last one
					 ; (assert (= (+ w z) (+ x y)))
					 z)))]
	)
  )
)

(define (trace-read! location guard-read [dependency dependency])
  ; (define guard-write (apply + (hash-ref! dependency location null)))
  (define guard-write (apply || (hash-ref! dependency location null)))
  ;;guard-write: Guard where original write is performed
  ;;guard-read: Guard where the current read is performed
	 ; (assert (<= guard-read guard-write) "|- assumption -\\-> dependency"))
	 (assert (=> guard-read guard-write) "|- assumption -\\-> dependency"))

(define (trace-write! location guard [dependency dependency])
  (hash-update! dependency
				location
				(curry cons guard) ;; a write on location depends on all vars in the pre-condition
				null))

(define (trace-exit!)
  (for ([dependent (hash-values dependency)]) ;; reset the symbolic var: 0 or 1
	; (assert (<= 0 (apply + dependent) 1))
	(void)
  )
)

(define ready-history null)

; Rollback after reaching trivially impossible path
(define (rollback exn)
  (printf "<<<<<<rollback>>>>>>\n")
  (let ([phi (conjoin* path-condition)])
	; (assert (= phi 0) "|- !assumption"))) ;; assert that the current path cond is infeasible
	(assert (! phi) "|- !assumption"))
  ; revert all the write changes
  (for ([r ready-history])
  	(set-ref-location! r #f)
  )
  (set! ready-history null)
) ;; assert that the current path cond is infeasible

; Evaluate residual program commands.
(define (evaluate-residue! program [shared-dependency null])
	; (printf "> residue is:\n~a\n" program)
	; (printf "> dependency is:\n~a\n" dependency)
	(for ([command program])
		(match command
			[(cmd:assume guard body)
				(push! path-condition guard)
				(with-handlers ([exn:fail? rollback])
					(evaluate-residue! body shared-dependency)
				)
				(pop! path-condition)
			]
			[(cmd:debug event)
				(displayln event)
			]
			[(cmd:alloc r)
				(set-ref-location! r (++ next-location))
			]
			[(ccmd:read r)
				; (let ([assumption (conjoin* path-condition)])
				; 	(trace-read! location assumption dependency)
				; )
				(printf ">>>>>>>>>> ccmd:read from ~a \n" r)
				(assert (ref-location r))
				; (assert (! (ref-location r)))
				; (assert #f)
				; (void)
			]
			[(ccmd:write r)
				; (let ([assumption (conjoin* path-condition)])
				; 	; (printf ">>> assumption is:\n~a\n" assumption)
				; 	(trace-write! location assumption dependency)
				; 	;; all perform write over each location in the shared memory. Useless?
				; 	;;;  (for-each (curry trace-write! location assumption) shared-dependency)
				; )
				(printf ">>>>>>>>>> ccmd:write to ~a \n" r)
				(printf "      >    residue is:~a\n" residue)
				; (assert (! (ref-location r)))
				(set-ref-location! r #t)
				; (assert (ref-location r))
				(set! ready-history (cons r ready-history))
				; (void)
			]
			[(cmd:write (ref location))
				(printf ">>>>>>>>>> cmd:write\n" )
				(let ([assumption (conjoin* path-condition)])
					; (printf ">>> assumption is:\n~a\n" assumption)
					(trace-write! location assumption dependency)
					;; all perform write over each location in the shared memory. Useless?
					;;;  (for-each (curry trace-write! location assumption) shared-dependency)
				)
			]
		)
	)
	; (printf "> path-condition becomes:\n~a\n" path-condition)
	; (printf "> dependency becomes:\n~a\n" dependency)
)

; Evaluate the accumulated residual program if in a quiescent state
(define (flush-residue!)
	(printf "--> flushing residue, q is: ~a\n" quiescent?)
  (when quiescent?
  	(printf ">> seriously flush starts!\n")
	(evaluate-residue! (reverse residue))
	(set! residue null)))

; Reset the state of symbolic tracing.
(define (break)
	(printf "break0\n")
  (evaluate-residue! (reverse residue))
  (set! residue null)
  (unless quiescent?
	(error 'break "Cannot break trace within nested operation"))
  (trace-exit!)
  (set! dependency (make-hasheq))
  (set! next-location 0)
  (set! ready-history null)
)

(define (clear)
	(printf "clear0\n")
  (set! residue null)
  (set! dependency (make-hasheq))
  (set! next-location 0)
  (set! ready-history null)
  (clear-asserts!))

; After one or more traces, solve for an assignment of each multichoice to an
; appropriately sized list of its alternatives.
(define (solve-trace)
  ; (let ([model (optimize #:minimize (list (bit*)) #:guarantee #t)])
  (let ([model (solve (list (bit*)))])
	; Extract the solved schedule, a mapping from holes to statements
	(and (sat? model) (concretize model))))
