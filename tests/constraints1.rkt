#lang rosette
(output-smt #t)
(define-symbolic b boolean?)
(define-symbolic c boolean?)
(define-symbolic v integer?)

(define (test)
	(assert
		(||
			(&& (equal? v 99) b c)
			(&& (equal? v 88) (! b) c)
			(&& (equal? v 77) b (! c))
			(&& (equal? v 66) (! b) (! c))
			(equal? v 55)
		)
	)
	(solve (assert (equal? v 99)))
)

(for ([i (range 1000)])
	(when (equal? 0 (modulo i 100))
		(printf "# testing ~a\n" i)
	)
	(test)
	(clear-asserts!)
)