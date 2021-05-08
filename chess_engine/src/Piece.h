#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>


enum class Color {
    BLACK, WHITE, EMPTY
};


enum class PieceType {
    EMPTY, KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN
};


class Piece {
private:
    Color color_;
    PieceType pieceType_;

public:
    Piece();
    Piece(Color color, PieceType pieceType);
    ~Piece();
    Color getColor() const;
    PieceType getPieceType() const;

    void setPiece(Color& color, PieceType& pieceType);
    void setPieceType(PieceType& pieceType);
    void setColor(Color& color);

    char getFenSymbol() const;
    void printPiece() const;
};


#endif // PIECE_H
