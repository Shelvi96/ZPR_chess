/** @file
 * @brief Interface to represent chess board.
 *
 * @author Jakub Jurasz, Konrad Owsikowski
 * @date 01.04.2021
 */
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "Piece.h"

const int WIDTH = 8;    /**< Board width */
const int HEIGHT = 8;   /**< Board height */

const int KING_VALUE = 10000;   /**< Value of King Piece */
const int QUEEN_VALUE = 9;      /**< Value of Queen Piece */
const int ROOK_VALUE = 5;       /**< Value of Rook Piece */
const int BISHOP_VALUE = 3;     /**< Value of Bishop Piece */
const int KNIGHT_VALUE = 3;     /**< Value of Knight Piece */
const int PAWN_VALUE = 1;       /**< Value of Pawn Piece */

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

    /** @brief Returns the board.
     * Returns the board as vector of Piece objects.
     * @return Game Board.
     */
    std::vector<Piece>& getBoard();

    /** @brief Sets the piece on a square.
     * Sets the piece on a square.
     * @param[in] square -	square position
     * @param[in] piece -	piece to be set on a square
     */
    void setPiece(int square, const Piece& piece);

    /** @brief Returns color of current player.
     * Returns color of current player.
     * @return Color of current player.
     */
    Color& getActiveColor();

    /** @brief Changes game turn.
     * Changes game turn to the opponent.
     */
    void changeActiveColor();

    /** @brief Returns state of white king-side castling.
     * Returns state of white king-side castling.
     * @return State of white king-side castling.
     */
    bool getCastlingWhiteK() const;

    /** @brief Returns state of white queen-side castling.
     * Returns state of white queen-side castling.
     * @return State of white queen-side castling.
     */
    bool getCastlingWhiteQ() const;

    /** @brief Returns state of black king-side castling.
     * Returns state of black king-side castling.
     * @return State of black king-side castling.
     */
    bool getCastlingBlackK() const;

    /** @brief Returns state of black queen-side castling.
     * Returns state of black queen-side castling.
     * @return State of black queen-side castling.
     */
    bool getCastlingBlackQ() const;

    /** @brief Disables castling possibility.
     * Disables white king-side castling possibility.
     */
    void takeAwayCastlingWhiteK();

    /** @brief Disables castling possibility.
     * Disables white queen-side castling possibility.
     */
    void takeAwayCastlingWhiteQ();

    /** @brief Disables castling possibility.
     * Disables black king-side castling possibility.
     */
    void takeAwayCastlingBlackK();

    /** @brief Disables castling possibility.
     * Disables black queen-side castling possibility.
     */
    void takeAwayCastlingBlackQ();

    /** @brief Returns en passant square position.
     * Returns en passant square position.
     * @return En passant square position.
     */
    int getEnPassantSquare() const;

    /** @brief Sets en passant square position.
     * Sets en passant square position.
     * @param[in] square -	en passant square position.
     */
    void setEnPassantSquare(int square);

    /** @brief Sets previous move.
     * Sets previous move.
     * @param[in] prevMove -	previous move.
     */
    void setPreviousMove(std::string prevMove);

    /** @brief Returns previous move.
     * Returns previous move.
     * @return Previous move.
     */
    std::string getPreviousMove();

    /** @brief Returns board's FEN string.
     * Returns board represented in FEN notation.
     * @return FEN string representing the board.
     */
    std::string getFenString();

    /** @brief Returns score.
     * Returns score.
     * @return Score.
     */
    float getScore() const;

    /** @brief Tworzy nowy element listy.
     * Tworzy nowy element listy i inicjalizuje go wartością x.
     * @param[in] x -	wskaźnik na napis, którym ma zostać zainicjalizowany
     *					nowy element listy.
     * @return Wskaźnik na utworzony element listy.
     */
    float eval();

    /** @brief Prints the board.
     * Prints the board into the console.
     */
    void printBoard();
};

#endif // BOARD_H