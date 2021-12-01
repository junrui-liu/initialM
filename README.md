## Hecate: Tree Traversal Synthesis Using Domain-Specific Symbolic Compilation

This branch (`master`) is the implementation of domain-specific encoding.

### Prerequisites

- Racket 7.7 ([https://download.racket-lang.org/releases/7.7/](https://download.racket-lang.org/releases/7.7/))

- Rosette 3.2 ([https://github.com/emina/rosette](https://github.com/emina/rosette))

  - To install Rosette 3.2, you need to install from source:

    ```bash
    git clone https://github.com/emina/rosette.git
    raco pkg remove rosette
    cd rosette/
    git checkout c092b65
    raco pkg install
    ```

### ASPLOS Commands for Artifact Evaluation

This reproduces the `HECATE` column of Table 1:

```bash
# binary-tree.grammar
racket ./run.rkt --root Root fuse benchmarks/grafter/binary-tree.grammar

# fmm.grammar (this needs full examples)
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/fmm.grammar

# piecewise series
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp1.grammar
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp2.grammar
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp3.grammar

# ast (this needs full examples, which takes a long time)
racket ./run.rkt --root Program fuse benchmarks/grafter/ast.grammar

# render (this needs full examples)
racket ./run.rkt --root Document fuse benchmarks/grafter/render.grammar
```

Note: add timing commands to record time usage, e.g., `time` in Linux.

### Other Commands

This includes all commands for both evaluation and debugging.

```bash
# render-toy-vector.grammar
racket ./run.rkt --root Box layout benchmarks/grafter/render-toy-vector.grammar

# render-toy-linked.grammar
racket ./run.rkt --root Box layout benchmarks/grafter/render-toy-linked.grammar

# toy.grammar for layout engine
racket ./run.rkt --root Tree layout benchmarks/toy.grammar

# memory-bug.grammar
racket ./run.rkt --root Function fuse benchmarks/testing/memory-bug.grammar

# hv-toy.grammar
racket ./run.rkt --root HVBox fuse benchmarks/grafter/hv-toy.grammar

# oopsla-example.grammar
racket ./run.rkt --root Root fuse benchmarks/grafter/oopsla-example.grammar

# binary-tree.grammar
racket ./run.rkt --root Root fuse benchmarks/grafter/binary-tree.grammar

# fmm.grammar (this needs full examples)
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/fmm.grammar

# piecewise series
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp1.grammar
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp2.grammar
racket ./run.rkt --root VirtualRoot fuse benchmarks/grafter/piecewise-exp3.grammar

# render (this needs full examples)
racket ./run.rkt --root Document fuse benchmarks/grafter/render.grammar

# ast (this needs full examples, which takes a long time)
racket ./run.rkt --root Program fuse benchmarks/grafter/ast.grammar

# ast-list (this needs full examples, which takes a long time)
racket ./run.rkt --root Program fuse benchmarks/grafter/ast-list.grammar
```

