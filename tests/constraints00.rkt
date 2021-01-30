#lang rosette

(define (test)
	(define-symbolic ptr integer?)
	(define vlist (for/list ([i (range 6)]) i))
	(define v (list-ref vlist ptr))
	(for ([_ (range 2000)])
		(set! v (list-ref vlist v))
	)
	v
)

(define final-v (test))
(printf "# eval done\n")
(solve (assert (equal? final-v 4)))
(printf "# solve done\n")