# TribbleSat

Experimental SAT solver.  I'll be exploring parallel SAT solving here.

## TODO (Random)

- Handle errors better than crashing in both dimacs_parser
- Unimplemented tests
- Mock out tests for the solver node, client, leader node, etc.

## TODO (Project)

- Add status propagation to the client and leader to handle missing nodes/etc.
- Script setting up a coordinator and solving nodes, and demonstrate distributing problems to both.
- Have solver nodes report back to the leader when they finish working on a problem.
- Stop all nodes currently working on a problem when a node finishes it.
- Implement sharing of learned terms.
- Implement more variable selection strategies.
- Implement more restart strategies.
- Implement more garbage collection strategies.