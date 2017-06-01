#!/bin/sh

if [ -z "$1" ]
then
    echo "Usage: $0 MB_FILE_SIZE"
    exit 1
fi

echo "Compiling gen_test_files.c"
clang -O2 -Wall gen_test_files.c -o gen_test_files
echo "Removing old test files"
rm -f only_zeroes only_ones sandwich tmp
echo "Generating test files ($1 MB)"
./gen_test_files $1
