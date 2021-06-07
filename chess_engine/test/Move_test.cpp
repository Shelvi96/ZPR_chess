#include <boost/test/unit_test.hpp>
#include "../src/Move.h"

BOOST_AUTO_TEST_SUITE(testMove)

    BOOST_AUTO_TEST_CASE( Move_test )
    {
        Move test_move = Move(8, 16, Piece(Color::BLACK, PieceType::QUEEN));
        BOOST_CHECK( test_move.getFrom() == 8 );
        BOOST_CHECK( test_move.getTo() == 16 );
        BOOST_CHECK( test_move.getPromoteTo().getColor() == Color::BLACK );
        BOOST_CHECK( test_move.getPromoteTo().getPieceType() == PieceType::QUEEN );
        BOOST_CHECK( test_move.getEnPassantSquare() == -1);
        BOOST_CHECK( !test_move.isItCastling() );
        BOOST_CHECK( !test_move.isItEnPassant() );
    }

BOOST_AUTO_TEST_SUITE_END()