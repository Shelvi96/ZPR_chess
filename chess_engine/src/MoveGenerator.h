
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
        void promotion(int curSquare, int newSquare, Color color);

        void generateRookMoves();
        void generateBishopMoves();
};

void dupsko();


#endif // MOVEGENERATOR_H
