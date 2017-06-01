#!/bin/sh

TEST_FILE_SIZE=128  # megabytes

clang -O2 -Wall gen_test_files.c -o gen_test_files
rm -f tmp
for i in $(seq 1 5)
do
    rm -f only_zeroes sandwich only_ones
    time ./gen_test_files $TEST_FILE_SIZE
done
