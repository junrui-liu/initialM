#lang rosette
(output-smt #t)
(define-symbolic b0 boolean?)
(define-symbolic b1 boolean?)

(define-symbolic c0 boolean?)
(define-symbolic c1 boolean?)

(define v0 (&& b0 (! b1)))
(define v1 (&& (! b0) b1))

(define u0 (&& c0 (! c1)))
(define u1 (&& (! c0) c1))

(define p
	(cond
		[v0 
			(cond
				[u0
					(cond
						[v0 1]
						[v1 2]
						[else 3]
					)
				]
				[u1 4]
				[else 5]
			)
		]
		[v1 6]
		[else 7]
	)
)
(define z
	(cond
		[(&& b0 (! b1)) 
			(cond
				[(&& c0 (! c1))
					(cond
						[(&& b0 (! b1)) 1]
						[(&& (! b0) b1) 2]
						[else 3]
					)
				]
				[(&& (! c0) c1) 4]
				[else 5]
			)
		]
		[(&& (! b0) b1) 6]
		[else 7]
	)
)
(define q
	(cond
		[v0 3]
		[v1 4]
		[else 5]
	)
)
(define r
	(cond
		[v0 3]
		[v1 4]
		[else 5]
	)
)

(solve (assert (&& (equal? q 3) (equal? r 3))))