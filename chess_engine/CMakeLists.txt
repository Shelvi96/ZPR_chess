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

find_package(Doxygen)
if (DOXYGEN_FOUND)
  message("Doxygen found. Documentation available")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
  )
else ()
  message("Doxygen not found. Please install doxygen to see the documentation")
endif (DOXYGEN_FOUND)
