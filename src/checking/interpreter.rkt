#lang rosette

; Checking interpreter for language of tree traversal schedules

(require "../utility.rkt"
         "../grammar/syntax.rkt"
         "../grammar/tree.rkt")

(provide emp new upd lkup interpret)

(define (emp)
  null)

(define (new store name)
  (cons (cons name (box #f)) store))

(define (upd store name)
  (let ([ref (lookup store name)])
    (assert (not (unbox ref)))
    (set-box! ref #t)))

(define (lkup store name)
  (assert (unbox (lookup store name))))

(define (interpret schedule tree)
  (match schedule
    [(ag:sequential left right)
     (interpret left tree)
     (interpret right tree)]
    [(ag:parallel left right)
     (let ([tree (tree-copy tree)])
       (interpret right tree)
       (interpret left tree))
     (interpret left tree)
     (interpret right tree)]
    [(ag:traversal order visitors)
     (traverse visitors tree)]))

(define (traverse  visitors self)
  (for ([stmt (lookup visitors (tree-class self))])
    (match stmt
      [(ag:recur child)
       (let ([subtree (lookup (tree-children self) child)])
         (if (list? subtree)
             (for ([node subtree])
               (traverse visitors node))
             (traverse visitors subtree)))]
      [(ag:iter/left child commands)
         (raise-user-error 'traverse "scheduled iteration is not implemented")]
      [(ag:iter/right child commands)
         (raise-user-error 'traverse "scheduled iteration is not implemented")]

      [_
       (for/all ([stmt stmt])
         (match stmt
           [(ag:skip)
            (void)]
          ;;;  [(ag:call method _)
          ;;;   (match-let ([(ag-method _ inputs outputs)
          ;;;                (get-method G (tree-class self) method)])
          ;;;     (for ([attr inputs])
          ;;;       (tree-bind self lkup attr))
          ;;;     (for ([attr outputs])
          ;;;       (tree-bind self upd attr)))]
        ))])))
