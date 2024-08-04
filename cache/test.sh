#!/bin/bash

#!/usr/bin/env bash

./main 128 8 0 P_PLRU 1 0 ./trace/astar.trace
./main 128 8 8 P_LRU 1 0 ./trace/astar.trace
./main 128 8 8 P_RANDOM 1 0 ./trace/astar.trace

./main 128 8 8 P_PLRU 1 0 ./trace/bzip2.trace
./main 128 8 8 P_LRU 1 0 ./trace/bzip2.trace
./main 128 8 8 P_RANDOM 1 0 ./trace/bzip2.trace

./main 128 8 8 P_PLRU 1 0 ./trace/mcf.trace
./main 128 8 8 P_LRU 1 0 ./trace/mcf.trace
./main 128 8 8 P_RANDOM 1 0 ./trace/mcf.trace

./main 128 8 8 P_PLRU 1 0 ./trace/perlbench.trace
./main 128 8 8 P_LRU 1 0 ./trace/perlbench.trace
./main 128 8 8 P_RANDOM 1 0 ./trace/perlbench.trace
