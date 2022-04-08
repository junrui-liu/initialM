#lang rosette
; (provide (prefix-out ag:
;                      (except-out (all-defined-out)

(provide (prefix-out g: (all-defined-out)))
(struct graph (adj adjT) #:transparent)

(define (new-graph)
  (graph (make-hash) (make-hash)))

(define (adj-add-edge adj s d)
  (hash-set! adj s 
    (if (hash-has-key? adj s)
      (let ([s-adj (hash-ref adj s)])
        (if (memq d s-adj) s-adj (cons d s-adj)))
      (list d))))
    
; duplicate edges are ignored
(define (add-edge g s d)
  (adj-add-edge (graph-adj g) s d)
  (adj-add-edge (graph-adjT g) d s))

(struct undirected-graph (adj) #:transparent)

(define (vertices g)
  (remove-duplicates (append
    (hash-keys (graph-adj g))
    (hash-keys (graph-adjT g)))))

(define (edges g)
  (for*/list ([s (vertices g)]
              [d (adjacent g s)])
      (cons s d)))


(define (directed->undirected g)
  (let ([gU (new-graph)])
    (for* ([u (vertices g)]
           [v (adjacent g u)])
      (add-edge gU u v)
      (add-edge gU v u))
    gU))

(define (dfs g v)
  ; (printf "dfs ~a\n" v)
  (let ([visited? (make-hash)])
    (for ([u (vertices g)])
      (hash-set! visited? u #f))
    ; (printf "visited? ~a\n" visited?)
    (define (inner u)
      (hash-set! visited? u #t)
      (for ([v (adjacent g u)]
            #:when (not (hash-ref visited? v)))
        (inner v)))
    (inner v)
    (for/list ([(v visited) visited?] #:when visited) v)))
    

(define (transpose g)
  (graph (graph-adjT g) (graph-adj g)))
; (define (transpose g)
;   (let* ([gT (new-graph)]
;          [adj (graph-adj g)])
;     (hash-for-each adj
;       (lambda (s adj)
;         (for ([d adj])
;           (add-edge gT d s))))
;     gT))

(define (adjacent g v)
  (let ([adj (graph-adj g)])
    (if (hash-has-key? adj v)
      (hash-ref (graph-adj g) v)
      (list))))
(define (adjacentT g v)
  (let ([adjT (graph-adjT g)])
    (if (hash-has-key? adjT v)
      (hash-ref (graph-adjT g) v)
      (list))))

(define (degree/out g v)
  (length (adjacent g v)))
        
(define (degree/in g v)
  (length (adjacentT g v)))  

(define (components g)
  (let ([ancestors (make-hash)])
    (for ([u (vertices g)])
      (hash-set! ancestors u #f))
    (define (inner u anc)
      (hash-set! ancestors u anc)
      (for ([v (adjacent g u)]
            #:when (not (hash-ref ancestors v)))
        (inner v anc)))
    (for ([u (vertices g)]
          #:when (not (hash-ref ancestors u)))
      (inner u u))
    (let ([partitions
           (map (lambda (u)
            (filter (lambda (v)
              (equal? u (hash-ref ancestors v)))
            (vertices g)))
           (vertices g))])
      (filter (lambda (l) (< 0 (length l))) partitions))))

                    

(define g (new-graph))
(define adj (graph-adj g))
(add-edge g 'a '1)
(add-edge g 'b '2)
(add-edge g 'b '2)
(add-edge g 'b '3)
(edges g)