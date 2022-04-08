#lang rosette

; Tracing synthesizer for language of tree traversal schedules

(require "../schedule/enumerate.rkt"
         "../grammar/syntax.rkt"
         "../grammar/tree.rkt"
         "../schedule/parse.rkt"
         "../utility.rkt"
         "../trace.rkt"
         "../incremental/analyze.rkt"
         "interpreter.rkt")

(provide complete-sketch
         complete-sketch-non-incr
         enumerate-from-meta)

(define substitute 0)
(define max-inner 100)
(define max-outer 5)
(define blame-stack (list))
(define trace-asserts #f)
(define best-model #f)
(define best-cost #f)

(define/match (concretize* S)
  [((ag:sequential sched-1 sched-2))
   (ag:sequential (concretize* sched-1) (concretize* sched-2))]
  [((ag:parallel sched-1 sched-2))
   (ag:parallel (concretize* sched-1) (concretize* sched-2))]
  [((ag:traversal order visitor-list))
   (ag:traversal order (map concretize* visitor-list))]
  [((ag:visitor class command-list))
   (ag:visitor class (substitute command-list))])

(define (permute* . xs)
  (permute (length xs) xs))

(define (generate-blames! analyses)
  (define blames (list))
  (for/list ([visitor-analyses analyses])
    (let* ([analyses-sorted (sort visitor-analyses < #:key an:analysis-cost)]
           [non-trivial (filter an:analysis-non-trivial analyses-sorted)])
           
      ; (printf "analyses-sorted: ~a\n" analyses-sorted)
      ; (printf "non-trivial: ~a\n" non-trivial)
      (if (< 0 (length non-trivial))
        (begin
          (define a (last non-trivial))
          (printf "(~a) ~a\n" (an:analysis-cost a) (an:analysis-msg a))
          (set! blames (cons (an:analysis-blame a) blames)))
        (void))))
  blames)

(define (push-blames! analyses)
  (define blames (generate-blames! analyses))
  (set! blame-stack (append blames blame-stack))
  blames)
; (define (push-blames! analyses)
;   (for ([visitor-analyses analyses])
;     (let* ([analyses-sorted
;             (sort visitor-analyses < #:key an:analysis-cost)]
;            [a (last analyses-sorted)])
;       (printf "(~a) ~a\n" (an:analysis-cost a) (an:analysis-msg a))
;       (set! blame-stack (cons (an:analysis-blame a) blame-stack)))))

(define (pop-blames!)
  (if (= 0 (length blame-stack))
    (void)
    (set! blame-stack (cdr blame-stack))))

(define (assert-blames!)
  (for* ([blame blame-stack])
    (assert blame)))

(define (reset-blames!)
  (clear-asserts!)
  (for ([a trace-asserts])
    (assert a))
  (set! blame-stack (list)))

(define (get-total-cost analyses)
  (apply +
    (for*/list ([visitor-analyses analyses]
                [analysis visitor-analyses])
    (an:analysis-cost analysis))))
    

(define (complete-sketch G sketch examples)
  (parameterize ([*box* ref]
                 [*box?* ref?]
                 [*unbox* deref]
                 [*set-box!* set-ref!]
                 [*denotation* abstract-denotation]
                 [*multichoose* permute*])

    (define schedule (instantiate-sketch G sketch))

    (define initial-time (current-milliseconds))

    (for ([tree examples])
      (let ([tree (tree-annotate tree)])
        (interpret schedule tree)
        (tree-validate tree deref)
        (break)))
    
    (set! trace-asserts (asserts))
    (reset-blames!)

    ; Enumerate models (buggy)
    ; (define models (list))
    ; (for ([i (in-range max-inner)])
    ;   (printf "Iter ~a\n" i)
    ;   (define model (solve))
    ;   (displayln (if model "SAT" "UNSAT"))
    ;   (if model
    ;     (begin
    ;       (set! models (cons model models))
    ;       (set! substitute (model->subst model))
    ;       (define S (concretize* schedule))
    ;       (displayln (string-replace (schedule->string S) "\n\n" "\n"))
    ;       (parameterize ([an:substitute substitute])
    ;       (let*
    ;         ([analyses (an:analyze-schedule schedule)]
    ;          [total-cost (get-total-cost analyses)])
    ;         (printf "Total cost: ~a\n" total-cost)
    ;         (for ([m models])
    ;           (assert (anew m))))))
    ;     #f))))

    ; Optimal synthesis
    (define (iter-solve i)
      (printf "Iter ~a\n" i)
      (define model (solve))
      (displayln (if model "SAT" "UNSAT"))
      (if model
        (begin
          (set! substitute (model->subst model))
          (define S (concretize* schedule))
          (displayln (string-replace (schedule->string S) "\n\n" "\n"))
          (parameterize ([an:substitute substitute])
          (let*
            ([analyses (an:analyze-schedule schedule)]
            [total-cost (get-total-cost analyses)])
            (printf "Total cost: ~a\n" total-cost)
            (when (or (not best-model) (< total-cost best-cost))
              (printf "Found new best!\n")
              (set! best-model model)
              (set! best-cost total-cost))
            (define blames (push-blames! analyses))
            (if (or (<= i 2) (< 0 (length blames)))
              (begin
                (assert-blames!)
                (iter-solve (+ i 1)))
              (begin
                (printf "solve-iter: No more blames\n")
                model)))))
        #f))
    
    (define (try-until-success)
      (let ([model (iter-solve 1)])
        (if (not model)
          (begin
            (reset-blames!)
            (try-until-success))
          model)))

    (define (iter-solve-outer)
      (for ([j (in-range max-outer)])
        (iter-solve 1)
        (reset-blames!)))
    

    (iter-solve-outer)
    (define model best-model)
    ; (define model (solve-until-max-or-unsat 1))
    (printf "Total cost: ~a\n" best-cost)
    (displayln (if model "SAT" "UNSAT"))
    (when model
      (set! substitute (model->subst model))
      (define S (concretize* schedule))
      (displayln (string-replace (schedule->string S) "\n\n" "\n")))))
        

    ; (for ([i (in-range max-inner)])
    ;   (printf "Iter ~a\n" i)
    ;   (define model (solve))
    ;   (displayln (if model "SAT" "UNSAT"))
    ;   (when model
    ;     (set! substitute (model->subst model))
    ;     (define S0 (concretize* schedule))
    ;      (displayln (string-replace (schedule->string S0) "\n\n" "\n"))
    ;     (parameterize ([an:substitute substitute])
    ;       (let*
    ;         ([analyses (an:analyze-schedule schedule)]
    ;          [total-cost (get-total-cost analyses)])
    ;         (printf "Total cost: ~a\n" total-cost)
    ;         (push-blames! analyses)
    ;         (assert-blames!)))))))
        ; S0))))
        ; (anew (list model))
            ; (define model1 (solve))
            ; (set! substitute (model->subst model1))
            ; (define S1 (concretize* schedule))
            ; (list S0 S1))))))
    ; (match-let-values ([(running-time) (- (current-milliseconds) initial-time)]
    ;                    [(nodes variables) (formula-size)]
    ;                    [((list model) overhead-time solving-time _)
    ;                     (time-apply solve null)])
    ;   (displayln (if model "SAT" "UNSAT"))
    ;   (printf "Symbolic Evaluation: ~ams\n" (+ running-time overhead-time))
    ;   (printf "Constraint Solving: ~ams\n" (- solving-time overhead-time))
    ;   (printf "Constraint Size: ~a nodes and ~a variables\n" nodes variables)
    ;   (when model
    ;     (set! substitute (model->subst model))
    ;     (define S0 (concretize* schedule))
    ;     (parameterize ([an:substitute substitute])
    ;       (let*
    ;         ([analyses (an:analyze-schedule schedule)]
    ;          [total-cost (get-total-cost analyses)])
    ;         (printf "Total cost: ~a\n" total-cost)
    ;         (assert-blames analyses)


    ;     ; S0))))
    ;     ; (anew (list model))
    ;         (define model1 (solve))
    ;         (set! substitute (model->subst model1))
    ;         (define S1 (concretize* schedule))
    ;         (list S0 S1))))
    ;         )))

