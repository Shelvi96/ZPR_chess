#!/bin/sh
echo "Chess webapp"
if ! cmake --version &>/dev/null; then
   echo "Cmake required! Install cmake==3.9+"
   exit 1
fi

cd chess_engine
if [ ! -d "./dependencies/pybind11" ];
then
  echo "Downloading pybind11..."
  git clone https://github.com/pybind/pybind11 dependencies/pybind11
fi
cmake .
make
cd ..

if [ ! -d "./chess_webapp/dependencies/flask" ];
then
  echo "Downloading Flask..."
  pip3 install flask --target=./chess_webapp/dependencies/flask
fi
DEPENDENCIES_PATH="./chess_webapp/lib:./chess_webapp/dependencies/flask"

PYTHONPATH=$DEPENDENCIES_PATH python3 run.py