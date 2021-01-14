## initialH: Experimental Tree Traversal Synthesis

(The `tracing`/`master` branch: domain-specific encoding.)

> Warning: reported bug in `denote-ite` unresolved in this branch.

### Benchmark Commands

```bash
# hv-toy.grammar
racket ./run.rkt --root HVBox fuse benchmarks/grafter/hv-toy.grammar

# oopsla-example.grammar
racket ./run.rkt --root Root fuse benchmarks/grafter/oopsla-example.grammar

# binary-tree.grammar
racket ./run.rkt --root Root fuse benchmarks/grafter/binary-tree.grammar

# fmm.grammar
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/fmm.grammar

# piecewise series
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp1.grammar
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp2.grammar
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp3.grammar
```

