#lang rosette
(output-smt #t)
(define-symbolic a boolean?)
(define-symbolic b boolean?)
(define-symbolic c boolean?)

(define (test)
	(define v
		(cond
			[(&& (! a) (! b) (! c)) 0]
			[(&& (! a) (! b) c) 1]
			[(&& (! a) b (! c)) 2]
			[(&& (! a) b c) 3]
			[(&& a (! b) (! c)) 4]
			[(&& a (! b) c) 5]
			[(&& a b (! c)) 6]
			[(&& a b c) 7]
			[else 99]
		)
	)
	(solve (assert (equal? v 99)))
)

(for ([i (range 10000)])
	(when (equal? 0 (modulo i 100))
		(printf "# testing ~a\n" i)
	)
	(test)
	(clear-asserts!)
)