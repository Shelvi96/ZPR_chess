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


/** @brief Class to represent chess move.
 * Class to represent chess move.
 */
class Move {
private:
    int from;
    int to;
    Piece promoteTo;
    int enPassantSquare;
    bool castling;
    bool enPassant;

public:
    /** @brief Default constructor.
     *  Default constructor.
     */
    Move();

    /** @brief Custom constructor.
     *  Custom constructor.
     *  @param[in] currentSquare    -   square to make a move from
     *  @param[in] targetSquare     -   square to make a move to
     *  @param[in] newPiece         -   type of new piece when making piece promotion
     *  @param[in] enPassantSquare  -   position of en passant square
     *  @param[in] castling         -   is it castling
     *  @param[in] isEnPassant      -   is it en passant
     */
    Move(int currentSquare, int targetSquare, const Piece& newPiece = Piece(), int enPassantSquare = -1, bool castling = false, bool isEnPassant = false);

    /** @brief Default destructor.
     *  Default destructor.
     */
    ~Move();

    /** @brief Returns position of origin square.
     * Returns position of origin square.
     * @return Position of origin square.
     */
    int getFrom() const;

    /** @brief Returns position of target square.
     * Returns position of target square.
     * @return Position of target square.
     */
    int getTo() const;

    /** @brief Returns promoted piece.
     * Returns promoted piece.
     * @return Promoted piece.
     */
    Piece getPromoteTo();

    /** @brief Returns en passant square position.
     * Returns en passant square position.
     * @return En passant square position.
     */
    int getEnPassantSquare() const;

    /** @brief Returns if move is castling.
     * Returns if move is castling.
     * @return Is move castling.
     */
    bool isItCastling() const;

    /** @brief Returns if move is en passant.
     * Returns if move is en passant.
     * @return Is move en passant.
     */
    bool isItEnPassant() const;

    /** @brief Returns string representation of the move.
     * Returns string representation of the move.
     * @return String representation of the move.
     */
    std::string toString();
};


#endif // MOVE_H
