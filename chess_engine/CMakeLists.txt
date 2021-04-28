cmake_minimum_required(VERSION 3.9)

project(chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -shared -std=c++11 -Wall -Wextra -fpic")
set(PYTHON_INCLUDE "/usr/include/python3.8")

find_package(PythonLibs REQUIRED)

add_library(chesslib SHARED 
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
    )

include_directories(${PYTHON_INCLUDE_DIRS})

target_link_libraries(chesslib python3.8)

target_link_libraries(chesslib ${PYTHON_LIBRARIES})
