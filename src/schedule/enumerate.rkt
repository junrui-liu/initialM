#lang rosette

(require 
  "dirty.rkt"
  "../grammar/syntax.rkt"
  "../utility.rkt"
)

(provide
  instantiate-sketch
  enumerate-sketches
  synthesize-schedules
  wc-counter
)

(define mc-counter 0)
(define (multichoose . xs)
  ; (printf ">> multichoose(~a) from ~a\n" mc-counter xs)
  (define m
    (apply 
      (curry list 'multichoose mc-counter) 
      ; (note) since using rosette's choose*,
      ;        you need to provide options for not evaluating anything
      ;        which is null
      (cons null xs)))
  (set! mc-counter (+ 1 mc-counter))
  ; (printf ">> done multichoose\n")
  m)
(define wc-counter 0)
(define (wcchoose xs)
  (define m
    (list 'wcchoose wc-counter xs))
  (set! wc-counter (+ 1 wc-counter))
  m)
(define rule-counter 0)
(define (clear-rule-counter!)
  (set! rule-counter 0))
(define (get-rule-counter)
  (define i rule-counter)
  (set! rule-counter (+ 1 rule-counter))
  i)

(define (enumerate-commands class #:order [order #f] #:iterator [iterator #f])
  (for/list ([rule (ag:class-rules* class)]
             #:when (eq? (ag:rule-iteration rule) iterator)
             #:when (implies (ag:rule-order rule)
                             (eq? (ag:rule-order rule) order)))
    (ag:eval (ag:rule-attribute rule))))

(define (instantiate-command-sketch class command [order #f] [iterator #f])
  (match command
    [(ag:iter/left child slots)
     (define steps
       (for/list ([slot slots])
         (instantiate-command-sketch class slot 'left child)))
     (ag:iter/left child steps)]
    [(ag:iter/right child slots)
     (define steps
       (for/list ([slot slots])
         (instantiate-command-sketch class slot 'right child)))
     (ag:iter/right child steps)]
    [(ag:when _ slots)
      (define steps
       (for/list ([slot slots])
         (instantiate-command-sketch class slot order iterator)))
      (define bits (dirty:allocation-bits (ag:class-allocation class)))
     (ag:when (wcchoose bits) steps)]
    [(ag:hole)
     (let ([range (enumerate-commands class #:order order #:iterator iterator)])
       (apply multichoose range))]
    [(ag:eval _) command]
    [(ag:recur _) command]))

; Instantiate a traversal sketch for an attribute grammar G, given an
; interpretation of (multi-)choice. Used to denote a traversal sketch as a
; symbolic traversal.
(define (instantiate-traversal-sketch G traversal num-dirty)
  (define visitors
    (for/list ([visitor (ag:traversal-visitors traversal)])
      (define class (ag:visitor-class visitor))
      ; set id for each rule
      (clear-rule-counter!)
      (for ([rule (ag:class-rules* class)])
        (when (not (ag:rule-id rule))
          (ag:set-rule-id! rule (get-rule-counter))))
      (define labels (map ag:label-name (ag:class-labels* class)))
      (printf "class ~a has attributes: ~a\n" (ag:class-name class) labels)
      ; (define assignment (vector
      ;   (vector 1 1 0 0 0 0 0 0 0 0)
      ;   (vector 0 0 1 1 1 1 0 0 1 0)
      ;   (vector 0 0 0 0 0 0 1 1 0 1)
      ; ))
      (define assignment
        '(
          ( ; D0: inputs
            style.padding.left style.padding.right style.padding.top style.padding.bottom
            style.border.left style.border.right style.border.top style.border.bottom
            style.margin.top style.margin.bottom)
          ( ; D1: inherited
            container.x container.y container.width container.height)
          ( ; D2: block 1 dependencies:
            style.width
            underflow
            style.margin.left style.margin.right)
          ( ; D3: block 
            padding.left padding.right
            border.left border.right
            margin.left margin.right
            content_box.x content_box.y content_box.width
            padding_box.x padding_box.y padding_box.width
            border_box.x border_box.y border_box.width
            )
          ( ; D4: block last: height-related
            intrinsic_height style.height
            padding.top padding.bottom
            border.top border.bottom
            margin.top margin.bottom
            content_box.height padding_box.height border_box.height margin_box.height)
          ( ; D5: sink
            margin_box.x margin_box.y margin_box.width
            computedHeight)
        ))
      (ag:set-class-allocation! class (dirty:alloc num-dirty labels #:manual assignment))
      ; (ag:set-class-allocation! class (dirty:alloc num-dirty labels))
      (ag:visitor (ag:visitor-class visitor)
                  (map (curry instantiate-command-sketch class)
                       (ag:visitor-commands visitor)))))
  (for ([visitor (ag:traversal-visitors traversal)])
      (define class (ag:visitor-class visitor))
      (ag:set-class-dependency-matrix! class (compute-dependency-matrix class)))

  (ag:traversal (ag:traversal-name traversal) visitors))


(define (compute-dependency-matrix class)
  (define rules (ag:class-rules* class))
  (define a (ag:class-allocation class))
  (define num-attributes (dirty:allocation-num-attr a))
  (define attr-ass (dirty:allocation-attr-ass a))
  (define m
    (build-matrix (length rules) num-attributes
      (const* (lambda () #f))))
  (for ([i (range (length rules))])
    (define rule (list-ref rules i))
    (for ([attr (ag:term-rhs (ag:rule-formula rule))])
      (define j (cdr (assoc attr attr-ass)))
      ; (printf "rule: ~a attr: ~a (~a)\n" rule attr j)
      (matrix-set! m i j #t)))
  (printf "~a\n" m)
  m)
  

; Instantiate a schedule sketch for an attribute grammar G, given an
; interpretation of (multi-)choice. Used to denote a schedule sketch as a
; symbolc schedule.
(define (instantiate-sketch G sketch num-dirty)
  (match sketch
    ;;; [(ag:sequential left-sched right-sched)
    ;;;  (ag:sequential (instantiate-sketch G left-sched)
    ;;;                 (instantiate-sketch G right-sched))]
    ;;; [(ag:parallel left-sched right-sched)
    ;;;  (ag:parallel (instantiate-sketch G left-sched)
    ;;;               (instantiate-sketch G right-sched))]
    [(ag:traverse order)
     (instantiate-traversal-sketch G (ag:grammar-ref/traversal G order) num-dirty)]
    ;;; [(ag:traversal order visitors)
    ;;;  (instantiate-traversal-sketch G sketch)]
     ))

; Enumerate schedule sketches for an attribute grammar G, bounded by the number
; of traversal passes up to n.
(define (enumerate-sketches G n)
  (let ([traversals (ag:grammar-traversals G)])
  (if (= n 1)
      traversals
      (append
       (if (= n 2)
           (for*/list ([left-sched traversals]
                       [right-sched traversals])
             (ag:parallel left-sched right-sched))
           null)
       (for*/list ([left-sched traversals]
                   [right-sched (enumerate-sketches G (- n 1))])
         (ag:sequential left-sched right-sched))))))

(define (synthesize-schedules G examples n synthesizer)
  (for ([sketch (shuffle (enumerate-sketches G n))])
    (printf "\n\n\n--------------------------------\n")
    (displayln sketch)
    (synthesizer G sketch examples)
    (clear-asserts!)))
