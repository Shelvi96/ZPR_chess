#!/bin/sh
echo "Chess webapp"
cd chess_engine
cmake CMakeLists.txt
make
cd ..
python3 run.py