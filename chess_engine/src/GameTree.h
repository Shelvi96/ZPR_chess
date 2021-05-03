#ifndef GAMETREE_H
#define GAMETREE_H

#include <iostream>
#include <vector>

#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "MoveGenerator.h"


class Node {
private:
    Board board_;
    MoveGenerator moveGenerator;
    std::vector<Node*> children;
    int depth_;
public:
    Node();
    explicit Node(const Board& board, int depth);
    Board &getBoard();
    void generateChildren(int maxDepth);
    int numberOfChildren();
    std::vector<Node*> &getChildren();
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
};


#endif //GAMETREE_H
