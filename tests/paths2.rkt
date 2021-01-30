#lang rosette
(output-smt #t)
(define-symbolic b integer?)
(assert (<= 0 b 1))

(define v
	(cond
		[(equal? b 0)
			(cond
				[(equal? b 1) 1]
				[else 2]
			)
		]
		[else
			(cond
				[(equal? b 1) 3]
				[else 4]
			)
		]
	)
)


