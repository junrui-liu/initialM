#lang rosette
(output-smt #t)
(define-symbolic b boolean?)
(define-symbolic c boolean?)

(define (test)
	(define v
		(cond
			[(&& b c) 99]
			[(&& (! b) c) 88]
			[(&& b (! c)) 77]
			[(&& (! b) (! c)) 66]
			[else 55]
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