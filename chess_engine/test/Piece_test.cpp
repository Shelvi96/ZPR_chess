#include <boost/test/unit_test.hpp>
#include "../src/Piece.h"

BOOST_AUTO_TEST_SUITE(testPiece)

    BOOST_AUTO_TEST_CASE( Piece_color_type )
    {
        Piece test_piece = Piece(Color::BLACK, PieceType::BISHOP);
        Color cb = Color::BLACK;
        Color cw = Color::WHITE;
        PieceType pr = PieceType::ROOK;
        PieceType pk = PieceType::KING;

        BOOST_CHECK( test_piece.getColor() == Color::BLACK );
        BOOST_CHECK( test_piece.getPieceType() == PieceType::BISHOP );

        test_piece.setPiece(cw, pr);
        BOOST_CHECK( test_piece.getColor() == Color::WHITE );
        BOOST_CHECK( test_piece.getPieceType() == PieceType::ROOK );

        test_piece.setColor(cb);
        BOOST_CHECK( test_piece.getColor() == Color::BLACK );

        test_piece.setPieceType(pk);
        BOOST_CHECK( test_piece.getPieceType() == PieceType::KING );
        BOOST_CHECK( test_piece.getFenSymbol() == 'k' );
    }

BOOST_AUTO_TEST_SUITE_END()