#!/bin/env zsh

PERFS="cpu-cycles,instructions,L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,LLC-load-misses,LLC-store-misses,dTLB-load-misses,dTLB-store-misses"

for ((i=1; i < 12; i++)); do
    integer n=$(( 1 << i ))
    perf stat -e $PERFS ./prog $n
done

