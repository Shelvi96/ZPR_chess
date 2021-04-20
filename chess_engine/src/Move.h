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
        bool castling;

    public:
        Move();
        Move(int currentSquare, int targetSquare, const Piece& newPiece = Piece(), int enPassant = -1, bool castling = false);
        ~Move();

        int getFrom() const;
        int getTo() const;
        Piece getPromoteTo();
        int getEnPassantSquare() const;
        bool isItCastling() const;

};


#endif // MOVE_H
