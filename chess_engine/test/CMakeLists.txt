cmake_minimum_required(VERSION 2.8.11)
project(my_first_test)
enable_testing()

# replace XX with the version you have
set(Boost_ADDITIONAL_VERSIONS ${BOOST_VERSION})

# finds boost, triggers an error otherwise
find_package(Boost ${BOOST_VERSION} REQUIRED COMPONENTS unit_test_framework)

file( GLOB_RECURSE test_cases FOLLOW_SYMLINKS "./*_test.cpp" )
set(VAR 1)
FOREACH( case ${test_cases} )
    add_executable(test_${VAR}
            ../src/Piece.h
            ../src/Piece.cpp
            ../src/Board.h
            ../src/Board.cpp
            ../src/Move.h
            ../src/Move.cpp
            ../src/MoveGenerator.h
            ../src/MoveGenerator.cpp
            ../src/GameTree.h
            ../src/GameTree.cpp
            test_main.cpp
            ${case})

    # indicates the include paths
    target_include_directories(test_${VAR} PRIVATE ${Boost_INCLUDE_DIRS})
    # indicates the shared library variant
    target_compile_definitions(test_${VAR} PRIVATE "BOOST_TEST_DYN_LINK=1")
    # indicates the link paths
    target_link_libraries(test_${VAR} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

    add_test(NAME test_${VAR} COMMAND test_${VAR})

    MATH(EXPR VAR "${VAR}+1")
ENDFOREACH()