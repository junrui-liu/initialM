#!/bin/sh

./run.rkt --root Tree -o browser/src/layout.rs layout benchmarks/toy.grammar
cd browser
cargo build && cargo run -- --html examples/test.html --css examples/test.css
