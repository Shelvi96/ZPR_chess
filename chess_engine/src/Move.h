/** @file
 * @brief Interface to handle making a move.
 *
 * @author Jakub Jurasz, Konrad Owsikowski
 * @date 01.04.2021
 */
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
        bool enPassant;

    public:
        Move();
        Move(int currentSquare, int targetSquare, const Piece& newPiece = Piece(), int enPassant = -1, bool castling = false, bool enPassant_ = false);
        ~Move();

        int getFrom() const;
        int getTo() const;
        Piece getPromoteTo();
        int getEnPassantSquare() const;
        bool isItCastling() const;
        bool isItEnPassant() const;

        std::string printMove();
};


#endif // MOVE_H
