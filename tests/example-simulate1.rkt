#lang rosette

;   N0
;  /  \
; N1  N2
(define dd (make-hash))
(hash-set! dd "N0.h" 0) ; Box.h  | self.h := l.h + self.w
(hash-set! dd "N0.w" 1) ; Box.w  | self.w := l.w + r.w
(hash-set! dd "N1.h" 2) ; Leaf.h | self.h := default()
(hash-set! dd "N1.w" 3) ; Leaf.w | self.w := default()
(hash-set! dd "N2.h" 4) ; Leaf.h | self.h := default()
(hash-set! dd "N2.w" 5) ; Leaf.w | self.h := default()
(define rbits (make-vector 6 #f))
(define (location-ref s) (vector-ref rbits (hash-ref dd s)))
(define (location-set! s v) (vector-set! rbits (hash-ref dd s) v))

; Leaf  h w
; step0 0 1
; step1 2 3
(define-symbolic b0 boolean?)
(define-symbolic b1 boolean?)
(define-symbolic b2 boolean?)
(define-symbolic b3 boolean?)

(define (choose-n1-step0 waitlist)
	(cond
		[(&& b0 (! b1))
			(assert (! (location-ref "N1.h")))
			(printf "# n1, step0, h: ~a\n" (pc))
			(location-set! "N1.h" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b0) b1)
			(assert (! (location-ref "N1.w")))
			(printf "# n1, step0, w: ~a\n" (pc))
			(location-set! "N1.w" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b0) (! b1))
			(printf "# n1, step0, none: ~a\n" (pc))
			((car waitlist) (cdr waitlist))
		]
	)
)

(define (choose-n1-step1 waitlist)
	(cond
		[(&& b2 (! b3))
			(assert (! (location-ref "N1.h")))
			(printf "# n1, step1, h: ~a\n" (pc))
			(location-set! "N1.h" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b2) b3)
			(assert (! (location-ref "N1.w")))
			(printf "# n1, step1, w: ~a\n" (pc))
			(location-set! "N1.w" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b2) (! b3))
			(printf "# n1, step1, none: ~a\n" (pc))
			((car waitlist) (cdr waitlist))
		]
	)
)

(define (choose-n2-step0 waitlist)
	(cond
		[(&& b0 (! b1))
			(assert (! (location-ref "N2.h")))
			(printf "# n2, step0, h: ~a\n" (pc))
			(location-set! "N2.h" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b0) b1)
			(assert (! (location-ref "N2.w")))
			(printf "# n2, step0, w: ~a\n" (pc))
			(location-set! "N2.w" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b0) (! b1))
			(printf "# n2, step0, none: ~a\n" (pc))
			((car waitlist) (cdr waitlist))
		]
	)
)

(define (choose-n2-step1 waitlist)
	(cond
		[(&& b2 (! b3))
			(assert (! (location-ref "N2.h")))
			(printf "# n2, step1, h: ~a\n" (pc))
			(location-set! "N2.h" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b2) b3)
			(assert (! (location-ref "N2.w")))
			(printf "# n2, step1, w: ~a\n" (pc))
			(location-set! "N2.w" #t)
			((car waitlist) (cdr waitlist))
		]
		[(&& (! b2) (! b3))
			(printf "# n2, step1, none: ~a\n" (pc))
			((car waitlist) (cdr waitlist))
		]
	)
)

; Box   h w
; step0 4 5
; step1 6 7
(define-symbolic b4 boolean?)
(define-symbolic b5 boolean?)
(define-symbolic b6 boolean?)
(define-symbolic b7 boolean?)

; plain trace unpacking
; choose for N1, step0
(define (choose-n0-step0 waitlist)
	(cond
		[(&& b4 (! b5))
			(assert (location-ref "N1.h"))
			(assert (location-ref "N0.w"))
			(assert (! (location-ref "N0.h")))
			(printf "# n0, step0, h: ~a\n" (pc))
			(location-set! "N0.h" #t)
			(if (null? waitlist)
				(printf "# done\n")
				((car waitlist) (cdr waitlist))
			)
		]
		[(&& (! b4) b5)
			(assert (location-ref "N1.w"))
			(assert (location-ref "N2.w"))
			(assert (! (location-ref "N0.w")))
			(printf "# n0, step0, w: ~a\n" (pc))
			(location-set! "N0.w" #t)
			(if (null? waitlist)
				(printf "# done\n")
				((car waitlist) (cdr waitlist))
			)
		]
		[(&& (! b4) (! b5))
			(printf "# n0, step0, none: ~a\n" (pc))
			(if (null? waitlist)
				(printf "# done\n")
				((car waitlist) (cdr waitlist))
			)
		]
	)
)

(define (choose-n0-step1 waitlist)
	(cond
		[(&& b6 (! b7))
			(assert (location-ref "N1.h"))
			(assert (location-ref "N0.w"))
			(assert (! (location-ref "N0.h")))
			(printf "# n0, step1, h: ~a\n" (pc))
			(location-set! "N0.h" #t)
			(if (null? waitlist)
				(printf "# done\n")
				((car waitlist) (cdr waitlist))
			)
		]
		[(&& (! b6) b7)
			(assert (location-ref "N1.w"))
			(assert (location-ref "N2.w"))
			(assert (! (location-ref "N0.w")))
			(printf "# n0, step1, w: ~a\n" (pc))
			(location-set! "N0.w" #t)
			(if (null? waitlist)
				(printf "# done\n")
				((car waitlist) (cdr waitlist))
			)
		]
		[(&& (! b6) (! b7))
			(printf "# n0, step1, none: ~a\n" (pc))
			(if (null? waitlist)
				(printf "# done\n")
				((car waitlist) (cdr waitlist))
			)
		]
	)
)

(choose-n1-step0
	(list
		choose-n1-step1
		choose-n2-step0
		choose-n2-step1
		choose-n0-step0
		choose-n0-step1
	)
)








