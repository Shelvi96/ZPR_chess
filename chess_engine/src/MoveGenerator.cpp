#include <iostream>

#include "Piece.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "MoveGenerator.h"


MoveGenerator::MoveGenerator() = default;

MoveGenerator::~MoveGenerator() = default;

MoveGenerator::MoveGenerator(Board board) {
    currentBoard = board;

    for(int curRow = 0; curRow < currentBoard.getHeight(); ++curRow) {
        for (int curFile = 0; curFile < currentBoard.getWidth(); ++curFile) {

            int curSquare = curRow * currentBoard.getWidth() + curFile;

            switch (currentBoard.getBoard()[curSquare].getPieceType()) {
                case PieceType::pawn:
                    generatePawnMoves(curSquare, curRow, curFile);
                    break;
                case PieceType::bishop:
                    generateBishopMoves(curSquare, curRow, curFile);
                    break;
                case PieceType::knight:
                    generateKnightMoves(curSquare, curRow, curFile);
                    break;
                case PieceType::rook:
                    generateRookMoves(curSquare, curRow, curFile);
                    break;
                case PieceType::queen:
                    generateQueenMoves(curSquare, curRow, curFile);
                    break;
                case PieceType::king:
                    generateKingMoves(curSquare, curRow, curFile);
                    break;
                default:
                    break;
            }
        }
    }
    std::cout << "Possible moves in this position: " << moves.size() << "\n";
}


void MoveGenerator::generatePawnMoves(int curSquare, int curRow, int curFile) {

    if (currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {
        forwardPawnMoves(curSquare, curRow);
        pawnCaptures(curSquare, curRow, curFile);
    }
}


void MoveGenerator::forwardPawnMoves(int curSquare, int curRow) {
    // check color and calculate values
    int nextSquare;
    int doubleSquare;
    int lastRank;
    int secondRank;
    if(currentBoard.getBoard()[curSquare].getColor() == Color::white) {
        nextSquare = curSquare + currentBoard.getWidth();
        doubleSquare = nextSquare + currentBoard.getWidth();
        lastRank = currentBoard.getHeight() - 1;
        secondRank = 1;
    } else {
        nextSquare = curSquare - currentBoard.getWidth();
        doubleSquare = nextSquare - currentBoard.getWidth();
        lastRank = 0;
        secondRank = currentBoard.getHeight() - 2;
    }

    // generate basic one square forward moves
    if(currentBoard.getBoard()[nextSquare].getPieceType() == PieceType::empty){
        // pawn promotes when it reaches last rank
        if(nextSquare / currentBoard.getWidth() == lastRank) {
            promotion(curSquare, nextSquare, Color::white);
        } else {
            moves.emplace_back(curSquare, nextSquare, Piece(Color::empty, PieceType::empty), -1);
        }
    }

    // generate two squares forward moves
    if(curRow == secondRank && currentBoard.getBoard()[nextSquare].getPieceType() == PieceType::empty
       && currentBoard.getBoard()[doubleSquare].getPieceType() == PieceType::empty) {
        // en passant square occurs only in this case
        moves.emplace_back(curSquare, nextSquare, Piece(Color::empty, PieceType::empty), nextSquare);
    }
}


void MoveGenerator::pawnCaptures(int curSquare, int curRow, int curFile) {
    // check color and calculate values

    int captureSquares[2][2] = {{0, 1}, {0, -1}};
    int lastRank;
    if(currentBoard.getBoard()[curSquare].getColor() == Color::white) {
        captureSquares[0][0] = 1;
        captureSquares[1][0] = 1;
        lastRank = currentBoard.getHeight() - 1;
    } else {
        captureSquares[0][0] = -1;
        captureSquares[1][0] = -1;
        lastRank = 0;
    }

    for(auto & direction : captureSquares) {
        int nextRow = curRow + direction[0];
        int nextFile = curFile + direction[1];
        int square = nextRow * currentBoard.getWidth() + nextFile;

        if(0 <= nextRow && nextRow < currentBoard.getHeight() && 0 <= nextFile && nextFile < currentBoard.getWidth()
           && ((currentBoard.getBoard()[square].getColor() != currentBoard.getActiveColor()
           && currentBoard.getBoard()[square].getColor() != Color::empty) || square == currentBoard.getEnPassantSquare())) {

            if(nextRow == lastRank) {
                promotion(curSquare, square, Color::white);
            } else {
                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
            }
        }
    }

}


void MoveGenerator::promotion(int curSquare, int newSquare, Color color) {
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::queen), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::rook), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::bishop), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::knight), -1);
}


