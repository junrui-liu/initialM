#lang rosette
(output-smt #t)
(define-symbolic b integer?)
(assert (<= 0 b 1))

(define v
	(cond
		[(<= 0 b)
			(cond
				[(<= 1 b) 1]
				[else 2]
			)
		]
		[else
			(cond
				[(<= 1 b) 3]
				[else 4]
			)
		]
	)
)


