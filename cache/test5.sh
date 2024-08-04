#!/bin/bash

#!/usr/bin/env bash

./main 128 8 8 P_LRU 0 0 ./trace/astar.trace test5.log
./main 128 8 8 P_LRU 0 1 ./trace/astar.trace test5.log
./main 128 8 8 P_LRU 1 0 ./trace/astar.trace test5.log
./main 128 8 8 P_LRU 1 1 ./trace/astar.trace test5.log
./main 128 8 8 P_LRU 0 0 ./trace/bzip2.trace test5.log
./main 128 8 8 P_LRU 0 1 ./trace/bzip2.trace test5.log
./main 128 8 8 P_LRU 1 0 ./trace/bzip2.trace test5.log
./main 128 8 8 P_LRU 1 1 ./trace/bzip2.trace test5.log
./main 128 8 8 P_LRU 0 0 ./trace/mcf.trace test5.log
./main 128 8 8 P_LRU 0 1 ./trace/mcf.trace test5.log
./main 128 8 8 P_LRU 1 0 ./trace/mcf.trace test5.log
./main 128 8 8 P_LRU 1 1 ./trace/mcf.trace test5.log
./main 128 8 8 P_LRU 0 0 ./trace/perlbench.trace test5.log
./main 128 8 8 P_LRU 0 1 ./trace/perlbench.trace test5.log
./main 128 8 8 P_LRU 1 0 ./trace/perlbench.trace test5.log
./main 128 8 8 P_LRU 1 1 ./trace/perlbench.trace test5.log