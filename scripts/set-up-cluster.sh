#!/bin/bash -eu
#
# Copyright 2019 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#!/bin/bash


../bazel-bin/src/clustersat/leader/leader_server --listening_address=0.0.0.0:50051 \
   --node_addresses="localhost:50052" --logtostderr=1 &
../bazel-bin/src/clustersat/node/tribblesat_server --listening_address=0.0.0.0:50052 --configuration=default &
../bazel-bin/src/clustersat/node/tribblesat_server --listening_address=0.0.0.0:50053 --configuration=linear &

wait
