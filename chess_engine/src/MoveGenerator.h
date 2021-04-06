
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
    public:
        MoveGenerator();
        explicit MoveGenerator(Board board);
        ~MoveGenerator();

        void generatePawnMoves();
        void forwardPawnMoves(int curSquare, int curRow);
        void promotion(int curSquare, int newSquare, Color color);

        void generateRookMoves();
        void generateBishopMoves();
        void generateKnightMoves();
};

void dupsko();


#endif // MOVEGENERATOR_H
