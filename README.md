# TribbleSAT and ClusterSAT

## TribbleSAT

Experimental SAT solver.

## ClusterSAT

A framework for distributing SAT Solving across a set of 'solver' nodes.  Uses TribbleSAT, but is designed to be
SAT solver independent.

## Building

Uses [Bazel](https://bazel.build/) to build, which must be installed.  That should be the only dependency.

Building is then "cd src; bazel build //..." to download dependent libraries, and build both TribbleSAT and ClusterSAT.

## Testing

Unit tests can be run via "bazel test //...".  Note that there are some unit tests that are
EXPECTED to fail, as they haven't all been written yet.  (Yes, the author is appropriately ashamed of this.)  The shared characteristic of these tests are that they are the only test in the test suite/test target, and they immediately fail.

## Usage

### Running TribbleSAT

TribbleSAT is a simple SAT solver.  You can run it on a file (see some from the [the site here](https://www.cs.ubc.ca/~hoos/SATLIB/benchm.html) in ./src/tribblesat/parsers/testdata/) pretty easily.

After building, the TribbleSAT executable is at:
./bazel-bin/src/tribblesat/utilities/cdcl_runner

And can be run like this:
./bazel-bin/src/tribblesat/utilities/cdcl_runner --file=$filename
(This runs it with the default settings.  Alternate settings, which may be slower, require modifying ./src/tribblesat/utilities/cdcl_runner.)

### Running ClusterSAT

ClusterSAT uses a leader/follower model.  You will need to start up at least one leader
and at least one follower, and then you can use a client to interact with it.

After building, the leader can be run like this:
./bazel-bin/src/clustersat/leader/leader_server --listening_address=0.0.0.0:50051 \
   --node_addresses="localhost:50052;localhost:50053" --logtostderr=1 &

Note:  listening_address is the address to listen to on the current machine.
node_addresses is a semicolon delineated list of follower servers that should be running
when the leader is running.

And the follower can be run like this:
./bazel-bin/src/clustersat/node/tribblesat_server --listening_address=0.0.0.0:50052 --configuration=default
AND/OR
./bazel-bin/src/clustersat/node/tribblesat_server --listening_address=0.0.0.0:50053 --configuration=linear

(Linear sets up a tribblesat_server with a linear variable selection scheme, default
uses VSIDS.)

There is a client that submits a request and then times that can be run like this:
./bazel-bin/src/clustersat/client/timing_wrapper --file=$filename --server="localhost:50051"
NOTE:  Filename should be a file name of a .cnf format file.  Server should be the leader server of a ClusterSAT instance.

See the ./scripts folder for some more example usage of TribbleSAT and ClusterSAT.

## Details

See 'documents' for more details on how TribbleSAT and ClusterSAT work.

Data analysis scripts and test scripts are all in ./scripts, which all should be run
from the ./scripts directory.

## TODO (Project)

- Timing for TribbleSAT/ClusterSAT on medium size problems
- Write up the results

## TODO (Random/Future)

- Handle errors better than crashing in dimacs_parser
- Unimplemented tests
- Mock tests for the solver node, client, leader node, etc.
- More comments in ClusterSAT
- Solve one problem at a time on a node.
- Implement sharing of learned terms.
- Implement more variable selection strategies.
- Implement more restart strategies.
- Implement more garbage collection strategies.
