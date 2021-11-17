#lang rosette

; A symbolic data structure for static scheduling of statements with varying
; static and dynamic contexts.


(require
	rosette/solver/mip/cplex
	rosette/solver/smt/z3
	rosette/lib/synthax
	rosette/lib/angelic
	"./grammar/syntax.rkt"
	"./grammar/tree.rkt"
	"./utility.rkt"
	"./schedule/dirty.rkt"
	"./schedule/enumerate.rkt"
)
(provide
	interpret
	idict
	wcdict
	wc-sum
)

; Activate an ILP solver (IBM CPLEX if available, otherwise Z3 in ILP mode)
; (current-solver
;   (if (cplex-available?) ; FIXME: Rosette encodes for CPLEX very slowly...
; 	  (cplex)
; 	  (z3 #:logic 'QF_LIA)))

; =============================================
; ======== interpreter and necessities ========
; =============================================
; includes:
;         | interpret
;         | traverse
;         | evaluate

(define idict (make-hash)) ; stores indication matrix
; indication matrix
(define (get-imat nth clist)
	; (printf ">> get-imat gets: ~a\n" clist)
	(if (hash-has-key? idict nth)
		(hash-ref idict nth)
		(let ([n (length clist)])
			(define m
				(for/list ([row (range n)])
					(apply choose* clist)))
			(hash-set! idict nth m)
			(hash-ref idict nth))))

(define wcdict (make-hash))
(define (get-wcmat nth bits)
	(if (hash-has-key? wcdict nth)
		(hash-ref wcdict nth)
		(begin
			(define m
				(list->vector (for/list ([i (range (length bits))])
					(bit*))))
			(hash-set! wcdict nth m)
			(hash-ref wcdict nth))))

(define (wc-sum)
		(for/list ([i (range wc-counter)])
			(vector-sum (get-wcmat i #f))))

(define (list-wrapper p)
	(if (list? p)
		p
		(list p)))

(struct denotation (ops fns ite) #:transparent)

(define (denote-op op xs)
	(void)
	; (apply 
	; 	((denotation-ops concrete-denotation) op) 
	; 	xs
	; )
)

(define (denote-fn fn xs)
	(void))

(define (denote-ite if then else)
	(void))

; returns an associated list:
(define (accumulator self)
	(for/list ([attr (ag:class-counters (tree-class self))])
		; (pending) is it box or slot?
		(cons attr (ag:slot #f))))

(define (interpret schedule tree)
	; (fixme) currently this only supports sequential schedule
	(ex:traverse schedule tree)
)

(define (ex:traverse trav self)
	(define class (tree-class self))
	(define visitor (ag:traversal-ref/visitor trav class))

	(for ([command (ag:visitor-commands visitor)])
		(ex:eval command trav self class)))

(define (ex:eval command trav self class #:curr-wc [wc #f])
	(match command
			[(ag:recur child)
				(define subtree (tree-ref/child self child))
				(if (list? subtree)
					(for ([node subtree])
						(ex:traverse trav node))
					(ex:traverse trav subtree))]
			[(ag:iter/left child commands)
				(iterate self child identity commands trav)
			]
			[(ag:iter/right child commands)
				(iterate self child reverse commands trav)
			]
			[(ag:when (list 'wcchoose nth bits) commands)
				(define wcmat (get-wcmat nth bits))
				(printf "~a\n" wcmat)
				(assert (apply || (map (lambda (b) (< 0 b)) (vector->list wcmat))) "at least one dirty bit in condition")
				(for ([command commands])
					(ex:eval command trav self class #:curr-wc wcmat))
				(void)]
			[(ag:skip)
				(void)]
			[(list 'multichoose nth vs ...)
				; (printf "<traverse> multichoose nth=~a\n" nth)
				; obtain a |vs| * |vs| matrix of boolean symbolic variables
				(define imat (get-imat nth vs))
				(for ([ev imat])
					; for every row, which is every choose, which is one rule or null
					(if (null? ev)
						(void) ; do nothing
						; else this is a rule
						(check-eval ev self class #:curr-wc wc)))]
			[(ag:eval ev) (check-eval command self class #:curr-wc wc)]
			[_ (println-and-exit "# exception/traverse: unknown command ~a\n" command)]))

(define (check-eval ev self class #:curr-wc [wc #f])
	(define ev-attr (ag:eval-attribute ev))
	(define ev-rule (ag:class-ref*/rule class ev-attr))
	(define ev-ready (^tree-select/ready self ev-attr))
	(assert (! (ag:slot-v ev-ready)) "before:write-to")
	(define ev-field (^tree-select/field self ev-attr))
	(define ev-res (evaluate self class (ag:rule-formula ev-rule) #:curr-wc wc))
	(ag:set-slot-v! ev-field ev-res)
	(ag:set-slot-v! ev-ready #t)
	(assert (ag:slot-v ev-ready) "after:write-to"))

(define (iterate self child order commands trav)
	(define class (tree-class self))
	(define state0 (accumulator self))

	(for ([command commands])
		(match command
			[(ag:recur _) (void)]
			[(ag:skip) (void)]
			[(list 'multichoose nth vs ...)
				; (printf "<iterate> multichoose nth=~a\n" nth)
				(define imat (get-imat nth vs))
				(for ([ev imat])
					(if (null? ev)
						(void) ; do nothing
						; else this is a rule
						(begin
							(define ev-attr (ag:eval-attribute ev))
							(define ev-rule (ag:class-ref*/rule class ev-attr))
							(when (ag:rule-folds? ev-rule)
								(ag:set-slot-v! (^ass-ref state0 ev-attr) (evaluate self #f (ag:rule-fold-init ev-rule)))
							)
						)
					)
				)
			]
			[_ (println-and-exit "# exception/iterate: unknown command ~a\n" command)]
		)
	)

	(define state#
		(for/fold ([state- state0]) ([node (order (list-wrapper (tree-ref/child self child)))])
			(define state+ (accumulator self))
			(for ([command commands])
				(match command
					[(ag:recur (== child))
						(ex:traverse trav node)
					]
					[(ag:skip)
						(void)
					]
					[(list 'multichoose nth vs ...)
						; (printf "<state> multichoose nth=~a\n" nth)
						(define imat (get-imat nth vs))
						(for ([ev imat])
							(if (null? ev)
								(void) ; do nothing
								; else this is a rule
								(begin
									(define ev-attr (ag:eval-attribute ev))
									(define ev-rule (ag:class-ref*/rule class ev-attr))
									(define ev-eval
										(curry evaluate self #f #:iterator child #:cursor node #:accumulator state-)
									)
									(if (ag:rule-folds? ev-rule)
										(begin
											(define ev-res (ev-eval (ag:rule-fold-next ev-rule)))
											(ag:set-slot-v! (^ass-ref state+ ev-attr))
										)
										(begin
											(define ev-ready (^tree-select/ready self ev-attr #:iterator child #:cursor node))
											(assert (! (ag:slot-v ev-ready)) "before:write-to")
											(define ev-field (^tree-select/field self ev-attr #:iterator child #:cursor node))
											(define ev-res (ev-eval (ag:rule-formula ev-rule)))
											(ag:set-slot-v! ev-field ev-res)
											(ag:set-slot-v! ev-ready #t)
											(assert (ag:slot-v ev-ready) "after:write-to")
										)
									)
								)
							)
						)
					]
					[_ (println-and-exit "# exception/iterate/state#: unknown command ~a\n" command)]
				)
			)
			state+
		)
	)

	; (for ([(attr value) (^in-ass? state#)])
	(for ([(attr value) state#])
		; (printf "> on4 attr: ~a\n" attr)
		(define ev-ready (^tree-select/ready self attr))
		(assert (! (ag:slot-v ev-ready)) "before:write-to")
		(define ev-field (^tree-select/field self attr))
		(define ev-res (ag:slot-v value))
		(ag:set-slot-v! ev-field ev-res)
		(ag:set-slot-v! ev-ready #t)
		(assert (ag:slot-v ev-ready) "after:write-to")
	)
)



(define (evaluate self class term #:iterator [iter #f] #:cursor [cur #f] #:accumulator [acc #f] #:curr-wc [wc #f])
	(define (recur term)
		(cond
			[(union? term)
				(for/all ([t term])
					(recur t)
				)
			]
			[else
				(match term
					[(ag:const val)
						val
					]
					[(ag:field (cons node fld))
						(define attr (cons node fld))
						(define a (ag:class-allocation class))
						(define m (dirty:allocation-map a))
						(define bits (dirty:allocation-bits a))
						(define attrs (dirty:allocation-attributes a))
						(define attr-ass (dirty:allocation-attr-ass a))
						(define i (^ass-ref attr-ass fld))
						; (printf "field: ~a i-th: ~a\n" fld i)
						(if wc
							(begin
								(for ([k bits])
									; (printf "wc: ~a ~a ~a\n" wc (if wc #t #f) (matrix-ref m i k))
									(assert (=> (< 0 (matrix-ref m i k)) (< 0 (vector-ref wc k))) (format "bit ~a used" k))
									; (print-assert)
									))
							(void))
						(define ev-ready (^tree-select/ready self attr #:iterator iter #:cursor cur))
						(assert (ag:slot-v ev-ready) "before:read-from/field")
						(define ev-field (^tree-select/field self attr #:iterator iter #:cursor cur))
						(ag:slot-v ev-field)
					]
					[(ag:accum attr)
						(ag:slot-v (^ass-ref acc attr))
					]
					[(ag:index/first (cons child field) default)
						(define nodes (tree-ref/child self child))
						(if (null? nodes)
							(recur default)
							(begin
								(define ev-ready (tree-ref/ready (first nodes) field))
								(assert (ag:slot-v ev-ready) "before:read-from/index/first")
								(define ev-field (tree-ref/field (first nodes) field))
								(ag:slot-v ev-field)
							)
						)
					]
					[(ag:index/last (cons child field) default)
						(define nodes (tree-ref/child self child))
						(if (null? nodes)
							(recur default)
							(begin
								(define ev-ready (tree-ref/ready (last nodes) field))
								(assert (ag:slot-v ev-ready) "before:read-from/index/last")
								(define ev-field (tree-ref/field (last nodes) field))
								(ag:slot-v ev-field)
							)
						)
					]
					[(ag:ite if then else)
						; (note) recur happens first, which means both branches should be ready
						; (fixme) if the user introduces redundant branches, the synthesizer will fail
						(denote-ite (recur if) (recur then) (recur else))
					]
					[(ag:expr operator operands)
						(define tmp0 (map recur operands))
						(define tmp1 (denote-op operator tmp0))
						tmp1
					]
					[(ag:call function arguments)
						(denote-fn function (map recur arguments))
					]
					[_ (println-and-exit "# exception/evaluate: unknown term ~a\n" term)]
				)
			]
		)
	)
	(define tmp0 (recur term))
	tmp0
)




