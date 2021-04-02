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
    std::cout << "Empty board: " << moves.size() << "\n";
    generatePawnMoves();
    std::cout << "Pawns: " << moves.size() << "\n";
    generateRookMoves();
    std::cout << "Rooks: " << moves.size() << "\n";
    generateBishopMoves();
    std::cout << "Bishops: " << moves.size() << "\n";

//    std::cout << moves.size();
}

// TODO: check and pin handling
// TODO: standard capturing and en passant capturing
void MoveGenerator::generatePawnMoves() {
    // i - current row
    // j - current file
    for(int i = 0; i < currentBoard.getHeight(); ++i) {
        for(int j = 0; j < currentBoard.getWidth(); ++j) {
            int curSquare = i * currentBoard.getWidth() + j;
            
            // move only active sides pawns
            if (currentBoard.getBoard()[curSquare].getPieceType() == PieceType::pawn
                && currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {
                forwardPawnMoves(curSquare, i);
            }
        }
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


void MoveGenerator::promotion(int curSquare, int newSquare, Color color) {
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::queen), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::rook), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::bishop), -1);
    moves.emplace_back(curSquare, newSquare, Piece(color, PieceType::knight), -1);
}


void MoveGenerator::generateRookMoves() {
    // i - current row
    // j - current file
    for(int i = 0; i < currentBoard.getHeight(); ++i) {
        for (int j = 0; j < currentBoard.getWidth(); ++j) {
            int curSquare = i * currentBoard.getWidth() + j;

            if (currentBoard.getBoard()[curSquare].getPieceType() == PieceType::rook && currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {
                // increments [x, y]
                int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

                for(auto & direction : directions) {
                    int curRow = i + direction[0];
                    int curFile = j + direction[1];
                    int square = curRow * currentBoard.getWidth() + curFile;

                    while(0 <= curRow && curRow < currentBoard.getHeight() && 0 <= curFile && curFile < currentBoard.getWidth()
                                && currentBoard.getBoard()[square].getPieceType() == PieceType::empty) {

                        moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
                        curRow = curRow + direction[0];
                        curFile = curFile + direction[1];
                        square = curRow * currentBoard.getWidth() + curFile;
                    }

                    // captures
                    if(0 <= curRow && curRow < currentBoard.getHeight() && 0 <= curFile && curFile < currentBoard.getWidth()
                       && currentBoard.getBoard()[square].getColor() != currentBoard.getActiveColor()) {
                        moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
                    }
                }
            }
        }
    }
}

void MoveGenerator::generateBishopMoves() {
    // i - current row
    // j - current file
    for(int i = 0; i < currentBoard.getHeight(); ++i) {
        for (int j = 0; j < currentBoard.getWidth(); ++j) {
            int curSquare = i * currentBoard.getWidth() + j;

            if (currentBoard.getBoard()[curSquare].getPieceType() == PieceType::bishop && currentBoard.getBoard()[curSquare].getColor() == currentBoard.getActiveColor()) {
                // increments [x, y]
                int directions[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

                for(auto & direction : directions) {
                    int curRow = i + direction[0];
                    int curFile = j + direction[1];
                    int square = curRow * currentBoard.getWidth() + curFile;

                    while(0 <= curRow && curRow < currentBoard.getHeight() && 0 <= curFile && curFile < currentBoard.getWidth()
                          && currentBoard.getBoard()[square].getPieceType() == PieceType::empty) {

                        moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
                        curRow = curRow + direction[0];
                        curFile = curFile + direction[1];
                        square = curRow * currentBoard.getWidth() + curFile;
                    }

                    // captures
                    if(0 <= curRow && curRow < currentBoard.getHeight() && 0 <= curFile && curFile < currentBoard.getWidth()
                       && currentBoard.getBoard()[square].getColor() != currentBoard.getActiveColor()) {
                        moves.emplace_back(curSquare, square, Piece(Color::empty, PieceType::empty), -1);
                    }
                }
            }
        }
    }
}


void dupsko() {
    Board board("rnbqkbnr/1ppppp1p/6p1/p7/P3P3/6P1/1PPP1P1P/RNBQKBNR w KQkq - 0 1");

    board.printBoard();

    MoveGenerator generator(board);
}

