#!/bin/bash

set -x

g++ -std=c++17 -Wall -Wpedantic main.cpp Sparse_Matrix.cpp -o sparse_matrix

set +x

if [ $? -eq 0 ]; then
    echo "Build successful! You can run the program using ./sparse_matrix"
else
    echo "Build failed."
fi