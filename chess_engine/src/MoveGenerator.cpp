#include <iostream>

#include "Piece.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "MoveGenerator.h"


MoveGenerator::MoveGenerator() = default;


MoveGenerator::~MoveGenerator() = default;


MoveGenerator::MoveGenerator(Board& board) {
//    currentBoard = board;

    for(int curRow = 0; curRow < board.getHeight(); ++curRow) {
        for (int curFile = 0; curFile < board.getWidth(); ++curFile) {

            int curSquare = curRow * board.getWidth() + curFile;

            switch (board.getBoard()[curSquare].getPieceType()) {

                case PieceType::pawn:
                    generatePawnMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::bishop:
                    generateBishopMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::knight:
                    generateKnightMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::rook:
                    generateRookMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::queen:
                    generateQueenMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::king:
                    generateKingMoves(board, curSquare, curRow, curFile);
                    break;
                default:
                    break;
            }
        }
    }
}


void MoveGenerator::generatePawnMoves(Board& board, int curSquare, int curRow, int curFile) {
    if (board.getBoard()[curSquare].getColor() == board.getActiveColor()) {
        forwardPawnMoves(board, curSquare, curRow);
        pawnCaptures(board, curSquare, curRow, curFile);
    }
}


void MoveGenerator::forwardPawnMoves(Board& board, int curSquare, int curRow) {
    // check color and calculate values
    int nextSquare;
    int doubleSquare;
    int lastRank;
    int secondRank;
    if(board.getBoard()[curSquare].getColor() == Color::white) {
        nextSquare = curSquare + board.getWidth();
        doubleSquare = nextSquare + board.getWidth();
        lastRank = board.getHeight() - 1;
        secondRank = 1;
    } else {
        nextSquare = curSquare - board.getWidth();
        doubleSquare = nextSquare - board.getWidth();
        lastRank = 0;
        secondRank = board.getHeight() - 2;
    }

    // generate basic one square forward moves
    if(board.getBoard()[nextSquare].getPieceType() == PieceType::empty){
        // pawn promotes when it reaches last rank
        if(nextSquare / board.getWidth() == lastRank) {
            promotion(curSquare, nextSquare, Color::white);
        } else {
            moves.emplace_back(curSquare, nextSquare);
        }
    }

    // generate two squares forward moves
    if(curRow == secondRank && board.getBoard()[nextSquare].getPieceType() == PieceType::empty
       && board.getBoard()[doubleSquare].getPieceType() == PieceType::empty) {
        // en passant square occurs only in this case
        moves.emplace_back(curSquare, doubleSquare, Piece(), nextSquare);
    }
}


void MoveGenerator::pawnCaptures(Board& board, int curSquare, int curRow, int curFile) {
    // check color and calculate values

    int captureSquares[2][2] = {{0, 1}, {0, -1}};
    int lastRank;
    if(board.getBoard()[curSquare].getColor() == Color::white) {
        captureSquares[0][0] = 1;
        captureSquares[1][0] = 1;
        lastRank = board.getHeight() - 1;
    } else {
        captureSquares[0][0] = -1;
        captureSquares[1][0] = -1;
        lastRank = 0;
    }

    for(auto & direction : captureSquares) {
        int nextRow = curRow + direction[0];
        int nextFile = curFile + direction[1];
        int square = nextRow * board.getWidth() + nextFile;
//        board.getBoard()[curSquare].printPiece();
//        std::cout << curSquare << " " << square << "\n";

        if((0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth()
            && ((board.getBoard()[square].getColor() != board.getActiveColor() && board.getBoard()[square].getColor() != Color::empty)))) {

            if(nextRow == lastRank) {
                promotion(curSquare, square, board.getActiveColor());
            } else {
                moves.emplace_back(curSquare, square);
            }
        }
        else if(0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth() && square == board.getEnPassantSquare()) {
            moves.emplace_back(curSquare, square, Piece(), -1, false, true);
        }
    }

}


void MoveGenerator::promotion(int curSquare, int newSquare, Color color) {
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::queen), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::rook), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::bishop), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::knight), -1);
}


