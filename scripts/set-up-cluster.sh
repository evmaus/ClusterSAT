#!/bin/bash


../bazel-bin/src/clustersat/leader/leader_server --listening_address=0.0.0.0:50051 \
   --node_addresses="localhost:50052" --logtostderr=1 &
../bazel-bin/src/clustersat/node/tribblesat_server --listening_address=0.0.0.0:50052 --configuration=default &
../bazel-bin/src/clustersat/node/tribblesat_server --listening_address=0.0.0.0:50053 --configuration=linear &

wait
