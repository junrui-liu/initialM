#lang rosette

; A symbolic data structure for static scheduling of statements with varying
; static and dynamic contexts.

(require
	rosette/solver/mip/cplex
	rosette/solver/smt/z3
	"./grammar/syntax.rkt"
	"./grammar/tree.rkt"
	"./utility.rkt"
)
(provide
	interpret
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
(define cdict (make-hash))
(define (select* nth clist)
	(if (hash-has-key? cdict nth)
		(hash-ref cdict nth)
		(begin
			(define-symbolic* s integer?)
			(hash-set! cdict nth (list-ref clist s))
			(hash-ref cdict nth)
		)
	)
)

(struct denotation (ops fns ite) #:transparent)
; lifted
(define (match-op arg-op)
	(cond
		[(symbol? arg-op)
			(cond
				[(equal? arg-op '+) +]
				[(equal? arg-op '-) -]
				[(equal? arg-op '*) *]
				[(equal? arg-op '/) /]
				[(equal? arg-op '<) <]
				[(equal? arg-op '<=) <=]
				[(equal? arg-op '==) =]
				[(equal? arg-op '>=) >=]
				[(equal? arg-op '>) >]
				[(equal? arg-op '!) not]
				[(equal? arg-op '&&) (λ (e1 e2) (and e1 e2))]
				[(equal? arg-op '\|\|) (λ (e1 e2) (or e1 e2))]
				[else (printf "# exception/match-op: unsupported operator ~a\n" arg-op)]
			)
		]
		[(union? arg-op)
			(for/all ([pp arg-op])
				(match-op pp)
			)
		]
		[else (printf "# exception/match-op: unsupported key ~a\n" arg-op)]
	)
)
; lifted
(define (match-fn arg-fn)
	(cond
		[(symbol? arg-fn)
			(cond
				[(equal? arg-fn 'max) max]
				[(equal? arg-fn 'min) min]
				[else (printf "# exception/match-fn: unsupported operator ~a\n" arg-fn)]
			)
		]
		[(union? arg-fn)
			(for/all ([pp arg-fn])
				(match-fn pp)
			)
		]
		[else (printf "# exception/match-op: unsupported key ~a\n" arg-fn)]
	)
)
(define concrete-denotation
	(denotation 
		match-op
		match-fn
		(λ (e1 e2 e3) (if e1 e2 e3))
	)
)

(define (denote-op op xs)
	(apply 
		((denotation-ops concrete-denotation) op) 
		xs
	)
)

(define (denote-fn fn xs)
	(apply 
		((denotation-fns concrete-denotation) fn)
		xs
	)
)

(define (denote-ite if then else)
	((denotation-ops concrete-denotation) if then else)
)

; returns an associated list:
(define (accumulator self)
	(for/list ([attr (ag:class-counters (tree-class self))])
		; (pending) is it box or slot?
		(cons attr (ag:slot #f))
	)
)

(define (all-combinations-all-permutations mcl)
	(for/fold ([res (list )]) ([v (combinations mcl)])
		; (if (null? v)
		; 	res
		; 	(append res (permutations v))
		; )
		(append res (permutations v))
	)
)

(define (interpret schedule tree)
	; (fixme) currently this only supports sequential schedule
	(traverse schedule tree)
)

(define (traverse trav self)
	(define class (tree-class self))
	(define visitor (ag:traversal-ref/visitor trav class))

	(for ([command (ag:visitor-commands visitor)])
		(match command
			[(ag:recur child)
				(printf "> ag:recur child\n")
				(define subtree (tree-ref/child self child))
				(if (list? subtree)
					(for ([node subtree])
						(traverse trav node)
					)
					(traverse trav subtree)
				)
			]
			[(ag:iter/left child commands)
				(printf "> ag:iter/left child\n")
				(iterate self child identity commands trav)
			]
			[(ag:iter/right child commands)
				(printf "> ag:iter/right child\n")
				(iterate self child reverse commands trav)
			]
			; [(list 'multichoose nth ev)
			; 	; (fixme) initiate a for loop for all-combinations-all-permutations
			; 	(printf "> single choose of ~a\n" command)
			; 	(printf "> yes?0\n")
			; 	(define ev-attr (ag:eval-attribute ev))
			; 	(define ev-rule (ag:class-ref*/rule class ev-attr))
			; 	(define ev-ready (tree-select/ready self ev-attr))
			; 	(printf "> yes?1\n")
			; 	(assert (! (ag:slot-v ev-ready)))
			; 	(define ev-field (tree-select/field self ev-attr))
			; 	(define ev-res (evaluate self (ag:rule-formula ev-rule)))
			; 	(printf "> ev-res is: ~a\n" ev-res)
			; 	(ag:set-slot-v! ev-field ev-res)
			; 	(ag:set-slot-v! ev-ready #t)
			; 	(assert (ag:slot-v ev-ready))
			; 	(printf "> ok!\n")
			; ]
			[(ag:skip)
				(printf "> ag:skip\n")
				(void)
			]
			[(list 'multichoose nth vs ...)
				; (fixme) initiate a for loop for all-combinations-all-permutations
				(printf "> traverse/multichoose of ~a\n" vs)
				(define acap (all-combinations-all-permutations vs))
				(define alist* (select* nth acap))
				; (printf "> alist* is: ~a\n" (pretty-format alist*))
				(printf "> enter\n")
				(for/all ([alist alist*])
					(printf "> now alist is: ~a\n" alist)
					(for ([ev alist])
						; (printf "> yes?0\n")
						(define ev-attr (ag:eval-attribute ev))
						(define ev-rule (ag:class-ref*/rule class ev-attr))
						(define ev-ready (tree-select/ready self ev-attr))
						; (printf "> yes?1\n")
						(assert (! (ag:slot-v ev-ready)))
						(define ev-field (tree-select/field self ev-attr))
						(define ev-res (evaluate self (ag:rule-formula ev-rule)))
						; (printf "> ev-res is: ~a\n" ev-res)
						(ag:set-slot-v! ev-field ev-res)
						(ag:set-slot-v! ev-ready #t)
						(assert (ag:slot-v ev-ready))
						; (printf "> ok!\n")
					)
				)
				(printf "> exit\n")
			]
			[_ (printf "# exception/traverse: unknown command ~a\n" command)]
		)
	)
)

(define (iterate self child order commands trav)
	(printf "> iterate\n")
	(define class (tree-class self))
	(define state0 (accumulator self))

	(for ([command commands])
		(match command
			; [(ag:recur _)
			; 	(void)
			; ]
			[(ag:eval attr)
				(define rule (ag:class-ref*/rule class attr))
				(when (ag:rule-folds? rule)
					(ag:set-slot-v! (ass-ref state0 attr) (evaluate self (ag:rule-fold-init rule)))
				)
			]
			[(ag:skip)
				(void)
			]
			[(list 'multichoose vs ...)
				; (fixme) initiate a for loop for all-combinations-all-permutations
				(printf "> iterate/multichoose of ~a\n" vs)
			]
			[_ (printf "# exception/iterate: unknown command ~a\n" command)]
		)
	)

	(define state#
		(for/fold ([state- state0]) ([node (order (tree-ref/child self child))])
			(define state+ (accumulator self))
			(for ([command commands])
				(match command
					[(ag:recur (== child))
						(traverse trav node)
					]
					[(ag:eval attr)
						(define rule (ag:class-ref*/rule class attr))
						(define eval
							(curry evaluate self #:iterator child #:cursor node #:accumulator state-)
						)
						(if (ag:rule-folds? rule)
							(ag:set-slot-v! (ass-ref state+ attr) (eval (ag:rule-fold-next rule)))
							(ag:set-slot-v! (tree-select/ready self attr #:iterator child #:cursor node) (eval (ag:rule-formula rule)))
						)
					]
					[(ag:skip)
						(void)
					]
					[(list 'multichoose vs ...)
						; (fixme) initiate a for loop for all-combinations-all-permutations
						(printf "> iterate/state#/multichoose of ~a\n" vs)
					]
					[_ (printf "# exception/iterate/state#: unknown command ~a\n" command)]
				)
			)
			state+
		)
	)

	(for ([(attr value) (in-ass? state#)])
		(ag:set-slot-v! (tree-select/ready self attr) (ag:slot-v value))
	)
)

(define (evaluate self term #:iterator [iter #f] #:cursor [cur #f] #:accumulator [acc #f])
	(printf "> evaluate: ~a\n" term)
	(define/match (recur term)
		[((ag:const val))
			val
		]
		[((ag:field attr))
			; (printf "> evaluate/field: ~a\n" term)
			(define ev-ready (tree-select/ready self attr #:iterator iter #:cursor cur))
			(assert (ag:slot-v ev-ready))
			(define ev-field (tree-select/field self attr #:iterator iter #:cursor cur))
			(ag:slot-v ev-field)
		]
		[((ag:accum attr))
			(ag:slot-v (ass-ref acc attr))
		]
		[((ag:index/first (cons child field) default))
			; (printf "> evaluate/index/first: ~a\n" term)
			(define nodes (tree-ref/child self child))
			(if (null? nodes)
				(recur default)
				(begin
					(define ev-ready (tree-ref/ready (first nodes) field))
					(assert (ag:slot-v ev-ready))
					(define ev-field (tree-ref/field (first nodes) field))
					(ag:slot-v ev-field)
				)
			)
		]
		[((ag:index/last (cons child field) default))
			; (printf "> evaluate/index/last: ~a\n" term)
			(define nodes (tree-ref/child self child))
			(if (null? nodes)
				(recur default)
				(begin
					(define ev-ready (tree-ref/ready (last nodes) field))
					(assert (ag:slot-v ev-ready))
					(define ev-field (tree-ref/field (last nodes) field))
					(ag:slot-v ev-field)
				)
			)
		]
		[((ag:ite if then else))
			(denote-ite (recur if) (recur then) (recur else))
		]
		[((ag:expr operator operands))
			(printf "> evaluate/expr: ~a\n" term)
			(define tmp0 (map recur operands))
			(printf "> operator is: ~a\n" (pretty-format operator))
			(printf "> operands (list? ~a) gets: ~a\n" (list? tmp0) (pretty-format tmp0))
			(define tmp1 (denote-op operator tmp0))
			(printf "> expression gets: ~a\n" tmp1)
			tmp1
		]
		[((ag:call function arguments))
			(denote-fn function (map recur arguments))
		]
		[(_) (printf "# exception/evaluate: unknown term ~a\n" term)]
	)
	(define tmp0 (recur term))
	; (printf ">>> evaluate returns: ~a\n" tmp0)
	tmp0
)




