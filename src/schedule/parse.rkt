#lang rosette

; Parser and Serializer for Language of Tree Traversal Schedules

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre)
         parser-tools/yacc
         "../grammar/syntax.rkt"
         "../utility.rkt"
         "dirty.rkt")

(provide parse-schedule
         file->schedule
         schedule->string
         schedule->solved)

; ----------------
; Lexer Definition
; ----------------

(define-empty-tokens e-tkns
  (LBRACE RBRACE LPAREN RPAREN LBRACKET RBRACKET
   DOT SEMICOLON SEQ PAR
   TRAVERSAL CASE ITERATE LEFT RIGHT
   RECUR CALL EVAL SKIP HOLE
   SELF
   EOF))

(define-tokens tkns (IDENT))

(define-lex-trans ident
  (syntax-rules ()
    ((_)
     (:: (:or (char-range "a" "z") (char-range "A" "Z") "_" "&") (:* (:or (char-range "a" "z") (char-range "A" "Z") (char-range "0" "9") "_" "-"))))))

(define-lex-trans comment
  (syntax-rules ()
    ((_)
     (:or (:: "//" (:* (char-complement (:or "\r" "\n"))) (:? "\r") "\n")
          (:: "/*" (complement (:: any-string "*/" any-string)) "*/")))))

(define sched-lex
  (lexer
   [(comment) (sched-lex input-port)]
   ["{" (token-LBRACE)]
   ["}" (token-RBRACE)]
   ["(" (token-LPAREN)]
   [")" (token-RPAREN)]
   ["[" (token-LBRACKET)]
   ["]" (token-RBRACKET)]
   ["." (token-DOT)]
   [";" (token-SEMICOLON)]
   [";;" (token-SEQ)]
   ["||" (token-PAR)]
   ["traversal" (token-TRAVERSAL)]
   ["case" (token-CASE)]
   ["iterate" (token-ITERATE)]
   ["left" (token-LEFT)]
   ["right" (token-RIGHT)]
   ["recur" (token-RECUR)]
   ["call" (token-CALL)]
   ["eval" (token-EVAL)]
   ["skip" (token-SKIP)]
   ["??" (token-HOLE)]
   ["self" (token-SELF)]
   [(ident) (token-IDENT (string->symbol lexeme))]
   [whitespace (sched-lex input-port)]
   [(eof) (token-EOF)]))

