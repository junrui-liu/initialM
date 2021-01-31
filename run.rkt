#!/usr/bin/env racket
#lang rosette

; Script to run the synthesizer on a given attribute grammar.

(require racket/cmdline
         racket/pretty
         "src/grammar/parse.rkt"
         "src/grammar/validate.rkt"
         "src/grammar/syntax.rkt"
         "src/grammar/tree.rkt"
         "src/schedule/parse.rkt"
         "src/tracing/synthesizer.rkt"
         "src/backend/generate.rkt"
         "src/backend/printer.rkt")

;(define verbose? (make-parameter #f))
(define *root* (make-parameter 'Root))
(define *output* (make-parameter "browser/src/layout.rs"))

(define (parse-grammar filename)
  (let ([G (file->grammar filename)])
    (validate-grammar G)
    G))

; FIXME: This is a horrid hack and only supports sequential schedule sketches.
(define (parse-schedule-sketch G S0)
  (define traversals
    (reverse
     (map (compose ag:traverse string->symbol)
          (filter non-empty-string?
                  (map string-trim (string-split S0 ";"))))))
  (foldr ag:sequential (first traversals) (rest traversals)))

(command-line
 #:program "synthesize"
 #:once-each
 ;[("-v" "--verbose") "Display verbose intermediate information"
 ;                    (verbose? #t)]
 [("-R" "--root") classname "Class to use as tree root"
                  (*root* (string->symbol classname))]
 [("-o" "--out") filename "File to output generated code"
                  (*output* filename)]
 #:args (schedule-sketch grammar-filename)
 (let* ([G (parse-grammar grammar-filename)]
        [E (tree-examples G (*root*))]
        [temp (printf "> generated ~a tree examples\n" (length E))]
        [temp0 (printf "> first tree looks like: ~a\n" (car E))]
        [S (parse-schedule-sketch G schedule-sketch)]
        [S* (complete-sketch G S E)])
   (when S*
     (displayln (string-replace (schedule->string S*) "\n\n" "\n"))
     (let ([P (generate-program G S*)]
           [file (open-output-file (*output*) #:mode 'text #:exists 'replace)])
       (parameterize ([current-output-port file])
         (print-program P))))))
