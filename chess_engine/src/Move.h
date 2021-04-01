#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Piece.h"


class Move {

    private:
        int from;
        int to;
        Piece promoteTo;
        int enPassantSquare;


    public:
        Move();
        Move(int currentSquare, int newSquare, const Piece& newPiece, int enPassant);
        ~Move();
};


#endif // MOVE_H
