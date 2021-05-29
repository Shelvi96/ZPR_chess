#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "Piece.h"

const int WIDTH = 8;
const int HEIGHT = 8;

const int KING_VALUE = 10000;
const int QUEEN_VALUE = 9;
const int ROOK_VALUE = 5;
const int BISHOP_VALUE = 3;
const int KNIGHT_VALUE = 3;
const int PAWN_VALUE = 1;

class Board {
private:
    std::vector<Piece> board_;

    Color activeColor_;
    bool castlingWhiteK_;
    bool castlingWhiteQ_;
    bool castlingBlackK_;
    bool castlingBlackQ_;

    int enPassantSquare_;
    int halfmoveClock_;
    int fullmoveNumber_;

    std::string previousMove_;
    float score_;

    std::string boardToFen();
    std::string colorToFen();
    std::string castlingToFen();
    std::string enPassantToFen();
    std::string halfMoveToFen();
    std::string fullMoveToFen();

public:
    Board();
    explicit Board(const std::string& fen, std::string prevMove = "00,00");
    ~Board();

    std::vector<Piece>& getBoard();
    void setPiece(int square, const Piece& piece);

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

    float getScore() const;
    float eval();

    void printBoard();
};


template<typename A>
void printVector(std::vector<A> &T);


#endif // BOARD_H