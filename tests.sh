#!/bin/bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Debug
make test -j 20
cd ..