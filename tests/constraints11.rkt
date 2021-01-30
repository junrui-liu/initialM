#lang rosette

(define zval
	(class object%
		(super-new)
		(init-field
			[v null]
		)
	)
)

(define (zlist-ref arg-list arg-ptr)
	(for/all ([p arg-ptr])
		(list-ref arg-list (get-field v p))
	)
)
(define (zget-v arg-obj)
	(for/all ([p arg-obj])
		(get-field v p)
	)
)

(define (test)
	(define-symbolic ptr integer?)
	(define vlist (for/list ([i (range 6)]) (new zval [v i])))
	(define v (list-ref vlist ptr))
	(for ([_ (range 2000)])
		(set! v (zlist-ref vlist v))
	)
	v
)

(define final-v (test))
(printf "# eval done\n")
(solve (assert (equal? (zget-v final-v) 4)))
(printf "# solve done\n")