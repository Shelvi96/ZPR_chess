#include <boost/test/unit_test.hpp>
#include "../src/Piece.h"

BOOST_AUTO_TEST_SUITE(testPiece)

    BOOST_AUTO_TEST_CASE( Piece_test ) {
        Piece test_piece = Piece(Color::BLACK, PieceType::BISHOP);
        BOOST_CHECK( test_piece.getColor() == Color::BLACK );
        BOOST_CHECK( test_piece.getPieceType() == PieceType::BISHOP );
    }

BOOST_AUTO_TEST_SUITE_END()