#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Piece.h"
#include "Move.h"


Move::Move() = default;


Move::Move(int currentSquare, int targetSquare, const Piece &newPiece, int enPassant, bool castling)
            : from(currentSquare), to(targetSquare), promoteTo(newPiece), enPassantSquare(enPassant), castling(castling){}


Move::~Move() = default;


int Move::getFrom() const {
    return from;
}

int Move::getTo() const {
    return to;
}

Piece Move::getPromoteTo() {
    return promoteTo;
}

int Move::getEnPassantSquare() const {
    return enPassantSquare;
}

bool Move::isItCastling() const {
    return castling;
}

