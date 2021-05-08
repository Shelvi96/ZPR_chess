
#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <iostream>
#include <vector>

#include "Board.h"
#include "Piece.h"
#include "Move.h"

const int rookDirections[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int bishopDirections[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
const int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {-1, -2}, {-1, 2}};
const int kingMoves[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};


class MoveGenerator {
private:
    std::vector<Move> moves_;

public:
    MoveGenerator();
    explicit MoveGenerator(Board& board);
    ~MoveGenerator();

    void generatePawnMoves(Board& board, int curSquare, int curRow, int curFile);
    void forwardPawnMoves(Board& board, int curSquare, int curRow);
    void pawnCaptures(Board& board, int curSquare, int curRow, int curFile);
    void promotion(int curSquare, int newSquare, Color color);


    void generateRookMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateBishopMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateKnightMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateQueenMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateKingMoves(Board& board, int curSquare, int curRow, int curFile);

    bool isChecking(Board& board);

    std::vector<Move> getMoves();

    Board MakeAMove(Board& board, Move move);
    Board MakeCastlingMove(Board& board, Move move);

    std::vector<Board> getPossibleBoards(Board& board);
    bool isMoveLegal(Board board);

};

#endif // MOVEGENERATOR_H
