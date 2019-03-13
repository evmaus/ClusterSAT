#!/usr/bin/python


clustersat_total_time = 0.0
clustersat_total_runs = 0

def process_clustersat_line(line):
    global clustersat_total_time, clustersat_total_runs
    if 'time' in line.lower():
        clustersat_total_time += float(line.split(':')[1])
        clustersat_total_runs += 1

with open('../old-run-data/clustersat-one-node.txt') as f:
    for line in f:
        process_clustersat_line(line)

print "Total time: ", clustersat_total_time
print "Total runs: ", clustersat_total_runs
print "Median time: ", clustersat_total_time / clustersat_total_runs