void MoveGenerator::generateRookMoves(int curSquare, int curRow, int curFile) {

    if(currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {
        for(auto & direction : rookDirections) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * currentBoard.getWidth() + nextFile;

            while(0 <= nextRow && nextRow < currentBoard.getHeight() && 0 <= nextFile && nextFile < currentBoard.getWidth()
                  && currentBoard.getBoard()[square].getPieceType() == PieceType::empty) {

                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
                nextRow = nextRow + direction[0];
                nextFile = nextFile + direction[1];
                square = nextRow * currentBoard.getWidth() + nextFile;
            }

            // captures
            if(0 <= nextRow && nextRow < currentBoard.getHeight() && 0 <= nextFile && nextFile < currentBoard.getWidth()
               && currentBoard.getBoard()[square].getColor() != currentBoard.getActiveColor()) {
                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
            }
        }
    }
}


void MoveGenerator::generateBishopMoves(int curSquare, int curRow, int curFile) {

    if (currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {
        for(auto & direction : bishopDirections) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * currentBoard.getWidth() + nextFile;

            while(0 <= nextRow && nextRow < currentBoard.getHeight() && 0 <= nextFile && nextFile < currentBoard.getWidth()
                  && currentBoard.getBoard()[square].getPieceType() == PieceType::empty) {

                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
                nextRow = nextRow + direction[0];
                nextFile = nextFile + direction[1];
                square = nextRow * currentBoard.getWidth() + nextFile;
            }

            // captures
            if(0 <= nextRow && nextRow < currentBoard.getHeight() && 0 <= nextFile && nextFile < currentBoard.getWidth()
               && currentBoard.getBoard()[square].getColor() != currentBoard.getActiveColor()) {
                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
            }
        }
    }
}


void MoveGenerator::generateKnightMoves(int curSquare, int curRow, int curFile) {

    if(currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {

        // iteration over possible knight moves
        for(auto & direction : knightMoves) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * currentBoard.getWidth() + nextFile;
            if(0 <= nextRow && nextRow < currentBoard.getHeight() && 0 <= nextFile && nextFile < currentBoard.getWidth()
               && (currentBoard.getBoard()[square].getPieceType() == PieceType::empty
                   || currentBoard.getBoard()[square].getColor() != currentBoard.getActiveColor())) {
                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
            }
        }
    }
}

void MoveGenerator::generateQueenMoves(int curSquare, int curRow, int curFile) {
    generateBishopMoves(curSquare, curRow, curFile);
    generateRookMoves(curSquare, curRow, curFile);
}

// TODO: castling, check, pins
void MoveGenerator::generateKingMoves(int curSquare, int curRow, int curFile) {
    if(currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {

        // iteration over possible knight moves
        for(auto & direction : kingMoves) {
            int nextRow = curRow + direction[0];
            int nextFile = curFile + direction[1];
            int square = nextRow * currentBoard.getWidth() + nextFile;
            if(0 <= nextRow && nextRow < currentBoard.getHeight() && 0 <= nextFile && nextFile < currentBoard.getWidth()
               && (currentBoard.getBoard()[square].getPieceType() == PieceType::empty
                   || currentBoard.getBoard()[square].getColor() != currentBoard.getActiveColor())) {
                moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
            }
        }
    }
}


void dupsko() {
    Board board("1b6/P6P/8/8/8/2n5/1P6/8 w - - 0 1");

    board.printBoard();

    MoveGenerator generator(board);
}

