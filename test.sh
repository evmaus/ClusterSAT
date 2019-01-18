#!/bin/bash


for filename in ./src/parsers/testdata/longsat/*.cnf; do
  [ -e "$filename" ] || continue
  echo $filename
  ./bazel-bin/src/utilities/cdcl_runner --file=$filename
done