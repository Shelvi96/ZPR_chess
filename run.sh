#!/bin/sh
echo "Chess webapp"
#cd chess_engine
#cmake CMakeLists.txt
#make
#cd ..
invoke build-chess
python3 run.py