#lang rosette
(output-smt #t)
(define-symbolic b integer?)

(define v
	(if (<= 0 b)
		(if (<= 78 b)
			1
			2
		)
		(if (<= 99 b)
			3
			4
		)
	)
)

