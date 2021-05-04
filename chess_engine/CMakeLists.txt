cmake_minimum_required(VERSION 3.9)

project(chessengine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared -std=c++11 -Wall -Wextra -fPIC")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../chess_webapp/lib")

include_directories(src)
add_subdirectory(dependencies/pybind11)
pybind11_add_module(chessengine
    src/Piece.h
    src/Piece.cpp
    src/Board.h
    src/Board.cpp
    src/Move.h
    src/Move.cpp
    src/MoveGenerator.h
    src/MoveGenerator.cpp
    src/GameTree.h
    src/GameTree.cpp
    src/api.h
    src/api.cpp
    src/pybind11_wrapper.cpp
 )

target_link_libraries(chessengine PUBLIC)
