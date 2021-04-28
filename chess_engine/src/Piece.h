#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>


enum class Color {
    black, white, empty
};


enum class PieceType {
    empty, king, queen, rook, bishop, knight, pawn
};


class Piece {
private:
    Color color;
    PieceType pieceType;

public:
    Piece();
    Piece(Color setColor, PieceType setPieceType);
    ~Piece();
    Color getColor();
    PieceType getPieceType();

    void setPiece(Color& newColor, PieceType& newPieceType);
    void setPieceType(PieceType& newPieceType);
    void setColor(Color& newColor);

    char getFenSymbol();
    void printPiece();
};


#endif // PIECE_H
