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
        Piece(Color color, PieceType pieceType);
        ~Piece();
        Color getColor();
        PieceType getPieceType();

        void printPiece();
};


#endif // PIECE_H