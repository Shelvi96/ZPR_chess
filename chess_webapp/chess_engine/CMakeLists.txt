cmake_minimum_required(VERSION 3.9)

project(chess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
set(PYTHON_INCLUDE "/usr/include/python3.8")

find_package(PythonLibs REQUIRED)

add_library(chesslib SHARED 
    src/piece.h
    src/piece.cpp
    src/board.h
    src/board.cpp
    src/move.h
    src/move.cpp
    )

include_directories(${PYTHON_INCLUDE_DIRS})

target_link_libraries(chesslib python3.8)

target_link_libraries(chesslib ${PYTHON_LIBRARIES})
