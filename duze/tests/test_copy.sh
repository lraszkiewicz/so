#!/bin/sh

TEST_FILE_SIZE=256  # megabytes

./prepare_tests.sh $TEST_FILE_SIZE

echo "Copy test: only_zeroes"
for i in $(seq 1 5)
do
    rm -f tmp
    time cp only_zeroes tmp
done

echo "Copy test: sandwich"
for i in $(seq 1 5)
do
    rm -f tmp
    time cp sandwich tmp
done

echo "Copy test: only_ones"
for i in $(seq 1 5)
do
    rm -f tmp
    time cp only_ones tmp
done
