#include <iostream>
#include <vector>
#include <string>


#include "piece.h"


using namespace std;


Piece::Piece() {
    pieceType = PieceType::empty;
    color = Color::empty;
}


Piece::Piece(Color color, PieceType pieceType) {
    pieceType = pieceType;
    color = color;
}


Piece::~Piece() {}


Color Piece::getColor() {
    return color;
}


PieceType Piece::getPieceType() {
    return pieceType;
}


std::ostream& operator << (std::ostream& os, const Color& c) {
    const string name[] = {"black", "white", "empty"};

    return os << name[static_cast<std::underlying_type<Color>::type>(c)];
}


std::ostream& operator << (std::ostream& os, const PieceType& p) {
    const string name[] = {"empty", "king", "queen", "rook", "bishop", "knight", "pawn"};

    return os << name[static_cast<std::underlying_type<PieceType>::type>(p)];
}


void Piece::printPiece() {
    cout << "(" << color << "," << pieceType << ")";
}

