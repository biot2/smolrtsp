#!/bin/bash

mkdir build -p
cd build
cmake ..
scan-build --use-analyzer /usr/bin/clang cmake -DCMAKE_C_COMPILER=clang --build .
