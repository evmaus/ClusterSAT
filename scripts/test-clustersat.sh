#!/bin/bash

for filename in ../src/tribblesat/parsers/testdata/medium-sat/*.cnf; do
  [ -e "$filename" ] || continue
  echo $filename
  ../bazel-bin/src/clustersat/client/timing_wrapper --file=$filename --server="localhost:50051"
done
