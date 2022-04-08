#lang rosette

; A symbolic data structure for static scheduling of statements with varying
; static and dynamic contexts.

(require "utility.rkt"
         rosette/solver/mip/cplex
         rosette/solver/smt/z3)

(provide permute iter-permuted for*/permuted debug
         model->subst anew model-eq?
         ref? deref set-ref! break clear
         permuted
         (rename-out [new-ref ref] [solve-trace solve]))

; Activate an ILP solver (IBM CPLEX if available, otherwise Z3 in ILP mode)
(current-solver
  (if (cplex-available?) ; FIXME: Rosette encodes for CPLEX very slowly...
      (cplex)
      (z3 #:logic 'QF_LIA)))

(define dependency (make-hasheq))
;(define antidependency (make-hasheq))

; Next available location for a reference.
(define next-location 0)

; List of assumed bit-encoded conditions.
(define path-condition null)

; List of bits used in permutations
(define pbits null)

; Generate a fresh binary integer symbol.
(define (bit*)
  (define-symbolic* b integer?) ;; either true or false 0/1 ILP
  (assert (<= 0 b 1))
  b)

; Generate a fresh binary integer symbol for permutation.
(define (pbit*)
  (define b (bit*))
  (set! pbits (cons b pbits))
  b)

; Symbolic permutation of length at most k
(define next-permuted-i 0)
(define (next-next-permuted-i)
  (let ([i next-permuted-i])
    (set! next-permuted-i (+ next-permuted-i 1))
    i))
(struct permuted (guards elements i) #:transparent)

; Symbolically choose a permutation of length at most k.
(define (permute k elements)
  (let* ([n (length elements)]
         [matrix (build-matrix k n (const* pbit*))])
    (for ([row (matrix-rows matrix)])
      (assert (<= (vector-sum row) 1))) ; each hole can choose at most one statement
    (for ([column (matrix-columns matrix)])
      (assert (<= (vector-sum column) 1))) ; each statement can be used by at most one hole
    (permuted matrix elements (next-next-permuted-i))))

; Instantiate a symbolic value (to include a symbolic permutation) according
; to a solved model.
(define (model->subst model)
  (define (subst value)
    (match value
      [(permuted guard-matrix elements i)
       (for/list ([guards (matrix-rows guard-matrix)]
                  #:when #t
                  [guard guards]
                  [element elements]
                  #:when (= (evaluate guard model) 1))
          ; (printf "~a -> ~a\n" element i)
         element)]
      [(? list?) (map subst value)]
      [(? vector?) (vector-map subst value)]
      [(? struct?) (struct-map subst value)]
      [_ (evaluate value model)]))
  subst)


; Opaque, user-facing reference to a location.
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

; Reverse block of residualizing program.
(define residue null)

; Quiescence is when the program is in a concrete, sequential state.
(define quiescent? #t)

(define ((residualize do-proc) . args)
  (shadow! ([quiescent? #f]
            [residue null])
    (apply do-proc args)
    (reverse residue)))

; Symbolically evaluate the body for each alternative of each position of the
; permutation.
(define (iter-permuted perm do-body)
  ; Evaluate the body for each alternative of the permutation, saving
  ; the resulting residual program frames, duplicating each for each
  ; possible occurrence in a concrete permutation.
  ; (printf "permuted-elements ~a\n" (permuted-elements perm))
  (let ([blocks (map (residualize do-body) (permuted-elements perm))])
    (for ([guards (matrix-rows (permuted-guards perm))])
    ; (printf "guards ~a\n" guards)
      (for ([guard guards]
            [i-block (enumerate blocks)])
        (match-define (cons i block) i-block)
        ; (printf "~a attr: ~a\tguard: ~a\n" i (list-ref (permuted-elements perm) i) guard)
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
  (push! residue (cmd:read r))
  (flush-residue!)
  (void))

; TODO: Perhaps use false to "de-initialize" a reference.
(define (set-ref! r v)
  (when v
    (push! residue (cmd:write r)))
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
      [(list) 1]
      [(list x) x]
      [(list x xs ...)
       (hash-ref! memo
                  (apply seteqv xs)
                  (thunk
                   (let ([y (conjoin* xs)]
                         [w (bit*)]
                         [z (bit*)])
                     (assert (<= z x))
                     (assert (<= z y))
                     (assert (= (+ w z) (+ x y)))
                     z)))])))

(define (trace-read! location guard-read [dependency dependency])
  (define guard-write (apply + (hash-ref! dependency location null)))
  ;;guard-write: Guard where original write is performed
  ;;guard-read: Guard where the current read is performed
     (assert (<= guard-read guard-write) "|- assumption -\\-> dependency"))

(define (trace-write! location guard [dependency dependency])
  (hash-update! dependency
                location
                (curry cons guard) ;; a write on location depends on all vars in the pre-condition
                null))

(define (trace-exit!)
  (for ([dependent (hash-values dependency)]) ;; reset the symbolic var: 0 or 1
    (assert (<= 0 (apply + dependent) 1)))) 

; Rollback after reaching trivially impossible path
(define (rollback exn)
  (let ([phi (conjoin* path-condition)])
    (assert (= phi 0) "|- !assumption"))) ;; assert that the current path cond is infeasible

; Evaluate residual program commands.
(define (evaluate-residue! program [shared-dependency null])
  (for ([command program])
    (match command
      [(cmd:assume guard body)
       (push! path-condition guard)
       (with-handlers ([exn:fail? rollback])
         (evaluate-residue! body shared-dependency))
       (pop! path-condition)]
      [(cmd:debug event)
       (displayln event)]
      [(cmd:alloc r)
       (set-ref-location! r (++ next-location))]
      [(cmd:read (ref location))
       (let ([assumption (conjoin* path-condition)])
         (trace-read! location assumption dependency))]
      [(cmd:write (ref location))
       (let ([assumption (conjoin* path-condition)])
         (trace-write! location assumption dependency)
         )])))

; Evaluate the accumulated residual program if in a quiescent state
(define (flush-residue!)
  (when quiescent?
    (evaluate-residue! (reverse residue))
    (set! residue null)))

; Reset the state of symbolic tracing.
(define (break)
  (evaluate-residue! (reverse residue))
  (set! residue null)
  (unless quiescent?
    (error 'break "Cannot break trace within nested operation"))
  (trace-exit!)
  (set! dependency (make-hasheq))
  (set! next-location 0))

(define (clear)
  (set! residue null)
  (set! dependency (make-hasheq))
  (set! next-location 0)
  (clear-asserts!))

; After one or more traces, solve for an assignment of each multichoice to an
; appropriately sized list of its alternatives.
(define (solve-trace)
  (let ([model (optimize #:minimize (list (bit*)) #:guarantee #t)])
    ; (printf "~a\n" pbits)
    ; Extract the solved schedule, a mapping from holes to statements
    (and (sat? model) model)))

(define (dtrace s x)
  (printf "~a: ~a\n" s x)
  x)


(define (and* xs)
  ; (dtrace "and* input" xs)
  (match xs
    [(cons x xs) (and x (and* xs))]
    [_ #t]))

(define (or* xs)
  ; (dtrace "and* input" xs)
  (match xs
    [(cons x xs) (or x (or* xs))]
    [_ #t]))

(define (anew model)
  (< 0 
    (apply +
    ; the new model isn't m
      (for/list ([b pbits])
        (- 1 (evaluate b model))))))

(define (model-eq? m0 m1)
  (and* (for/list ([b pbits])
    (= (evaluate b m0) (evaluate b m1)))))