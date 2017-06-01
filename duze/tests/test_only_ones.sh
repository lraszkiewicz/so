#!/bin/sh

TEST_FILE_SIZE=256  # megabytes

./prepare_tests.sh $TEST_FILE_SIZE

echo "Copy test: only_ones"
for i in $(seq 1 10)
do
    rm -f tmp
    time cp only_ones tmp
done
