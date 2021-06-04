#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "Piece.h"

const int WIDTH = 8;
const int HEIGHT = 8;

// Value of each piece
const int KING_VALUE = 1000;
const int QUEEN_VALUE = 9;
const int ROOK_VALUE = 5;
const int BISHOP_VALUE = 3;
const int KNIGHT_VALUE = 3;
const int PAWN_VALUE = 1;

// Piece-Square tables used for static board evaluation
// Rewards for pieces standing well
// Penalties for pieces standing badly
// source: https://www.chessprogramming.org/Simplified_Evaluation_Function

const float PAWN_TABLE[64] =
    {
            0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
            0.50, 0.50, 0.50, 0.50, 0.50, 0.50, 0.50, 0.50,
            0.10, 0.10, 0.20, 0.30, 0.30, 0.20, 0.10, 0.10,
            0.05, 0.05, 0.10, 0.25, 0.25, 0.10, 0.05, 0.05,
            0.00, 0.00, 0.00, 0.20, 0.20, 0.00, 0.00, 0.00,
            0.05, -0.05, -0.10, 0.00, 0.00, -0.10, -0.05, 0.05,
            0.05, 0.10, 0.10, -0.20, -0.20, 0.10, 0.10, 0.05,
            0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00
    };

const float KNIGHT_TABLE[64] =
        {
                -50.00, -40.00, -30.00, -30.00, -30.00, -30.00, -40.00, -50.00,
                -40.00, -20.00, 0.00, 0.00, 0.00, 0.00, -20.00, -40.00,
                -30.00, 0.00, 10.00, 15.00, 15.00, 10.00, 0.00, -30.00,
                -30.00, 5.00, 15.00, 20.00, 20.00, 15.00, 5.00, -30.00,
                -30.00, 0.00, 15.00, 20.00, 20.00, 15.00, 0.00, -30.00,
                -30.00, 5.00, 10.00, 15.00, 15.00, 10.00, 5.00, -30.00,
                -40.00, -20.00, 0.00, 5.00, 5.00, 0.00, -20.00, -40.00,
                -50.00, -40.00, -30.00, -30.00, -30.00, -30.00, -40.00, -50.00
        };

const float BISHOP_TABLE[64] =
        {
                -20.00, -10.00, -10.00, -10.00, -10.00, -10.00, -10.00, -20.00,
                -10.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, -10.00,
                -10.00, 0.00, 5.00, 10.00, 10.00, 5.00, 0.00, -10.00,
                -10.00, 5.00, 5.00, 10.00, 10.00, 5.00, 5.00, -10.00,
                -10.00, 0.00, 10.00, 10.00, 10.00, 10.00, 0.00, -10.00,
                -10.00, 10.00, 10.00, 10.00, 10.00, 10.00, 10.00, -10.00,
                -10.00, 5.00, 0.00, 0.00, 0.00, 0.00, 5.00, -10.00,
                -20.00, -10.00, -10.00, -10.00, -10.00, -10.00, -10.00, -20.00
        };

const float ROOK_TABLE[64] =
        {
                0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00,
                5.00, 10.00, 10.00, 10.00, 10.00, 10.00, 10.00, 5.00,
                -5.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, -5.00,
                -5.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, -5.00,
                -5.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, -5.00,
                -5.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, -5.00,
                -5.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, -5.00,
                0.00, 0.00, 5.00, 5.00, 5.00, 5.00, 0.00, 0.00
        };

const float QUEEN_TABLE[64] =
        {
                -20.00, -10.00, -10.00, -5.00, -5.00, -10.00, -10.00, -20.00,
                -10.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, -10.00,
                -10.00, 0.00, 5.00, 5.00, 5.00, 5.00, 0.00, -10.00,
                -5.00, 0.00, 5.00, 5.00, 5.00, 5.00, 0.00, -5.00,
                0.00, 0.00, 5.00, 5.00, 5.00, 5.00, 0.00, -5.00,
                -10.00, 5.00, 5.00, 5.00, 5.00, 5.00, 0.00, -10.00,
                -10.00, 0.00, 5.00, 0.00, 0.00, 0.00, 0.00, -10.00,
                -20.00, -10.00, -10.00, -5.00, -5.00, -10.00, -10.00, -20.00

        };

const float KING_TABLE[64] =
        {
                -30.00, -40.00, -40.00, -50.00, -50.00, -40.00, -40.00, -30.00,
                -30.00, -40.00, -40.00, -50.00, -50.00, -40.00, -40.00, -30.00,
                -30.00, -40.00, -40.00, -50.00, -50.00, -40.00, -40.00, -30.00,
                -30.00, -40.00, -40.00, -50.00, -50.00, -40.00, -40.00, -30.00,
                -20.00, -30.00, -30.00, -40.00, -40.00, -30.00, -30.00, -20.00,
                -10.00, -20.00, -20.00, -20.00, -20.00, -20.00, -20.00, -10.00,
                20.00, 20.00, 0.00, 0.00, 0.00, 0.00, 20.00, 20.00,
                20.00, 30.00, 10.00, 0.00, 0.00, 10.00, 30.00, 20.00
        };


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