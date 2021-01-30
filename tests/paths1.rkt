#lang rosette
(output-smt #t)
(define-symbolic b integer?)
(define-symbolic c integer?)

(define v
	(if (<= 0 b)
		(if (<= 0 c)
			(if (<= 0 b)
				1
				2
			)
			(if (<= 0 b)
				3
				4
			)
		)
		(if (<= 0 c)
			(if (<= 0 b)
				5
				6
			)
			(if (<= 0 b)
				7
				8
			)
		)
	)
)

