# TribbleSat

Experimental SAT solver.  I'll be exploring parallel SAT solving here.

## TODO (Random)

- Output models.
- Implement "implies" binary operation
- Fix memory issues with functions--implement destructor, use unique pointers from absl.
- Handle errors better than crashing in dimacs_parser

## TODO (Project)

- Implement arbitrary model -> CNF conversion
- Implement CDCL algorithm for SAT solving
- Investigate/Implement parallelized CDCL algorithm (ManySAT)
- Investigate/Implement SAT splitting (GrADSAT/PSATO)
- Combine the two strategies in a novel way