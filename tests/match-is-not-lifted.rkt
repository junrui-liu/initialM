#lang rosette
(require rosette/lib/synthax)
(define (mm x)
  (match x
    [(cons 1 a) (printf "> cons1\n")]
    [(cons a b) (printf "> cons\n")]
    [(list a b c) (printf "> list\n")]
  )
)
(define ll (list (cons 1 2) (list 3 4 5)))
(define-symbolic ptr integer?)
(define j0 (list-ref ll ptr))
(define j1 (cons (choose 1 2) 9))