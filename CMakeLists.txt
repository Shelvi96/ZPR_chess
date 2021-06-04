cmake_minimum_required(VERSION 3.19)
project(ZPR_chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(chess_engine/src)

add_executable(ZPR_chess
        chess_engine/src/api.cpp
        chess_engine/src/api.h
        chess_engine/src/Board.cpp
        chess_engine/src/Board.h
        chess_engine/src/GameTree.cpp
        chess_engine/src/GameTree.h
        chess_engine/src/Move.cpp
        chess_engine/src/Move.h
        chess_engine/src/MoveGenerator.cpp
        chess_engine/src/MoveGenerator.h
        chess_engine/src/Piece.cpp
        chess_engine/src/Piece.h
        chess_engine/src/pybind11_wrapper.cpp)
