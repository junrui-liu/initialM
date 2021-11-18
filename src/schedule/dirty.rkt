#lang rosette

(require 
  "../utility.rkt")

(provide (prefix-out dirty: (except-out (all-defined-out))))

(struct allocation (map attributes bits num-attr num-dirty attr-ass) #:mutable #:transparent)

(define (alloc k attributes #:manual [assignment #f])
  ; assignment is a vector of lists of attributes
  ; assignment[j] = attributes that are mapped to dirty bit j
  
  (let* (
    [n (length attributes)]
    [attr-ass (for/list ([i (range n)]) (cons (list-ref attributes i) i))]
    [bits (build-vector k (lambda (i) i))]
    [matrix
      (if assignment
        (begin
          (for ([row assignment])
            (printf "assignment*/row: ~a\n" row)
            (for ([attr row])
              (assert (member attr attributes) (format "~a is not an attribute" attr))))
          (build-matrix n k (lambda (i j)
            (let ([j-attrs (list-ref assignment j)]
                  [i-attr (list-ref attributes i)])
                (if (member i-attr j-attrs) 1 0)))))
        ; (build-matrix n k (lambda (i j)
        ;   (vector-ref (vector-ref assignment j) i)
          (build-matrix n k (const* bit*)))])
    (printf "dirty bit matrix: ~a\n" matrix)
    (for ([i (range n)])
      (define row (vector-ref (matrix-rows matrix) i))
      (assert (>= (vector-sum row) 1) (format "attribute ~a has no dirty bit" (list-ref attributes i)))
      (printf "attribute ~a\n" (list-ref attributes i))
      ) ; each attribute should be mapped to exactly one dirty bit
    ; (for ([col (matrix-columns matrix)])
    ;   (assert (<= (vector-sum col) 1))) ; DELETE: each dirty bit should be mapped to at most one attribute
  (allocation matrix attributes bits n k attr-ass)))


(define (concretize model)
  (define (subst value)
    (match value
      [(allocation map attributes bits num-attr num-dirty _)
       (for/list ([attrs (matrix-columns map)])
        (for/list ([i (range num-attr)]
                  #:when (= (evaluate (vector-ref attrs i) model) 1))
         (list-ref attributes i)))]
      [_ (evaluate value model)]))
  subst)

(define (bit-of allocation attribute)
  (define i (index-of (allocation-attributes allocation) attribute))
  (define row (vector-ref allocation i))
  (for/list (
    [j (in-range 0 (vector-length row))]
    #:when (= 1 (vector-ref row j)))
    j))


(define (solve-alloc)
  (let ([model (optimize #:minimize (list (bit*)) #:guarantee #t)])
    ; Extract the solved schedule, a mapping from holes to statements
    (and (sat? model) model)))

(define (allocation->strings a model)
  (define sigma (concretize model))
  (define bit-to-attr (sigma a))
  (match a
    [(allocation map attributes bits num-attr num-dirty _)
      (for/list ([i bits])
        (format " : bit ~a -> ~a"
          i
          (list-ref bit-to-attr i)))]))