void MoveGenerator::generateRookMoves(Board& board, int curSquare, int curRow, int curFile) {

    if(board.getBoard()[curSquare].getColor() == board.getActiveColor()) {
        for(auto & direction : rookDirections) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * board.getWidth() + nextFile;

            while(0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth()
                  && board.getBoard()[square].getPieceType() == PieceType::empty) {

                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
                nextRow = nextRow + direction[0];
                nextFile = nextFile + direction[1];
                square = nextRow * board.getWidth() + nextFile;
            }

            // captures
            if(0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth()
               && board.getBoard()[square].getColor() != board.getActiveColor()) {
                moves.emplace_back(curSquare, square);
            }
        }
    }
}


void MoveGenerator::generateBishopMoves(Board& board, int curSquare, int curRow, int curFile) {

    if (board.getBoard()[curSquare].getColor() == board.getActiveColor()) {
        for(auto & direction : bishopDirections) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * board.getWidth() + nextFile;

            while(0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth()
                  && board.getBoard()[square].getPieceType() == PieceType::empty) {

                moves.emplace_back(curSquare, square);
                nextRow = nextRow + direction[0];
                nextFile = nextFile + direction[1];
                square = nextRow * board.getWidth() + nextFile;
            }

            // captures
            if(0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth()
               && board.getBoard()[square].getColor() != board.getActiveColor()) {
                moves.emplace_back(curSquare, square);
            }
        }
    }
}


void MoveGenerator::generateKnightMoves(Board& board, int curSquare, int curRow, int curFile) {

    if(board.getBoard()[curSquare].getColor() == board.getActiveColor()) {

        // iteration over possible knight moves
        for(auto & direction : knightMoves) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * board.getWidth() + nextFile;
            if(0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth()
               && (board.getBoard()[square].getPieceType() == PieceType::empty
                   || board.getBoard()[square].getColor() != board.getActiveColor())) {
                moves.emplace_back(curSquare, square);
            }
        }
    }
}


void MoveGenerator::generateQueenMoves(Board& board, int curSquare, int curRow, int curFile) {
    generateBishopMoves(board, curSquare, curRow, curFile);
    generateRookMoves(board, curSquare, curRow, curFile);
}


void MoveGenerator::generateKingMoves(Board& board, int curSquare, int curRow, int curFile) {
    if(board.getBoard()[curSquare].getColor() == board.getActiveColor()) {

        // iteration over possible king moves
        for(auto & direction : kingMoves) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * board.getWidth() + nextFile;
            if(0 <= nextRow && nextRow < board.getHeight() && 0 <= nextFile && nextFile < board.getWidth()
               && (board.getBoard()[square].getPieceType() == PieceType::empty
                   || board.getBoard()[square].getColor() != board.getActiveColor())) {
                moves.emplace_back(curSquare, square);
            }
        }

        // castling:
        if(board.getActiveColor() == Color::white){
            // white king castling
            if(board.getCastlingWhiteK() && board.getBoard()[curSquare - 1].getPieceType() == PieceType::empty
                && board.getBoard()[curSquare - 2].getPieceType() == PieceType::empty) {
                moves.emplace_back(curSquare, curSquare - 2, Piece(), -1, true);
            }
            if(board.getCastlingWhiteQ() && board.getBoard()[curSquare + 1].getPieceType() == PieceType::empty
               && board.getBoard()[curSquare + 2].getPieceType() == PieceType::empty && board.getBoard()[curSquare + 3].getPieceType() == PieceType::empty) {
                moves.emplace_back(curSquare, curSquare + 2, Piece(), -1, true);
            }
        } else {
            // black king castling
            if(board.getCastlingBlackK() && board.getBoard()[curSquare - 1].getPieceType() == PieceType::empty
               && board.getBoard()[curSquare - 2].getPieceType() == PieceType::empty) {
                moves.emplace_back(curSquare, curSquare - 2, Piece(), -1, true);
            }
            if(board.getCastlingBlackQ() && board.getBoard()[curSquare + 1].getPieceType() == PieceType::empty
               && board.getBoard()[curSquare + 2].getPieceType() == PieceType::empty && board.getBoard()[curSquare + 3].getPieceType() == PieceType::empty) {
                moves.emplace_back(curSquare, curSquare + 2, Piece(), -1, true);
            }
        }

    }
}


std::vector<Move> MoveGenerator::getMoves() {
    return moves;
}


bool MoveGenerator::isChecking(Board& board) {
    for(auto & move : moves) {
        if(board.getBoard()[move.getTo()].getPieceType() == PieceType::king)
            return true;
    }

    return false;
}


