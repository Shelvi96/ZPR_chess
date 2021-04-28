#include <pybind11/pybind11.h>
#include <api.h>

PYBIND11_MODULE(pybind11_chessengine, m) {
    m.def("getNextFen", &getNextFen, "A function that returns next fen string");
}