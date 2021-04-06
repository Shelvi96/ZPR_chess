
#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <iostream>
#include <vector>


#include "Board.h"
#include "Piece.h"
#include "Move.h"


class MoveGenerator {
private:
    std::vector<Move> moves;
    Board currentBoard;
    int rookDirections[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int bishopDirections[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
    int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {-1, -2}, {-1, 2}};
    int kingMoves[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

public:
    MoveGenerator();
    explicit MoveGenerator(Board board);
    ~MoveGenerator();

    void generatePawnMoves(int curSquare, int curRow, int curFile);
    void forwardPawnMoves(int curSquare, int curRow);
    void pawnCaptures(int curSquare, int curRow, int curFile);
    void promotion(int curSquare, int newSquare, Color color);

    void generateRookMoves(int curSquare, int curRow, int curFile);
    void generateBishopMoves(int curSquare, int curRow, int curFile);
    void generateKnightMoves(int curSquare, int curRow, int curFile);
    void generateQueenMoves(int curSquare, int curRow, int curFile);
    void generateKingMoves(int curSquare, int curRow, int curFile);
};

void dupsko();


#endif // MOVEGENERATOR_H
