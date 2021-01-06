#!/usr/bin/env racket
#lang rosette

; Script to run the synthesizer on a given attribute grammar.

(require 
	racket/cmdline
	racket/pretty
	"./src/grammar/parse.rkt"
	"./src/grammar/validate.rkt"
	"./src/grammar/syntax.rkt"
)