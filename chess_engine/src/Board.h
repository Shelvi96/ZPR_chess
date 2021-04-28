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

    std::string previousMove;

public:
    Board();
    explicit Board(const std::string& fen, std::string prevMove = "00,00");
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

    void setPreviousMove(std::string prevMove);
    std::string getPreviousMove();
    std::string getFenString();

    void printBoard();
};


template<typename A>
void printVector(std::vector<A> &T);


#endif // BOARD_H