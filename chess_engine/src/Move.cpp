#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Piece.h"
#include "Move.h"


Move::Move() = default;


Move::Move(int currentSquare, int targetSquare, const Piece &newPiece, int enPassant, bool castling, bool enPassant_)
            : from(currentSquare), to(targetSquare), promoteTo(newPiece), enPassantSquare(enPassant), castling(castling), enPassant(enPassant_){}


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

bool Move::isItEnPassant() const {
    return enPassant;
}

std::string Move::printMove() {
    std::string file = "hgfedcba";
    std::string row = "12345678";
    std::string ret = "";
    ret += file[from % 8];
    ret += row[from / 8];
    ret += ",";
    ret += file[to % 8];
    ret += row[to / 8];
    return ret;
}