#include <iostream>
#include <vector>
#include <string>


#include "Piece.h"


using namespace std;


Piece::Piece() {
    pieceType = PieceType::empty;
    color = Color::empty;
}


Piece::Piece(Color setColor, PieceType setPieceType) {
    color = setColor;
    pieceType = setPieceType;
}


Piece::~Piece() = default;


Color Piece::getColor() {
    return color;
}


PieceType Piece::getPieceType() {
    return pieceType;
}


void Piece::setPiece(Color& newColor, PieceType& newPieceType) {
    color = newColor;
    pieceType = newPieceType;
}


void Piece::setPieceType(PieceType& newPieceType) {
    pieceType = newPieceType;
}


void Piece::setColor(Color& newColor) {
    color = newColor;
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
