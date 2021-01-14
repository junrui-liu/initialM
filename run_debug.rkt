#!/usr/bin/env racket
#lang rosette

; Script to run the synthesizer on a given attribute grammar.

(require 
	racket/cmdline
	racket/pretty
	"./src/checking.rkt"
	"./src/utility.rkt"
	"./src/grammar/parse.rkt"
	"./src/grammar/validate.rkt"
	"./src/grammar/syntax.rkt"
	"./src/grammar/tree.rkt"
	"./src/schedule/parse.rkt"
	"./src/schedule/enumerate.rkt"
)

(define (parse-grammar filename)
	(define G (file->grammar filename))
	(validate-grammar G)
	G
)

; FIXME: This is a horrid hack and only supports sequential schedule sketches.
(define (parse-schedule-sketch G S0)
	(define traversals 
		(reverse
			(map 
				(compose ag:traverse string->symbol)
				(filter 
					non-empty-string? 
					(map 
						string-trim 
						(string-split S0 ";")
					)
				)
			)
		)
	)
	(foldr ag:sequential (first traversals) (rest traversals))
)

; validation function for tree-validate
; assert the current attribute is ready
(define (validate-fn arg-slot)
	; (printf "> validate-fn: ~a\n" arg-slot)
	(assert (ag:slot-v arg-slot))
)

; (define classname "Node")
; (define rootname (string->symbol classname))
; (define schedule-sketch "fusion")
; (define grammar-filename "./benchmarks/molly/molly5.grammar")

(define classname "Root")
(define rootname (string->symbol classname))
(define schedule-sketch "fuse")
(define grammar-filename "./benchmarks/grafter/oopsla-example.grammar")

; (define classname "Root")
; (define rootname (string->symbol classname))
; (define schedule-sketch "fuse")
; (define grammar-filename "./benchmarks/molly/molly8.grammar")

; (define classname "VirtualRoot")
; (define rootname (string->symbol classname))
; (define schedule-sketch "fusion")
; (define grammar-filename "./benchmarks/molly/molly7.grammar")

; G: grammar
(define G (parse-grammar grammar-filename))
; (printf "> grammar is:\n~a\n" G)

; E: tree set
(define E (tree-examples G rootname))
(printf "> generated ~a tree examples\n" (length E))
; (for ([e E])
	; e: (struct tree (class fields readys children) #:mutable #:transparent)
	;  | "fields" "readys" "children" are currently null
	;  | e.g., #(struct:tree #<class> () () ())
	; (printf "> tree is:\n~a\n" (inspect-tree e))
; )
; (printf "> last tree is:\n~a\n" (list-ref (reverse E) 0))

; S: #(struct:traverse fusion)
;  | this is just a invocation
;  | e.g., #(struct:traverse fusion)
(define S (parse-schedule-sketch G schedule-sketch))
; (printf "> S is:\n~a\n" S)

; schedule: (struct traversal (name visitors) #:transparent)
;         | now it becomes a definition
;         | e.g., #(struct:traversal 
;                   fusion
;                   (
;                     #(struct:visitor 
;                       #<class> 
;                       (
;                         #(struct:recur lk) 
;                         #(struct:recur rk) 
;                         (choose 
;                           #(struct:eval (self . puff)) 
;                           #(struct:eval (self . pie))
;                         )
;                       )
;                     ) 
;                     #(struct:visitor 
;                       #<class> 
;                       (
;                         (choose 
;                           #(struct:eval (self . puff)) 
;                           #(struct:eval (self . pie))
;                         )
;                       )
;                     )
;                   )
;                 )
(define schedule (instantiate-sketch G S))
; (printf "> schedule is:\n~a\n" schedule)

(for ([e (reverse E)])
; (for ([e (cdr (reverse E))])
	; ae: (struct tree (class fields readys children) #:mutable #:transparent)
	;   | all struct members are currently filled
	;   | e.g., #(struct:tree 
	;             #<class> 
	;             (
	;               (puff . #(struct:slot #f)) 
	;               (pie . #(struct:slot #f))
	;             ) 
	;             (
	;               (puff . #(struct:slot #f)) 
	;               (pie . #(struct:slot #f))
	;             )
	;             () --> no children
	;           )
	; (printf "> tree is:\n~a\n" (inspect-tree e))
	(define ae (tree-annotate e))
	; (printf "> annotated tree is:\n~a\n" ae)

	; then start the interpretation
	(interpret schedule ae)
	; (printf "> interpreted tree is:\n~a\n" ae)

	; validate is reading all attributes
	(tree-validate ae validate-fn)


	; (pause)
)

(define sol (solve (assert #t)))
(if (sat? sol)
	(begin
		(printf "> SAT\n")
		(printf (schedule->string schedule sdict sol))
		(printf "\n")
	)
	(begin
		(printf "> UNSAT\n")
	)
)

