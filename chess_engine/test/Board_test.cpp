#include <boost/test/unit_test.hpp>
#include "../src/Board.h"

BOOST_AUTO_TEST_SUITE( Board_test )

    BOOST_AUTO_TEST_CASE( Board_color )
    {
        Board test_board( "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" );
        BOOST_CHECK( test_board.getActiveColor() == Color::WHITE );

        test_board.changeActiveColor();
        BOOST_CHECK( test_board.getActiveColor() == Color::BLACK );
    }

    BOOST_AUTO_TEST_CASE( Board_castling )
    {
        Board test_board( "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" );

        BOOST_CHECK( test_board.getCastlingBlackK());
        BOOST_CHECK( test_board.getCastlingWhiteK());
        BOOST_CHECK( test_board.getCastlingBlackQ());
        BOOST_CHECK( test_board.getCastlingWhiteQ());

        test_board.takeAwayCastlingBlackK();
        test_board.takeAwayCastlingWhiteK();
        test_board.takeAwayCastlingBlackQ();
        test_board.takeAwayCastlingWhiteQ();
        BOOST_CHECK( !test_board.getCastlingBlackK());
        BOOST_CHECK( !test_board.getCastlingWhiteK());
        BOOST_CHECK( !test_board.getCastlingBlackQ());
        BOOST_CHECK( !test_board.getCastlingWhiteQ());
    }

    BOOST_AUTO_TEST_CASE( Board_enpassant )
    {
        Board test_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        BOOST_CHECK( test_board.getEnPassantSquare() == -1);
        test_board.setEnPassantSquare(12);
        BOOST_CHECK( test_board.getEnPassantSquare() == 12);
    }

    BOOST_AUTO_TEST_CASE( Board_previous_move )
    {
        Board test_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

        BOOST_CHECK( test_board.getPreviousMove() == "00,00");
        test_board.setPreviousMove("01,00");
        BOOST_CHECK( test_board.getPreviousMove() == "01,00");
    }

    BOOST_AUTO_TEST_CASE( Board_fen )
    {
        Board test_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        BOOST_CHECK( test_board.getFenString() == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }

    BOOST_AUTO_TEST_CASE( Board_eval_score )
    {
        Board test_board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        BOOST_CHECK(test_board.eval() > 0);
    }

BOOST_AUTO_TEST_SUITE_END()