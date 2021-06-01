/** @file
 * @brief Interface to handle game tree building and decision making.
 *
 * @author Jakub Jurasz, Konrad Owsikowski
 * @date 20.04.2021
 */
#ifndef GAMETREE_H
#define GAMETREE_H

#include <iostream>
#include <vector>

#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "MoveGenerator.h"


const float INFINITY = 1e10;

/** @brief Class to represent game tree node.
 * Class to represent game tree node.
 */
class Node {
private:
    Board board_;
    MoveGenerator moveGenerator_;
    std::vector<Node*> children_;
    int depth_;

public:
    /** @brief Default constructor.
     *  Default constructor.
     */
    Node();

    /** @brief Custom constructor.
     *  Custom constructor.
     *  @param[in] board - board at GameTree root.
     *  @param[in] depth - maximum tree depth when generating tree.
     */
    Node(const Board& board, int depth);

    /** @brief Default destructor.
     *  Default destructor.
     */
    ~Node();

    /** @brief
     *
     *  @param[in]
     *  @return
     */
    Board &getBoard();

    /** @brief
     *
     *  @param[in]
     *  @return
     */
    void generateChildren(int maxDepth);

    /** @brief
     *
     *  @param[in]
     *  @return
     */
    int numberOfChildren();

    /** @brief
     *
     *  @param[in]
     *  @return
     */
    std::vector<Node*> &getChildren();

    /** @brief
     *
     *  @param[in]
     *  @return
     */
    void generateMoves();

    /** @brief
     *
     *  @param[in]
     *  @return
     */
    MoveGenerator getMoveGenerator();
};

/** @brief Class to represent game tree.
 * Class to represent game tree.
 */
class GameTree {
private:
    Node* root{};
    float alphaBeta(Node *node, int depth, float alpha, float beta, bool maximizingPlayer);

public:
    /** @brief Default constructor.
     *  Default constructor.
     */
    GameTree();

    /** @brief Default constructor.
     *  Default constructor.
     */
    GameTree(Board board);

    /** @brief Default destructor.
     *  Default destructor.
     */
    ~GameTree();

    /** @brief Returns root node of game tree.
     *  Returns root node of game tree.
     *  @return Root node of game tree.
     */
    Node* getRoot();

    /** @brief Generates game tree.
     *  Generates game tree of given depth.
     *  @param[in] depth    - tree depth
     */
    void generateTree(int depth);

    /** @brief Deletes node's subtree.
     *  Deletes node's subtree.
     *  @param[in] node - root node of subtree to be deleted
     */
    void deleteTree(Node* node);

    /** @brief Returns number of valid boards.
     *  Returns number of valid boards in a tree of given depth rooted in node.
     *  @param[in] node     - root node
     *  @param[in] level    - max tree depth
     *  @return Number of valid boards.
     */
    int countPossibleBoards(Node* node, int level);

    /** @brief Returns best move.
     *  Returns best move in current game tree.
     *  @param[in] depth            - max tree depth to be considered
     *  @param[in] maximizingPlayer - is player maximizing or minimizing
     *  @return Best move.
     */
    std::string getBestMove(int depth, bool maximizingPlayer);
};


#endif //GAMETREE_H
