#!/bin/env zsh

for ((i=1; i < 12; i++)); do
    integer n=$(( 1 << i ))
    ./nexec $n
done

