#!/usr/bin/python
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

import sys


def main(argv):
    pass


if __name__ == '__main__':
    main(sys.argv)
#!/usr/bin/python


tribblesat_total_time = 0.0
tribblesat_total_runs = 0

def process_tribblesat_line(line):
    global tribblesat_total_time, tribblesat_total_runs
    if 'total_time' in line.lower():
        tribblesat_total_time += float(line.split(':')[1])
        tribblesat_total_runs += 1

with open('../old-run-data/tribblesat-final-run-2.txt') as f:
    for line in f:
        process_tribblesat_line(line)

print "Total time: ", tribblesat_total_time
print "Total runs: ", tribblesat_total_runs
print "Median time: ", tribblesat_total_time / tribblesat_total_runs