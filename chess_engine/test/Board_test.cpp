#include <boost/test/unit_test.hpp>
#include "../src/Board.h"

BOOST_AUTO_TEST_SUITE(testBoard)

    BOOST_AUTO_TEST_CASE( Board_test )
    {
        Board test_board( "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" );

        BOOST_CHECK( test_board.getActiveColor() == Color::WHITE );
    }

BOOST_AUTO_TEST_SUITE_END()