(define sched-parse-lexed
  (parser
   (start composition)
   (tokens tkns e-tkns)
   (end EOF)
   (error (λ (_ token lexeme) (printf "Unexpected token: ~a(~a)~n" token lexeme)))
   (grammar
    (composition
     ((traversal SEQ composition) `(seq ,$1 ,$3))
     ((traversal PAR composition) `(par ,$1 ,$3))
     ((traversal) $1))

    (traversal
     ((TRAVERSAL name LBRACE visitor-list RBRACE) `(trav ,$2 ,$4))
     ((LPAREN composition RPAREN) $2))

    (visitor-list
     ((visitor visitor-list) (cons $1 $2))
     ((visitor) (list $1)))

    (visitor
     ((CASE name LBRACE command-list RBRACE) (cons $2 $4)))

    (command-list
     ((command command-list) (cons $1 $2))
     (() null))

    (command
     ((ITERATE LBRACKET LEFT RBRACKET name LBRACE command-list RBRACE) `(iter-left ,$5 ,$7))
     ((ITERATE LBRACKET RIGHT RBRACKET name LBRACE command-list RBRACE) `(iter-right ,$5 ,$7))
     ((RECUR name SEMICOLON) `(recur ,$2))
     ((HOLE SEMICOLON) `(hole))
     ((SKIP SEMICOLON) `(skip))
     ((EVAL node DOT name SEMICOLON) `(eval ,$2 ,$4))
     ((CALL name SEMICOLON) `(call ,$2)))

    (node
     ((SELF) 'self)
     ((name) $1))

    (name
     ((IDENT) $1)
     ((TRAVERSAL) 'traversal)
     ((CASE) 'case)
     ((ITERATE) 'iterate)
     ((LEFT) 'left)
     ((RIGHT) 'right)
     ((RECUR) 'recur)
     ((CALL) 'call)
     ((EVAL) 'eval)
     ((SKIP) 'skip)))))

(define (parse-schedule input)
  (sched-parse-lexed (thunk (sched-lex input))))

(define (file->schedule path)
  (call-with-input-file path parse-schedule #:mode 'text))

(define (schedule->string sched sdict sol)
  (match sched
    [(ag:sequential left-sched right-sched)
     (format "~a ;; ~a"
             (schedule->string left-sched sdict sol)
             (schedule->string right-sched sdict sol))]
    [(ag:parallel left-sched right-sched)
     (format "(~a || ~a)"
             (schedule->string left-sched sdict sol)
             (schedule->string right-sched sdict sol))]
    [(ag:traversal order visitors)
     (format "traversal ~a {\n~a\n}"
             order
             (string-join (for/list ([v visitors]) (visitor->string v sdict sol)) "\n"))]
  )
)

(define indentation (make-parameter 0))

(define (indent)
  (build-string (* (indentation) 2) (thunk* #\ )))

(define (visitor->string visitor sdict sol)
  (match visitor
    [(ag:visitor class commands)
     (parameterize ([indentation (+ (indentation) 1)])
       (define content
         (parameterize ([indentation (+ (indentation) 1)])
           (string-join (for/list ([c commands]) (command->string c sdict sol)) "\n")))
       (define a (ag:class-allocation class))
       (define allocation-content
        (parameterize ([indentation (+ (indentation) 1)])
          (string-join (dirty:allocation->strings a sol) "\n")))
       (format "~acase ~a {\n~a\n~a\n~a}"
               (indent)
               (ag:class-name class)
               allocation-content
               content
               (indent)))]
  )
)

(define (command->string command sdict sol)
  (match command
    [(list) #f] ; choose to evaluate nothing
    [(ag:iter/left child commands)
     (define content
       (parameterize ([indentation (+ (indentation) 1)])
         (string-join (for/list ([c commands]) (command->string c sdict sol)) "\n")))
     (format "~aiterate[left] ~a {\n~a\n~a}"
             (indent) child content (indent))]
    [(ag:iter/right child commands)
     (define content
       (parameterize ([indentation (+ (indentation) 1)])
         (string-join (for/list ([c commands]) (command->string c sdict sol)) "\n")))
     (format "~aiterate[right] ~a {\n~a\n~a}"
             (indent) child content (indent))]
    [(ag:when ii commands)
      (define cond
        (if (equal? 0 (length ii))
          "true"
          (string-join (map (curry format "d~a") ii) " || " )))
      (define content
       (parameterize ([indentation (+ (indentation) 1)])
         (string-join (for/list ([c commands]) (command->string c sdict sol)) "\n")))
     (format "~awhen ~a {\n~a\n~a}"
             (indent) cond content (indent))]
    [(ag:recur child)
     (format "~arecur ~a;" (indent) child)]
    [(ag:eval (cons node label))
     (format "~aeval ~a.~a;" (indent) node label)]
    [(ag:hole) (format "~a??;" (indent))]
    [(ag:skip) (format "~askip;" (indent) (indent))]
    ; [(list commands ...)
    ;  (string-join (for/list ([c commands]) (command->string c sdict sol)) "\n")]
    [(list 'multichoose nth vs ...)
      (if (hash-has-key? sdict nth)
        (begin
          (define ccmds (evaluate (hash-ref sdict nth) sol))
          ; (when (slist? ccmds) (set! ccmds (get-field v ccmds)))
          ; (printf "> chosen: ~a\n" ccmds)
          (string-join 
            (filter (lambda (x) x) ; remove #f from choosing nothing
              (for/list ([c ccmds])
                (command->string c sdict sol)
              ) 
            )
            "\n"
          )
        )
        ; can't find key: didn't traverse this hole, which means the solution can be wrong
        ""
      ) 
    ]
  )
)



(define (schedule->solved sdict sol wcdict sched)
  (match sched
   [(ag:traversal order visitors)
    (ag:traversal order (map (curry visitor->solved sdict sol wcdict) visitors))]))

(define (visitor->solved sdict sol wcdict visitor)
  (match visitor
  [(ag:visitor class commands)
   (ag:visitor class (append-map (curry command->solved class sdict sol wcdict) commands))]))

(define (command->solved class sdict sol wcdict c)
  (define allocation (ag:class-allocation class))
  (define (recur commands) (append-map (curry command->solved class sdict sol wcdict) commands))
  (match c
    [(list) '()]
    [(ag:iter/left child commands)
      (list (ag:iter/left child (recur commands)))]
    [(ag:iter/right child commands)
      (list (ag:iter/right child (recur commands)))]
    [(ag:when (list 'wcchoose nth bits) commands)
      (define commands* (recur commands))
      (define conds* (evaluate (hash-ref wcdict nth) sol))
      (printf "~a\n" conds*)
      (define deps (union* (for/list ([command* commands*])
        (define ev-attr (ag:eval-attribute command*))
        (define ev-rule (ag:class-ref*/rule class ev-attr))
        (define ev-formula (ag:rule-formula ev-rule))
        (define rhs (ag:term-rhs ev-formula))
        rhs)))
      (printf "deps: ~a\n" deps)
      (list (ag:when (nonzeros conds*) commands*))]
    [(list 'multichoose nth vs ...)
      (if (hash-has-key? sdict nth)
        (begin
          (define commands* (filter (lambda (x) (ag:eval? x)) (evaluate (hash-ref sdict nth) sol)))
          ; (for/list ([command* commands*])
          ;   (define ev-attr (ag:eval-attribute command*))
          ;   (define ev-rule (ag:class-ref*/rule class ev-attr))
          ;   (define ev-formula (ag:rule-formula ev-rule))
          ;   (printf "eval ~a with rhs ~a\n" command* (ag:term-rhs ev-formula)))
          commands*)
      #f)]
    [_ (list c)]))
  