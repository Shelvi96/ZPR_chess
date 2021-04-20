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
        children.emplace_back(newBoard, depth_ + 1);
    if(depth_ < maxDepth) {
        for(auto & child : children)
            child.generateChildren(maxDepth);
    }
}

int Node::numberOfChildren() {
    return children.size();
}

std::vector<Node> &Node::getChildren() {
    return children;
}


Node GameTree::getRoot() {
    return root;
}


GameTree::GameTree(Board board) {
    root = Node(board, 0);
}

void GameTree::generateTree(int depth) {
    root.generateChildren(depth);
}




void dupsko() {
    std::cout << "Hello its me\n";

    GameTree tree(Board("r2qkbnr/p1pppppp/bpn5/8/2P1P3/5N2/PP1P1PPP/RNBQK2R b KQkq - 0 1"));

    tree.generateTree(1);
    int generatedMoves = 0;
    for(auto & child : tree.getRoot().getChildren()){
        generatedMoves = generatedMoves + child.numberOfChildren();
    }

    std::cout << generatedMoves << "\n";

}