#ifndef GLUPIEGOWNO_GAMETREE_H
#define GLUPIEGOWNO_GAMETREE_H

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
    std::vector<Node> children;
    int depth_;
public:
    Node();
    explicit Node(const Board& board, int depth);

    Board &getBoard();
    void generateChildren(int maxDepth);
    int numberOfChildren();
    std::vector<Node> &getChildren();
};



class GameTree {
private:
    Node root;

public:
    Node getRoot();
    explicit GameTree(Board board);
    void generateTree(int depth);
};

void dupsko();

#endif //GLUPIEGOWNO_GAMETREE_H
