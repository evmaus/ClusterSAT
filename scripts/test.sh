#!/bin/bash

for filename in ./src/tribblesat/parsers/testdata/medium-sat/*.cnf; do
  [ -e "$filename" ] || continue
  echo $filename
  ./bazel-bin/src/tribblesat/utilities/cdcl_runner --file=$filename --info
done
