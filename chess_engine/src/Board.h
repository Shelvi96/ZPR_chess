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

    std::vector<Piece>& getBoard();
    void setPiece(int square, const Piece& piece);

    const int& getWidth() const;
    const int& getHeight() const;

    Color& getActiveColor();
    void changeActiveColor();

    bool getCastlingWhiteK() const;
    bool getCastlingWhiteQ() const;
    bool getCastlingBlackK() const;
    bool getCastlingBlackQ() const;
    void takeAwayCastlingWhiteK();
    void takeAwayCastlingWhiteQ();
    void takeAwayCastlingBlackK();
    void takeAwayCastlingBlackQ();

    int getEnPassantSquare() const;
    void setEnPassantSquare(int square);

    void printBoard();
};


template<typename A>
void printVector(std::vector<A> &T);


#endif // BOARD_H