Board MoveGenerator::MakeAMove(Board& board, Move move) {
    Board newBoard = board;
    if(newBoard.getBoard()[move.getFrom()].getPieceType() == PieceType::king) {
        if(newBoard.getActiveColor() == Color::white) {
            newBoard.takeAwayCastlingWhiteK();
            newBoard.takeAwayCastlingWhiteQ();
        } else {
            newBoard.takeAwayCastlingBlackK();
            newBoard.takeAwayCastlingBlackQ();
        }
    } else if(newBoard.getBoard()[move.getFrom()].getPieceType() == PieceType::rook) {
        if(newBoard.getActiveColor() == Color::white) {
            // TODO: do it smarter
            if(4 < move.getFrom())
                newBoard.takeAwayCastlingWhiteQ();
            else
                newBoard.takeAwayCastlingWhiteK();

        } else {
            if(4 < move.getFrom())
                newBoard.takeAwayCastlingBlackQ();
            else
                newBoard.takeAwayCastlingBlackK();
        }
    }
    newBoard.changeActiveColor();
    newBoard.setEnPassantSquare(-1);
    if(move.getPromoteTo().getPieceType() != PieceType::empty) {
        newBoard.setPiece(move.getTo(), move.getPromoteTo());
        newBoard.setPiece(move.getFrom(), Piece());
    } else if(move.getEnPassantSquare() != -1) {
        newBoard.setEnPassantSquare(move.getEnPassantSquare());
        newBoard.setPiece(move.getTo(), newBoard.getBoard()[move.getFrom()]);
        newBoard.setPiece(move.getFrom(), Piece());
    } else if(move.isItEnPassant()) {
        newBoard.setPiece(move.getTo(), newBoard.getBoard()[move.getFrom()]);
        if(newBoard.getBoard()[move.getFrom()].getColor() == Color::white)
            newBoard.setPiece(move.getTo() - 8, Piece());
        else
            newBoard.setPiece(move.getTo() + 8, Piece());
        newBoard.setPiece(move.getFrom(), Piece());
    } else if(move.isItCastling()) {
        // for validation purpose
        for(int i = move.getTo(); i < move.getFrom() + 1; ++i)
            newBoard.setPiece(i, newBoard.getBoard()[move.getFrom()]);
        for(int i = move.getTo(); i > move.getFrom() - 1; --i)
            newBoard.setPiece(i, newBoard.getBoard()[move.getFrom()]);
    } else {
        newBoard.setPiece(move.getTo(), newBoard.getBoard()[move.getFrom()]);
        newBoard.setPiece(move.getFrom(), Piece());
    }


    newBoard.setPreviousMove(move.printMove());
    return newBoard;
}


Board MoveGenerator::MakeCastlingMove(Board& board, Move move) {
    Board newBoard = board;
    if(newBoard.getActiveColor() == Color::white) {
        newBoard.takeAwayCastlingWhiteK();
        newBoard.takeAwayCastlingWhiteQ();
    } else {
        newBoard.takeAwayCastlingBlackK();
        newBoard.takeAwayCastlingBlackQ();
    }
    newBoard.changeActiveColor();
    if(move.getTo() > move.getFrom()) {
        newBoard.setPiece(move.getTo() - 1, newBoard.getBoard()[move.getFrom() + 4]);
        newBoard.setPiece(move.getFrom() + 4, Piece());
    } else {
        newBoard.setPiece(move.getTo() + 1, newBoard.getBoard()[move.getFrom() - 3]);
        newBoard.setPiece(move.getFrom() - 3, Piece());
    }
    newBoard.setPiece(move.getTo(), newBoard.getBoard()[move.getFrom()]);
    newBoard.setPiece(move.getFrom(), Piece());
    newBoard.setEnPassantSquare(-1);
    newBoard.setPreviousMove(move.printMove());
    return newBoard;
}


bool MoveGenerator::isMoveLegal(Board board) {
    MoveGenerator newMoves = MoveGenerator(board);


    if(newMoves.isChecking(board))
        return false;


    return true;
}

std::vector<Board> MoveGenerator::getPossibleBoards(Board& board) {
    std::vector<Board> boards;
    for(auto & move : moves) {
        Board temp = MakeAMove(board, move);
        if(isMoveLegal(temp)) {
            if(move.isItCastling()) {
                Board temp = MakeCastlingMove(board, move);
                boards.emplace_back(temp);
            } else {
                boards.emplace_back(temp);
            }
        }
    }
    return boards;
}


