#lang rosette
(define slist
	(class object%
		(super-new)
		(init-field
			[v null]
		)
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

(define u (all-combinations-all-permutations (list 1 2)))
(define r (for/list ([i u]) (new slist [v i])))
(define-symbolic ptr integer?)
(define v (list-ref u ptr))
(define q (list-ref r ptr))