#!/bin/bash

ITERS=0
NUM_TEST=20
BITS=(1 2 4 8 16 20 22 24 26)
# BITS=(2 4 8 12 14 16)
BIT_LEN=${#BITS[@]}
for (( i = 0; i < ${BIT_LEN}; i++));
do
    printf "BITS: "
    printf ${BITS[$i]}
    printf "\n"
    while [ $ITERS -lt $NUM_TEST ]; do
        let ITERS=ITERS+1;
        time ./a.out ${BITS[$i]};
    done
    let ITERS=0;
    printf "\n"
done  
