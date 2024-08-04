#!/bin/bash

#!/usr/bin/env bash

./main 128 4 0 P_LRU 0 0 ./trace/astar.trace
./main 128 4 0 P_LRU 0 1 ./trace/astar.trace
./main 128 4 0 P_LRU 1 0 ./trace/astar.trace
./main 128 4 0 P_LRU 1 1 ./trace/astar.trace
./main 128 8 0 P_LRU 0 0 ./trace/astar.trace
./main 128 8 0 P_LRU 0 1 ./trace/astar.trace
./main 128 8 0 P_LRU 1 0 ./trace/astar.trace
./main 128 8 0 P_LRU 1 1 ./trace/astar.trace
./main 128 16 0 P_LRU 0 0 ./trace/astar.trace
./main 128 16 0 P_LRU 0 1 ./trace/astar.trace
./main 128 16 0 P_LRU 1 0 ./trace/astar.trace
./main 128 16 0 P_LRU 1 1 ./trace/astar.trace
./main 128 32 0 P_LRU 0 0 ./trace/astar.trace
./main 128 32 0 P_LRU 0 1 ./trace/astar.trace
./main 128 32 0 P_LRU 1 0 ./trace/astar.trace
./main 128 32 0 P_LRU 1 1 ./trace/astar.trace
./main 128 64 0 P_LRU 0 0 ./trace/astar.trace
./main 128 64 0 P_LRU 0 1 ./trace/astar.trace
./main 128 64 0 P_LRU 1 0 ./trace/astar.trace
./main 128 64 0 P_LRU 1 1 ./trace/astar.trace