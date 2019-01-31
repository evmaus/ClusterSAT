# TribbleSat

Experimental SAT solver.  I'll be exploring parallel SAT solving here.

## TODO (Random)

- Handle errors better than crashing in both dimacs_parser
- Unimplemented tests

## TODO (Project)

- Create a coordinator that can distribute a SAT Problem to a set of solver nodes.
- Script setting up a coordinator and solving nodes, and demonstrate distributing problems to both.
- Stop all nodes currently working on a problem when a node finishes it.
- Add logging to all nodes.
