#lang rosette

(require 
  "../grammar/syntax.rkt")

(provide (all-defined-out))

; Currently only support per-interface dirty bit assignment
(define bit-attr (hash
  ; toy-3
  ; 'Tree #(
  ;   (width)
  ;   (height)
  ; )
  ; 'Node #(
  ;   (style.width container.width width)
  ;   (style.height container.height height_acc height)
  ; )))

  ; toy-block
  'Tree #(
    (width)
    (height))
  'LayoutBox #(
    (
    container.x
    content_box.x
    padding_box.x
    border_box.x
    margin_box.x
    container.width
    content_box.width
    padding_box.width
    border_box.width
    margin_box.width
    style.width
    padding.left
    padding.right
    border.left
    border.right
    margin.left
    margin.right
    style.margin.left
    style.margin.right
    style.padding.left
    style.padding.right
    style.border.left
    style.border.right
    underflow)
  (container.y
content_box.y
padding_box.y
border_box.y
margin_box.y
padding.top
padding.bottom
border.top
border.bottom
margin.top
margin.bottom
style.margin.top
style.margin.bottom
style.padding.top
style.padding.bottom
style.border.top
style.border.bottom
margin_acc.top
margin_acc.bottom
container.height
intrinsic_height
content_box.height
padding_box.height
border_box.height
margin_box.height
style.height
computedHeight
margin_acc.top.collapse
margin_acc.bottom.collapse
floatLstIn
floatLstOut))))




  ; toy-2
  ; 'Inner #(
  ;   (ratio pWidth widthRel)
  ;   (widthMode widthAbs width)
  ;   (pFont font))
    ; 'LayoutBox #(
    ;       ( ; D0: inputs
    ;         style.padding.left style.padding.right style.padding.top style.padding.bottom
    ;         style.border.left style.border.right style.border.top style.border.bottom
    ;         style.margin.top style.margin.bottom)
    ;       ( ; D1: inherited
    ;         container.x container.y container.width container.height)
    ;       ( ; D2: block 1 dependencies:
    ;         style.width
    ;         underflow
    ;         style.margin.left style.margin.right)
    ;       ( ; D3: block 
    ;         padding.left padding.right
    ;         border.left border.right
    ;         margin.left margin.right
    ;         content_box.x content_box.y content_box.width
    ;         padding_box.x padding_box.y padding_box.width
    ;         border_box.x border_box.y border_box.width
    ;         )
    ;       ( ; D4: block last: height-related
    ;         intrinsic_height style.height
    ;         padding.top padding.bottom
    ;         border.top border.bottom
    ;         margin.top margin.bottom
    ;         content_box.height padding_box.height border_box.height margin_box.height)
    ;       ( ; D5: sink
    ;         margin_box.x margin_box.y margin_box.width
    ;         computedHeight)
    ;     )))
        ; 'Block #(
        ;   ( ; b0: bottom top
        ;     style.padding.top style.padding.bottom
        ;     ; style.border.top style.border.bottom
        ;     style.margin.top style.margin.bottom)
        ;   ( ; b1: left right
        ;     style.padding.left style.padding.right
        ;     ; style.border.left style.border.right  
        ;     style.margin.left style.margin.right
        ;     ; border.left border.right
        ;     padding.left padding.right)
        ;   ( ; b2: underflow related
        ;     style.width container.width underflow margin.left margin.right)
        ;   ( ; b3: sink
        ;     padding.top padding.bottom
        ;     ; border.top border.bottom
        ;     margin.top margin.bottom
        ;     ))
  

    
(define (rev-bit-attr bit-attr)
  (for/hash ([kv (hash->list bit-attr)])
    (match-define (cons cls bits) kv)
    (values cls
      (for*/hash ([i (in-range (vector-length bits))]
                  [a (vector-ref bits i)])
        (values a i)))))
(define attr-bit (rev-bit-attr bit-attr))


(define (bit-of class attribute)
  (let*
    ([object (car attribute)]
     [field  (cdr attribute)]
     [interface-name (match object
      ['self
       (ag:class-interface-name class)]
      [name
       (ag:child-interface-name (ag:class-ref*/child class name))])])
    (hash-ref (hash-ref attr-bit interface-name) field)))

(define (attr-of class bit)
  (vector-ref (hash-ref bit-attr (ag:class-interface-name class)) bit))
