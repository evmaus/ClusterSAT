# TribbleSat

Experimental SAT solver.  I'll be exploring parallel SAT solving here.

## TODO (Random)

- Handle errors better than crashing in both dimacs_parser
- Unimplemented tests
- Mock out tests for the solver node, client, leader node, etc.

## TODO (Project)

- Stop all nodes currently working on a problem when a node finishes it.
- Script setting up a coordinator and solving nodes, and demonstrate distributing problems to both.
- Implement sharing of learned terms.
- Implement more variable selection strategies.
- Implement more restart strategies.
- Implement more garbage collection strategies.