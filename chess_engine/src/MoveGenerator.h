/** @file
 * @brief Interface to handle move generation and validation.
 *
 * @author Jakub Jurasz, Konrad Owsikowski
 * @date 01.04.2021
 */
#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <iostream>
#include <vector>

#include "Board.h"
#include "Piece.h"
#include "Move.h"

/** @brief Rook's possible move shifts.
 *  Rook's possible move shifts.
 */
const int rookDirections[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

/** @brief Bishop's possible move shifts.
 *  Bishop's possible move shifts.
 */
const int bishopDirections[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

/** @brief Knight's possible move shifts.
 *  Knight's possible move shifts.
 */
const int knightMoves[8][2] = {{2, 1}, {2, -1}, {-2, -1}, {-2, 1}, {1, 2}, {1, -2}, {-1, -2}, {-1, 2}};

/** @brief King's possible move shifts.
 *  King's possible move shifts.
 */
const int kingMoves[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

/** @brief Class for move generation and validation.
 * Class for move generation and validation
 */
class MoveGenerator {
private:
    std::vector<Move> moves_;

    void generatePawnMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateRookMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateBishopMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateKnightMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateQueenMoves(Board& board, int curSquare, int curRow, int curFile);
    void generateKingMoves(Board& board, int curSquare, int curRow, int curFile);

    void forwardPawnMoves(Board& board, int curSquare, int curRow);
    void pawnCaptures(Board& board, int curSquare, int curRow, int curFile);
    void promotion(int curSquare, int newSquare, Color color);

    bool isChecking(Board& board);

public:
    /** @brief Default constructor.
     *  Default constructor.
     */
    MoveGenerator();

    /** @brief Custom constructor.
     *  Custom constructor.
     *  @param[in] board - chess board to generate moves for
     */
    explicit MoveGenerator(Board& board);

    /** @brief Default destructor.
     *  Default destructor.
     */
    ~MoveGenerator();

    /** @brief Returns generated moves.
     * Returns generated moves.
     * @return Generated moves.
     */
    std::vector<Move> getMoves();

    /** @brief Makes a given move for given board.
     * Makes a given move for a given board.
     * @param[in] board - board for which the move should be made
     * @param[in] move  - move to be made on given board
     * @return Board after making the move.
     */
    Board MakeAMove(Board& board, Move move);

    /** @brief Makes a castling move for given board.
     * Makes a castling move for a given board.
     * @param[in] board - board for which the move should be made
     * @param[in] move  - move to be made on given board
     * @return Board after making the move.
     */
    Board MakeCastlingMove(Board& board, Move move);

    /** @brief Returns legality of the move.
     * Returns legality of the move.
     * @param[in] board - board for which the move is being validated
     * @return Board after makin.
     */
    bool isMoveLegal(Board board);

    /** @brief Returns all legal boards.
     * Returns all boards that are created
     * @param[in]
     * @return
     */
    std::vector<Board> getPossibleBoards(Board& board);
};

#endif // MOVEGENERATOR_H