(define (enumerate-from-meta G sketch-meta)
  (define granularity (hash 'Viewport 1 'Block 3))
  (enumerate-incr-sketches G sketch-meta granularity))

(define (complete-sketch-non-incr G sketch examples)
  (parameterize ([*box* ref]
                 [*box?* ref?]
                 [*unbox* deref]
                 [*set-box!* set-ref!]
                 [*denotation* abstract-denotation]
                 [*multichoose* permute*])

    (define schedule (instantiate-sketch G sketch))

    (define initial-time (current-milliseconds))

    (for ([tree examples])
      (let ([tree (tree-annotate tree)])
        (interpret schedule tree)
        (tree-validate tree deref)
        (break)))

    (match-let-values ([(running-time) (- (current-milliseconds) initial-time)]
                       [(nodes variables) (formula-size)]
                       [((list model) overhead-time solving-time _)
                        (time-apply solve null)])
      (displayln (if model "SAT" "UNSAT"))
      (printf "Symbolic Evaluation: ~ams\n" (+ running-time overhead-time))
      (printf "Constraint Solving: ~ams\n" (- solving-time overhead-time))
      (printf "Constraint Size: ~a nodes and ~a variables\n" nodes variables)
      (when model
        (begin
          (set! substitute (model->subst model))
          (define S (concretize* schedule))
          (displayln (string-replace (schedule->string S) "\n\n" "\n")))))))

