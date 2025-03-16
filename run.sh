#!/bin/bash

OUTPUT="main"
CFLAGS="-Wall -Werror"
SRC_FILES=$(find . -name "*.c")
DEBUG=false

# Parse command-line arguments
while getopts "d" opt; do
    case $opt in
    d)
        DEBUG=true
        ;;
    *)
        echo "Usage: $0 [-d]"
        exit 1
        ;;
    esac
done

echo "Compiling project..."

gcc $CFLAGS -o $OUTPUT $SRC_FILES

if [ $? -eq 0 ]; then
    echo "Compilation successful! Output binary: $OUTPUT"
else
    echo "Compilation failed!"
    exit 1
fi

if [ "$DEBUG" = true ]; then
    echo "Running in debug mode with valgrind..."
    valgrind --leak-check=full ./$OUTPUT
else
    ./$OUTPUT
fi

rm -f $OUTPUT
