#include <iostream>
#include <vector>
#include <string>


#include "Piece.h"


using namespace std;


Piece::Piece() {
    pieceType_ = PieceType::EMPTY;
    color_ = Color::EMPTY;
}


Piece::Piece(Color color, PieceType pieceType) {
    color_ = color;
    pieceType_ = pieceType;
}


Piece::~Piece() = default;


Color Piece::getColor() const {
    return color_;
}


PieceType Piece::getPieceType() const {
    return pieceType_;
}


void Piece::setPiece(Color& color, PieceType& pieceType) {
    color_ = color;
    pieceType_ = pieceType;
}


void Piece::setPieceType(PieceType& pieceType) {
    pieceType_ = pieceType;
}


void Piece::setColor(Color& color) {
    color_ = color;
}


std::ostream& operator << (std::ostream& os, const Color& c) {
    const string name[] = {"BLACK", "WHITE", "EMPTY"};

    return os << name[static_cast<std::underlying_type<Color>::type>(c)];
}


std::ostream& operator << (std::ostream& os, const PieceType& p) {
    const string name[] = {"EMPTY", "KING", "QUEEN", "ROOK", "BISHOP", "KNIGHT", "PAWN"};

    return os << name[static_cast<std::underlying_type<PieceType>::type>(p)];
}


char Piece::getFenSymbol() const {
    switch(pieceType_) {
        case PieceType::KING:
            return color_ == Color::WHITE ? 'K' : 'k';
        case PieceType::QUEEN:
            return color_ == Color::WHITE ? 'Q' : 'q';
        case PieceType::ROOK:
            return color_ == Color::WHITE ? 'R' : 'r';
        case PieceType::BISHOP:
            return color_ == Color::WHITE ? 'B' : 'b';
        case PieceType::KNIGHT:
            return color_ == Color::WHITE ? 'N' : 'n';
        case PieceType::PAWN:
            return color_ == Color::WHITE ? 'P' : 'p' ;
        default:
            return '0';
    }
}


void Piece::printPiece() const {
    cout << "(" << color_ << "," << pieceType_ << ")";
}
