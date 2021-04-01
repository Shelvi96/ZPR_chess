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
    std::cout << "+ Rooks: " << moves.size() << "\n";
    generateBishopMoves();
    std::cout << "+ Bishops: " << moves.size() << "\n";


    // std::cout << moves.size();
}

// TODO: check and pin handling
// TODO: standard capturing and en passant capturing
void MoveGenerator::generatePawnMoves() {
    // i - current row
    // j - current file
    for(int i = 0; i < currentBoard.getHeight(); ++i) {
        for(int j = 0; j < currentBoard.getWidth(); ++j) {
            int curSquare = i * currentBoard.getWidth() + j;

            if (currentBoard.getBoard()[curSquare].getPieceType() == PieceType::pawn) {

                // Forward moves generation
                if(currentBoard.getBoard()[curSquare].getColor() == Color::white && currentBoard.getActiveColor() == Color::white) {

                    // basic one square forward moves
                    int nextSquare = curSquare + currentBoard.getWidth();
                    if(currentBoard.getBoard()[nextSquare].getPieceType() == PieceType::empty){
                        // pawn promotes when it reaches last rank
                        if(i == currentBoard.getHeight() - 2) {
                            promotion(curSquare, nextSquare, Color::white);
                        } else {
                            moves.emplace_back(curSquare, nextSquare, Piece(Color::empty, PieceType::empty), -1);
                        }
                    }

                    // two squares forward moves
                    int doubleSquare = nextSquare + currentBoard.getWidth();
                    if(i == 1 && currentBoard.getBoard()[nextSquare].getPieceType() == PieceType::empty
                        && currentBoard.getBoard()[doubleSquare].getPieceType() == PieceType::empty) {
                        // en passant square occurs only in this case
                        moves.emplace_back(curSquare, nextSquare, Piece(Color::empty, PieceType::empty), nextSquare);
                    }
                }

                if(currentBoard.getBoard()[curSquare].getColor() == Color::black && currentBoard.getActiveColor() == Color::black) {
                    // basic one square forward moves
                    int nextSquare = curSquare - currentBoard.getWidth();
                    if(currentBoard.getBoard()[nextSquare].getPieceType() == PieceType::empty){
                        // pawn promotes when it reaches last rank
                        if(i == 1) {
                            promotion(curSquare, nextSquare, Color::black);
                        } else {
                            moves.emplace_back(curSquare, nextSquare, Piece(Color::empty, PieceType::empty), -1);
                        }
                    }

                    // two squares forward moves
                    int doubleSquare = nextSquare - currentBoard.getWidth();
                    if(i == currentBoard.getHeight() - 2 && currentBoard.getBoard()[nextSquare].getPieceType() == PieceType::empty
                        && currentBoard.getBoard()[doubleSquare].getPieceType() == PieceType::empty) {
                        moves.emplace_back(curSquare, nextSquare, Piece(Color::empty, PieceType::empty), nextSquare);
                    }
                }
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
    Board board("b2k4/8/4B3/2K5/4N3/8/5Rp1/n6R b - - 0 1");

    board.printBoard();

    MoveGenerator generator(board);
}

