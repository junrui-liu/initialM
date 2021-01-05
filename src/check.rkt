#lang rosette

; A symbolic data structure for static scheduling of statements with varying
; static and dynamic contexts.

(require
	rosette/solver/mip/cplex
	rosette/solver/smt/z3
)
(provide slot slot-v)

; Activate an ILP solver (IBM CPLEX if available, otherwise Z3 in ILP mode)
; (current-solver
;   (if (cplex-available?) ; FIXME: Rosette encodes for CPLEX very slowly...
; 	  (cplex)
; 	  (z3 #:logic 'QF_LIA)))

(struct slot (v) #:mutable #:transparent)
