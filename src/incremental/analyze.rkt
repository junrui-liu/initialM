#lang rosette

(require 
  "../grammar/syntax.rkt"
  "../trace.rkt"
  "graph.rkt"
  "dirty.rkt"
  "../utility.rkt")

(provide (prefix-out an: (all-defined-out)))
  ; analyze-schedule
  ; substitute))

(struct analysis (blame cost condition msg non-trivial) #:transparent)

(define substitute (make-parameter #f))

(define/match (analyze-schedule schedule)
  [((ag:traversal _ visitors))
    (map analyze-visitor visitors)])

(define/match (analyze-visitor visitor)
  ; (printf "analyze-visitor\n"))
  [((ag:visitor class commands))
   (printf "analyze-visitor ~a\n" (ag:class-name class))
   (filter (lambda (x) x) (map (curry analyze-command class) commands))])

(define (analyze-command class command)
  (match command
    [(ag:when condition commands)
     (analyze-when class condition (first commands))]
    [_ #f]))

(define (analyze-when class condition commands)
  (match-define (permuted guard elements permuted-i) commands)
  ; (printf "analyze-when ~a\n" permuted-i)
  (let* ([concrete-commands ((substitute) commands)]
        ; attribute dependency graph
        [dep-graph (g:new-graph)]
        ; attribute -> dirty bit dependency (bipartite) graph
        [bit-graph (g:new-graph)]
        ; sinks is a list of attributes that are written to
        [sinks (for/list ([command concrete-commands]) (ag:eval-attribute command))])
    ; construct attribute dependency graph
    (for ([lhs sinks])
      (for ([dep (dependencies class lhs)])
        (g:add-edge dep-graph lhs dep)))
    ; sources is a list of attributes that are read from
    ; but not written to in the current block
    (let ([sources (filter (lambda (a) (= 0 (g:degree/out dep-graph a)))
                           (g:vertices dep-graph))])
      ; construct bipartite graph
      (for ([a sinks]) ; for every attribute a that's written to
        ; find source attribute s that a depends on
        (let ([dep-sources (filter (lambda (a1) (member a1 sources)) (g:dfs dep-graph a))])
          (for ([s dep-sources])
            ; add an edge from a to the dirty bit of s
            (let ([s-bit (bit-of class s)])
              (g:add-edge bit-graph a s-bit)))))
      ; compute approximate cost
      (let* (
        [bit-graphT (g:transpose bit-graph)]
        [s-bits (remove-duplicates (map (curry bit-of class) sources))]
        [cost (begin
          ; (printf "s-bits: ~a\n" s-bits)
          (apply + (for/list ([s-bit s-bits])
            (let* ([ss (attr-of class s-bit)]
                  [non-spurious (filter (lambda (a) (member a sinks)) (g:adjacent bit-graphT s-bit))]
                  [spurious (filter (lambda (a) (not (member a non-spurious))) sinks)])
              ; (printf "bit ~a controls: ~a\n" s-bit ss)
              ; (printf "non-spurious: ~a\n" non-spurious)
              ; (printf "spurious: ~a\n" spurious)
              (length spurious)))))])
      ; (printf "cost: ~a\n" cost)
      ; assert when block is non-empty
      (assert (< 0 (apply +
        (for*/list ([row (matrix-rows guard)] [b row]) b))))
          
      ; compute weakly connected components
      (let* ([bit-graphU (g:directed->undirected bit-graph)]
             [components (map (lambda (c) (filter (lambda (v) (member v sinks)) c)) (g:components bit-graphU))]
             [components-sorted (sort components (lambda (c1 c2) (< (length c1) (length c2))))])
        (printf "components (~a): ~a\n" (length components-sorted) components-sorted)
        (printf "bit-graph: ~a\n" (g:graph-adj bit-graph))
        (if (<= 2 (length components-sorted))
          ; there are at least two components
          (begin
            (let* (
              [min-c (first components-sorted)]
              [min-a (list-ref min-c (random (length min-c)))]
              [min-i (index-of (map (lambda (ev) (ag:eval-attribute ev)) elements) min-a)]
              [min-bits (apply + (vector->list (vector-ref (matrix-columns guard) min-i)))]
              [max-c (last components-sorted)]
              [max-a (list-ref max-c (random (length max-c)))]
              [max-i (index-of (map (lambda (ev) (ag:eval-attribute ev)) elements) max-a)]
              [max-bits (apply + (vector->list (vector-ref (matrix-columns guard) max-i)))])
              ; (printf "distancing ~a from ~a\n" min-i max-i)
              (assert (not (member #f (list min-i max-i))))
              (analysis (<= max-bits (- 1 min-bits)) cost s-bits
                (format "distancing ~a from ~a" min-a max-a)
                #t)
              ))
          (analysis #t cost s-bits "" #f))
        )))))

      ; (printf "dirty bits ~a\n" (vector-ref (hash-ref bit-attr (ag:class-name class)) 0)))
    

(define (dependencies class attribute)
  (let ([rule (ag:class-ref*/rule class attribute)])
    (deps (ag:rule-formula rule))))

(define/match (deps term)
  [((ag:field attribute)) (list attribute)]
  [((ag:expr _ operands)) (append-map deps operands)]
  [((ag:call _ arguments)) (append-map deps arguments)]
  [((ag:ite e1 e2 e3)) (append-map deps (list e1 e2 e3))]
  [(_) (list)])
