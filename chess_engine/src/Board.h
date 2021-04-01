#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "Piece.h"


class Board {
private:
    std::vector<Piece> board;
    int height;
    int width;

    Color activeColor;
    bool castlingWhiteK;
    bool castlingWhiteQ;
    bool castlingBlackK;
    bool castlingBlackQ;

    int enPassantSquare;
    int halfmoveClock;
    int fullmoveNumber;

public:
    Board();
    explicit Board(const std::string& fen);
    ~Board();

    int getWidth() const;

    int getHeight() const;

    Color getActiveColor();

    std::vector<Piece> getBoard();

    void printBoard();
};


template<typename A>
void printVector(std::vector<A> &T);


#endif // BOARD_H