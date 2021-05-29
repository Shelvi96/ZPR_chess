#include <iostream>

#include "Piece.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "MoveGenerator.h"


MoveGenerator::MoveGenerator() = default;


MoveGenerator::~MoveGenerator() = default;


MoveGenerator::MoveGenerator(Board& board) {

    for(int curRow = 0; curRow < HEIGHT; ++curRow) {
        for (int curFile = 0; curFile < WIDTH; ++curFile) {

            int curSquare = curRow * WIDTH + curFile;

            switch (board.getBoard()[curSquare].getPieceType()) {

                case PieceType::PAWN:
                    generatePawnMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::BISHOP:
                    generateBishopMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::KNIGHT:
                    generateKnightMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::ROOK:
                    generateRookMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::QUEEN:
                    generateQueenMoves(board, curSquare, curRow, curFile);
                    break;
                case PieceType::KING:
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
    // check color_ and calculate values
    int nextSquare;
    int doubleSquare;
    int lastRank;
    int secondRank;
    if(board.getBoard()[curSquare].getColor() == Color::WHITE) {
        nextSquare = curSquare + WIDTH;
        doubleSquare = nextSquare + WIDTH;
        lastRank = HEIGHT - 1;
        secondRank = 1;
    } else {
        nextSquare = curSquare - WIDTH;
        doubleSquare = nextSquare - WIDTH;
        lastRank = 0;
        secondRank = HEIGHT - 2;
    }

    // generate basic one square forward moves_
    if(board.getBoard()[nextSquare].getPieceType() == PieceType::EMPTY){
        // PAWN promotes when it reaches last rank
        if(nextSquare / WIDTH == lastRank) {
            promotion(curSquare, nextSquare, Color::WHITE);
        } else {
            moves_.emplace_back(curSquare, nextSquare);
        }
    }

    // generate two squares forward moves_
    if(curRow == secondRank && board.getBoard()[nextSquare].getPieceType() == PieceType::EMPTY
       && board.getBoard()[doubleSquare].getPieceType() == PieceType::EMPTY) {
        // en passant square occurs only in this case
        moves_.emplace_back(curSquare, doubleSquare, Piece(), nextSquare);
    }
}


void MoveGenerator::pawnCaptures(Board& board, int curSquare, int curRow, int curFile) {
    // check color_ and calculate values

    int captureSquares[2][2] = {{0, 1}, {0, -1}};
    int lastRank;
    if(board.getBoard()[curSquare].getColor() == Color::WHITE) {
        captureSquares[0][0] = 1;
        captureSquares[1][0] = 1;
        lastRank = HEIGHT - 1;
    } else {
        captureSquares[0][0] = -1;
        captureSquares[1][0] = -1;
        lastRank = 0;
    }

    for(auto & direction : captureSquares) {
        int nextRow = curRow + direction[0];
        int nextFile = curFile + direction[1];
        int square = nextRow * WIDTH + nextFile;

        if((0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH
            && ((board.getBoard()[square].getColor() != board.getActiveColor() && board.getBoard()[square].getColor() != Color::EMPTY)))) {

            if(nextRow == lastRank) {
                promotion(curSquare, square, board.getActiveColor());
            } else {
                moves_.emplace_back(curSquare, square);
            }
        }
        else if(0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH && square == board.getEnPassantSquare()) {
            moves_.emplace_back(curSquare, square, Piece(), -1, false, true);
        }
    }

}


void MoveGenerator::promotion(int curSquare, int newSquare, Color color) {
    moves_.emplace_back(curSquare, newSquare, Piece(color, PieceType::QUEEN), -1);
    moves_.emplace_back(curSquare, newSquare, Piece(color, PieceType::ROOK), -1);
    moves_.emplace_back(curSquare, newSquare, Piece(color, PieceType::BISHOP), -1);
    moves_.emplace_back(curSquare, newSquare, Piece(color, PieceType::KNIGHT), -1);
}


void MoveGenerator::generateRookMoves(Board& board, int curSquare, int curRow, int curFile) {

    if(board.getBoard()[curSquare].getColor() == board.getActiveColor()) {
        for(auto & direction : rookDirections) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * WIDTH + nextFile;

            while(0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH
                  && board.getBoard()[square].getPieceType() == PieceType::EMPTY) {

                moves_.emplace_back(curSquare, square, Piece(Color::EMPTY, PieceType::EMPTY), -1);
                nextRow = nextRow + direction[0];
                nextFile = nextFile + direction[1];
                square = nextRow * WIDTH + nextFile;
            }

            // captures
            if(0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH
               && board.getBoard()[square].getColor() != board.getActiveColor()) {
                moves_.emplace_back(curSquare, square);
            }
        }
    }
}


void MoveGenerator::generateBishopMoves(Board& board, int curSquare, int curRow, int curFile) {

    if (board.getBoard()[curSquare].getColor() == board.getActiveColor()) {
        for(auto & direction : bishopDirections) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * WIDTH + nextFile;

            while(0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH
                  && board.getBoard()[square].getPieceType() == PieceType::EMPTY) {

                moves_.emplace_back(curSquare, square);
                nextRow = nextRow + direction[0];
                nextFile = nextFile + direction[1];
                square = nextRow * WIDTH + nextFile;
            }

            // captures
            if(0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH
               && board.getBoard()[square].getColor() != board.getActiveColor()) {
                moves_.emplace_back(curSquare, square);
            }
        }
    }
}


void MoveGenerator::generateKnightMoves(Board& board, int curSquare, int curRow, int curFile) {

    if(board.getBoard()[curSquare].getColor() == board.getActiveColor()) {
        // iteration over possible KNIGHT moves_
        for(auto & direction : knightMoves) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * WIDTH + nextFile;
            if(0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH
               && (board.getBoard()[square].getPieceType() == PieceType::EMPTY
                   || board.getBoard()[square].getColor() != board.getActiveColor())) {
                moves_.emplace_back(curSquare, square);
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

        // iteration over possible KING moves_
        for(auto & direction : kingMoves) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * WIDTH + nextFile;
            if(0 <= nextRow && nextRow < HEIGHT && 0 <= nextFile && nextFile < WIDTH
               && (board.getBoard()[square].getPieceType() == PieceType::EMPTY
                   || board.getBoard()[square].getColor() != board.getActiveColor())) {
                moves_.emplace_back(curSquare, square);
            }
        }

        // castling:
        if(board.getActiveColor() == Color::WHITE){
            // WHITE KING castling
            if(board.getCastlingWhiteK() && board.getBoard()[curSquare - 1].getPieceType() == PieceType::EMPTY
                && board.getBoard()[curSquare - 2].getPieceType() == PieceType::EMPTY) {
                moves_.emplace_back(curSquare, curSquare - 2, Piece(), -1, true);
            }
            if(board.getCastlingWhiteQ() && board.getBoard()[curSquare + 1].getPieceType() == PieceType::EMPTY
               && board.getBoard()[curSquare + 2].getPieceType() == PieceType::EMPTY && board.getBoard()[curSquare + 3].getPieceType() == PieceType::EMPTY) {
                moves_.emplace_back(curSquare, curSquare + 2, Piece(), -1, true);
            }
        } else {
            // BLACK KING castling
            if(board.getCastlingBlackK() && board.getBoard()[curSquare - 1].getPieceType() == PieceType::EMPTY
               && board.getBoard()[curSquare - 2].getPieceType() == PieceType::EMPTY) {
                moves_.emplace_back(curSquare, curSquare - 2, Piece(), -1, true);
            }
            if(board.getCastlingBlackQ() && board.getBoard()[curSquare + 1].getPieceType() == PieceType::EMPTY
               && board.getBoard()[curSquare + 2].getPieceType() == PieceType::EMPTY && board.getBoard()[curSquare + 3].getPieceType() == PieceType::EMPTY) {
                moves_.emplace_back(curSquare, curSquare + 2, Piece(), -1, true);
            }
        }

    }
}


std::vector<Move> MoveGenerator::getMoves() {
    return moves_;
}


bool MoveGenerator::isChecking(Board& board) {
    for(auto & move : moves_) {
        if(board.getBoard()[move.getTo()].getPieceType() == PieceType::KING)
            return true;
    }

    return false;
}


Board MoveGenerator::MakeAMove(Board& board, Move move) {
    Board newBoard = board;
    if(newBoard.getBoard()[move.getFrom()].getPieceType() == PieceType::KING) {
        if(newBoard.getActiveColor() == Color::WHITE) {
            newBoard.takeAwayCastlingWhiteK();
            newBoard.takeAwayCastlingWhiteQ();
        } else {
            newBoard.takeAwayCastlingBlackK();
            newBoard.takeAwayCastlingBlackQ();
        }
    } else if(newBoard.getBoard()[move.getFrom()].getPieceType() == PieceType::ROOK) {
        if(newBoard.getActiveColor() == Color::WHITE) {
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
    if(move.getPromoteTo().getPieceType() != PieceType::EMPTY) {
        newBoard.setPiece(move.getTo(), move.getPromoteTo());
        newBoard.setPiece(move.getFrom(), Piece());
    } else if(move.getEnPassantSquare() != -1) {
        newBoard.setEnPassantSquare(move.getEnPassantSquare());
        newBoard.setPiece(move.getTo(), newBoard.getBoard()[move.getFrom()]);
        newBoard.setPiece(move.getFrom(), Piece());
    } else if(move.isItEnPassant()) {
        newBoard.setPiece(move.getTo(), newBoard.getBoard()[move.getFrom()]);
        if(newBoard.getBoard()[move.getFrom()].getColor() == Color::WHITE)
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
    if(newBoard.getActiveColor() == Color::WHITE) {
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
    for(auto & move : moves_) {
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


