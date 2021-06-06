#!/bin/sh
echo "Chess webapp"
echo "Building tests..."
cd chess_engine/test
cmake .
make
echo "Tests built. Running tests..."
ctest