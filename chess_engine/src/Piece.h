/** @file
 * @brief Interface to represent a chess piece.
 *
 * @author Jakub Jurasz, Konrad Owsikowski
 * @date 25.03.2021
 */
#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>

/** @brief Enum type to represent piece color.
 * Enum type to represent piece color.
 *
 */
enum class Color {
    BLACK, WHITE, EMPTY
};

/** @brief Enum type to represent chess piece.
 * Enum type to represent chess piece.
 *
 */
enum class PieceType {
    EMPTY, KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN
};

/** @brief Class to represent chess piece.
 * Class to represent chess piece.
 *
 */
class Piece {
private:
    Color color_;
    PieceType pieceType_;

public:
    /** @brief Default constructor.
     *  Default constructor.
     */
    Piece();

    /** @brief Custom constructor.
     *  Custom constructor.
     *  @param[in] color    - piece color.
     *  @param[in] pieceType    - type of piece
     */
    Piece(Color color, PieceType pieceType);

    /** @brief Default destructor.
     *  Default destructor.
     */
    ~Piece();

    /** @brief Returns piece color.
     * Returns piece color.
     * @return Piece color.
     */
    Color getColor() const;

    /** @brief Returns type of piece.
     * Returns type of piece.
     * @return Type of piece.
     */
    PieceType getPieceType() const;

    /** @brief Sets piece type and color.
     * Sets piece type and color.
     * @param[in] color     - piece color
     * @param[in] pieceType - piece type
     */
    void setPiece(Color& color, PieceType& pieceType);

    /** @brief Sets piece type.
     * Sets piece type.
     * @param[in] pieceType - piece type
     */
    void setPieceType(PieceType& pieceType);

    /** @brief Sets piece color.
     * Sets piece color.
     * @param[in] color     - piece color
     */
    void setColor(Color& color);

    /** @brief Returns piece's FEN symbol.
     * Returns piece's symbol representation in FEN notation.
     * @return Piece symbol.
     */
    char getFenSymbol() const;
};


#endif // PIECE_H
