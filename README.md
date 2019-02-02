# TribbleSat

Experimental SAT solver.  I'll be exploring parallel SAT solving here.

## TODO (Random)

- Handle errors better than crashing in both dimacs_parser
- Unimplemented tests
- Mock out tests for the solver node, client, leader node, etc.
- More comments in ClusterSAT
- Switch TribbleSAT over to the google logging framework rather than a custom one.

## TODO (Project)

- Logging for TribbleSAT server node
- Solve one problem at a time on a node.
- Implement sharing of learned terms.
- Implement more variable selection strategies.
- Implement more restart strategies.
- Implement more garbage collection strategies.