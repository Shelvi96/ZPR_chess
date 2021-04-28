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

    moveGenerator = MoveGenerator(board_);
    std::vector<Board> boards = moveGenerator.getPossibleBoards(board_);


    for(auto & newBoard : boards)
        children.push_back(new Node(newBoard, depth_ + 1));
    if(depth_ < maxDepth) {
        for(auto & child : children)
            child->generateChildren(maxDepth);
    }

}

int Node::numberOfChildren() {
    return children.size();
}

std::vector<Node*> &Node::getChildren() {
    return children;
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


int testfun() {
    GameTree tree(Board("r3k2r/pppq1ppp/2np1n2/2b1p1B1/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 4 8"));

    tree.generateTree(1);

//     for(auto & node : tree.getRoot()->getChildren()) {
//         std::cout << node->getBoard().getPreviousMove() << ": " << tree.countPossibleBoards(node, 1)<< "\n";
//     }

    int generatedMoves = tree.countPossibleBoards(tree.getRoot(), 1);

    tree.deleteTree(tree.getRoot());

    std::cout << "Generated moves: " << generatedMoves << "\n";

    return generatedMoves;

}