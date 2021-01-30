#lang rosette
(output-smt #t)
(define-symbolic b0 boolean?)
(define-symbolic b1 boolean?)

(define (test0 x y)
	(cond
		[(&& (! x) (! y)) 0]
		[(&& (! x) y) 1]
		[(&& x (! y)) 2]
		[(&& x y) 3]
		[else 100]
	)
)

(define (test1 x y)
	(cond
		[(&& (! x) (! y))
			(cond
				[(&& (! x) (! y)) 0]
				[(&& (! x) y) 1]
				[(&& x (! y)) 2]
				[(&& x y) 3]
				[else 100]
			)
		]
		[(&& (! x) y)
			(cond
				[(&& (! x) (! y)) 0]
				[(&& (! x) y) 1]
				[(&& x (! y)) 2]
				[(&& x y) 3]
				[else 100]
			)
		]
		[(&& x (! y))
			(cond
				[(&& (! x) (! y)) 0]
				[(&& (! x) y) 1]
				[(&& x (! y)) 2]
				[(&& x y) 3]
				[else 100]
			)
		]
		[(&& x y)
			(cond
				[(&& (! x) (! y)) 0]
				[(&& (! x) y) 1]
				[(&& x (! y)) 2]
				[(&& x y) 3]
				[else 100]
			)
		]
		[else
			(cond
				[(&& (! x) (! y)) 0]
				[(&& (! x) y) 1]
				[(&& x (! y)) 2]
				[(&& x y) 3]
				[else 100]
			)
		]
	)
)

