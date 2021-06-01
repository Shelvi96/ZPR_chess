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

class Node {
private:
    Board board_;
    MoveGenerator moveGenerator_;
    std::vector<Node*> children_;
    int depth_;
public:
    Node();
    explicit Node(const Board& board, int depth);
    Board &getBoard();
    void generateChildren(int maxDepth);
    int numberOfChildren();
    std::vector<Node*> &getChildren();
    void generateMoves();
    MoveGenerator getMoveGenerator();
};


class GameTree {
private:
    Node* root{};

public:
    Node* getRoot();
    GameTree();
    explicit GameTree(Board board);
    void generateTree(int depth);
    void deleteTree(Node* node);
    int countPossibleBoards(Node* node, int level);
    std::string getBestMove(int depth, bool maximizingPlayer);
    float alphaBeta(Node *node, int depth, float alpha, float beta, bool maximizingPlayer);
};


#endif //GAMETREE_H
