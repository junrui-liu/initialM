#lang rosette

; Helper functions and common initialization.

(provide (all-defined-out))
(port-count-lines-enabled #t)
(current-bitwidth #f)

(define (pause)
	(printf "# pause...\n")
	(read-line)
)

(define (println-and-exit . msg)
	(printf "~a\n" (apply format msg))
	(exit 0)
)

; (temporary) class to wrap a list
(define slist
	(class object%
		(super-new)
		(init-field
			[v null]
		)
	)
)
(define (slist? o) (is-a? o slist))

; iv: input variable
(define (allocate-iv*)
	(define-symbolic* iv-int integer?)
	(define-symbolic* iv-bool boolean?)
	(define iv-list (list iv-int iv-bool))
	(define-symbolic* iv-ptr integer?)
	(define iv (list-ref iv-list iv-ptr))
	iv
)

; (lifted) associate list reference procedure
;        | only symbols can be keys of associate lists
;        | this is used in tree struct, e.g., (lk . #(struct:tree #<class> ...)) is a pair
;        | in schedule there's no associate list, even though there are pairs like #(struct:eval (lk . puff))
;          and both elements can be union/symbolic, which is out of scope of this procedure
;        | i.e., this won't support keys like (lk . puff)
(define (^ass-ref arg-list arg-key)
	(cond
		[(symbol? arg-key) 
			(match arg-list
				[(list cur rest ...)
					(if (equal? (car cur) arg-key) (cdr cur) (^ass-ref rest arg-key))
				]
				[(list) (println-and-exit "# exception/^ass-ref: key not found for ~a\n" arg-key)]
				[_ (println-and-exit "# exception/^ass-ref: input is not a list but ~a\n" arg-list)]
			)
		]
		[(union? arg-key) (for/all ([pp arg-key])
			(^ass-ref arg-list pp)
		)]
		[else (println-and-exit "# exception/^ass-ref: unsupported key ~a\n" arg-key)]
	)
)

; (lifted) associate list has-key? procedure
(define (^in-ass? arg-list arg-key)
	(cond
		[(symbol? arg-key) (begin
			(match arg-list
				[(list) #f]
				[(list cur rest ...)
					(if (equal? (car cur) arg-key) #t (^in-ass? rest arg-key))
				]
				[_ (println-and-exit "# exception/in-ass?: input is not a list but ~a\n" arg-list)]
			)
		)]
		[(union? arg-key) (begin
			(for/all ([pp arg-key])
				(^in-ass? list pp)
			)
		)]
		[else (println-and-exit "# exception/^in-ass?: unsupported key ~a\n" arg-key)]
	)
)

(define (oracle type)
	(match type
		['int (define-symbolic* int integer?) int]
		['bool (define-symbolic* bool boolean?) bool]
	)
)

(define ((distribute proc) v)
	(if (list? v)
		(map proc v)
		(proc v)
	)
)

(define (dict-map-key dict0 proc)
	(for/fold ([dict (dict-clear dict0)])
		([(key value) (in-dict dict0)])
		(dict-set dict (proc key) value)
	)
)

(define (dict-map-value dict0 proc)
	(for/fold ([dict (dict-clear dict0)])
		([(key value) (in-dict dict0)])
		(dict-set dict key (proc value))
	)
)

(define-syntax-rule (if/let ([id expr]) consequent alternate)
	(let ([id expr])
		(if id
			consequent
			alternate
		)
	)
)

(define-syntax-rule (when/let ([id expr]) body ...)
	(if/let ([id expr])
		(begin body ...)
		(void)
	)
)

(define-syntax when/let*
	(syntax-rules ()
		[(_ ([id expr] [id* expr*] ...) body ...)
			(let ([id expr])
				(when id
					(when/let* ([id* expr*] ...) body ...)
				)
			)
		]
		[(_ () body ...)
			(begin body ...)
		]
	)
)

(define-syntax-rule (matches? patterns ...)
	(match-lambda
		[(or patterns ...) #t]
		[_ #f]
	)
)

(define (symbol-append . xs)
	(string->symbol (string-append* (map symbol->string xs)))
)

(define (symbol-join lst [sep ""])
	(string->symbol (string-join (map symbol->string lst) sep))
)

(define symbol-upcase
	(compose string->symbol string-upcase symbol->string)
)

(define symbol-downcase
	(compose string->symbol string-downcase symbol->string)
)

; If it isn't a list, make it a singleton list.
(define (listify x)
	(if (list? x) 
		x 
		(list x)
	)
)

(define (const* f) (thunk* (f)))

; Compute the approximate size of a formula, where each unique occurrence of an
; AST node counts as 1. Returns two values: the number of unique AST nodes in the
; assertion store and the number of unique variables in the assertion store.
(define (formula-size)
	(let ([subformulae (mutable-seteq)] 
		  [nodes 0] 
		  [variables 0])
		(define (recurse term)
			(unless (set-member? subformulae term)
				(set-add! subformulae term)
				(match term
					[(expression _ terms ...)
						(set! nodes (+ nodes 1))
						(for-each recurse terms)
					]
					[(constant name _)
						(set! variables (+ variables 1))
					]
					[_
						(void)]
				)
			)
		)
		(for-each recurse (asserts))
		(values nodes variables)
	)
)

(define-syntax-rule (-- x)
	(begin
		(set! x (- x 1))
		x
	)
)

(define-syntax-rule (++ x)
	(begin
		(set! x (+ x 1))
		x
	)
)

(define (lookup lst x [same? eq?])
	(let ([y (assoc x lst same?)])
		(and y (cdr y))
	)
)

(define (find-by proj lst key #:same? [same? equal?])
	(findf (λ (elem) (same? (proj elem) key)) lst)
)

(define (filter-by proj lst key #:same? [same? equal?])
	(filter (λ (elem) (same? (proj elem) key)) lst)
)

(define (union #:same? [same? equal?] #:key [key identity] . lsts)
	(remove-duplicates (apply append lsts) same? #:key key)
)

(define (union* #:same? [same? equal?] #:key [key identity] . lsts)
	(remove-duplicates (apply append* lsts) same? #:key key)
)

(define (vector-sum vec)
	(apply + (vector->list vec))
)

(struct matrix (height width rows) #:transparent) ; row-major vector representation

(define (build-matrix n m f)
	(matrix 
		n 
		m
		(build-vector 
			n 
			(λ (i) 
				(build-vector 
					m 
					(λ (j) (f i j))
				)
			)
		)
	)
)

(define (matrix-ref mat i j)
	(vector-ref (vector-ref (matrix-rows mat) i) j)
)

(define (matrix-transpose mat)
	(let ([n (matrix-height mat)] [m (matrix-width mat)])
		(matrix m n
			(for/vector #:length m ([j (in-range m)])
				(for/vector #:length n ([i (in-range n)])
					(matrix-ref mat i j)
				)
			)
		)
	)
)

(define (matrix-columns mat)
	(matrix-rows (matrix-transpose mat))
)

(define-syntax-rule (push! name expr)
	(set! name (cons expr name))
)

(define-syntax-rule (pop! name)
	(begin0
		(first name)
		(set! name (rest name))
	)
)

(define-syntax shadow!
	(syntax-rules ()
		[(shadow! ([name expr]) body ...)
			(let ([initial name])
				(set! name expr)
				(begin0
					(begin body ...)
					(set! name initial)
				)
			)
		]
		[(shadow! (binder binders ...) body ...)
			(shadow! (binder) (shadow! (binders ...) body ...))
		]
	)
)

(define-match-expander symbol
	(syntax-rules ()
		[(symbol id) (? symbol? id)]
	)
)
