#include <iostream>
#include <vector>
#include <string>

#include "Board.h"
#include "Piece.h"
#include "Move.h"


Move::Move() = default;


Move::Move(int currentSquare, int targetSquare, const Piece& newPiece, int enPassant)
            : from(currentSquare), to(targetSquare), promoteTo(newPiece), enPassantSquare(enPassant){}


Move::~Move() = default;
