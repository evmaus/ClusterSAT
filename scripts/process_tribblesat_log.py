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