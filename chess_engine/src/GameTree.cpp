#include "GameTree.h"


Node::Node() = default;


Node::Node(const Board& board, int depth) {
    board_ = board;
    depth_ = depth;
}


Board &Node::getBoard() {
    return board_;
}

void Node::generateChildren(int maxDepth) {

    moveGenerator_ = MoveGenerator(board_);
    std::vector<Board> boards = moveGenerator_.getPossibleBoards(board_);


    for(auto & newBoard : boards)
        children_.push_back(new Node(newBoard, depth_ + 1));
    if(depth_ < maxDepth) {
        for(auto & child : children_)
            child->generateChildren(maxDepth);
    }

}

int Node::numberOfChildren() {
    return children_.size();
}

std::vector<Node*> &Node::getChildren() {
    return children_;
}


Node* GameTree::getRoot() {
    return root;
}

GameTree::GameTree() = default;

GameTree::GameTree(Board board) {
    root = new Node(board, 0);
}

void GameTree::generateTree(int depth) {
    root->generateChildren(depth);
}

void GameTree::deleteTree(Node *node) {
    for(auto &child : node->getChildren()){
        deleteTree(child);
    }
    delete node;
}

int GameTree::countPossibleBoards(Node *node, int level) {
    if(node == nullptr) {
        return -1;
    }
    if(level == 1) {
        return node->numberOfChildren();
    } else {
        int counter = 0;
        for(auto &child : node->getChildren()){
            counter = counter + countPossibleBoards(child, level - 1);
        }
        return counter;
    }
}

