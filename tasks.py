import invoke
import pathlib


@invoke.task()
def build_chees_engine(c):
    """ Build the shared library for the sample C++ code """
    print("Building C++ Library")
    print(pathlib.Path().absolute())

    invoke.run(
        "g++ -O3 -Wall -Werror -shared -std=c++11 -fPIC chess_engine/src/Piece.h chess_engine/src/Piece.cpp "
        "chess_engine/src/Board.h chess_engine/src/Board.cpp chess_engine/src/Move.h chess_engine/src/Move.cpp "
        "chess_engine/src/MoveGenerator.h chess_engine/src/MoveGenerator.cpp chess_engine/src/GameTree.h "
        "chess_engine/src/GameTree.cpp chess_engine/src/api.h chess_engine/src/api.cpp "
        "-o libchessengine.so "
    )
    print("* Complete")


def compile_python_module(cpp_name, extension_name):
    invoke.run(
        "g++ -O3 -Wall -Werror -shared -std=c++11 -fPIC "
        "`python3 -m pybind11 --includes` "
        "-I /usr/include/python3.8 -I ./chess_engine/src  "
        "{0} "
        "-o {1}`python3.8-config --extension-suffix` "
        "-L. -lchessengine -Wl,-rpath,.".format(cpp_name, extension_name)
    )


@invoke.task(build_chees_engine)
def build_chess(c):
    """ Build the pybind11 wrapper library """
    print("Building PyBind11 Module")
    compile_python_module("./chess_engine/src/pybind11_wrapper.cpp", "pybind11_chessengine")
    print("* Complete")