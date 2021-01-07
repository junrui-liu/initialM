## initialH: Experimental Tree Traversal Synthesis

(The tool is currently under inspection on Molly's forensic desktop.)

### Commands

```bash
# molly3.grammar: accessing list children without dependencies
racket ./run.rkt --interface Node --traversal fusion --grammar ./benchmarks/molly/molly3.grammar

# molly4.grammar: accessing list children with dependencies
racket ./run.rkt --interface Node --traversal fusion --grammar ./benchmarks/molly/molly4.grammar

# molly5.grammar: parent depends on children
racket ./run.rkt --interface Node --traversal fusion --grammar ./benchmarks/molly/molly5.grammar

# molly6.grammar: chain dependency
racket ./run.rkt --interface VirtualRoot --traversal fusion --grammar ./benchmarks/molly/molly6.grammar

# molly7.grammar: many attributes (takes longer than others to solve)
racket ./run.rkt --interface VirtualRoot --traversal fusion --grammar ./benchmarks/molly/molly7.grammar

# grafter/oopsla-example.grammar: this takes forever to solve
racket ./run.rkt --interface Node --traversal fuse --grammar ./benchmarks/grafter/oopsla-example.grammar

# hv-toy.grammar
racket ./run.rkt --interface HVBox --traversal fuse --grammar benchmarks/molly/hv-toy.grammar
```

