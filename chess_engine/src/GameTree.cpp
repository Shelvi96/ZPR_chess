#include "GameTree.h"


Node::Node() = default;


Node::Node(const Board& board, int depth) {
    board_ = board;
    depth_ = depth;
}


Node::~Node() = default;


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


void Node::generateMoves() {
    moveGenerator_ = MoveGenerator(board_);
}


MoveGenerator Node::getMoveGenerator() {
    return moveGenerator_;
}


Node* GameTree::getRoot() {
    return root;
}


GameTree::GameTree() = default;


GameTree::GameTree(Board board) {
    root = new Node(board, 0);
}


GameTree::~GameTree() = default;


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


std::string GameTree::getBestMove(int depth, bool maximizingPlayer) {
    generateTree(1);
    std::string ret;
    if(maximizingPlayer) {
        float maxEval = -INFINITY;
        int best_move = 0;
        float alpha = -INFINITY;
        float beta = INFINITY;
        for(int i = 0; i < int(root->getChildren().size()); ++i) {
            float eval = alphaBeta(root->getChildren()[i], depth - 1, alpha, beta, false);
            if(eval > maxEval) {
                best_move = i;
                maxEval = eval;
            }
            alpha = std::max(maxEval, beta);
            if(alpha <= beta)
                break;
        }
        ret = root->getChildren()[best_move]->getBoard().getFenString();
    } else {
        float minEval = INFINITY;
        int best_move = 0;
        float alpha = -INFINITY;
        float beta = INFINITY;
        for(int i = 0; i < int(root->getChildren().size()); ++i) {
            float eval = alphaBeta(root->getChildren()[i], depth - 1, alpha, beta, true);
            if(eval < minEval){
                best_move = i;
                minEval = eval;

            }
            beta = std::min(minEval, beta);
            if(beta <= alpha)
                break;
        }
        ret = root->getChildren()[best_move]->getBoard().getFenString();
    }

    deleteTree(root);
    return ret;
}


float GameTree::alphaBeta(Node *node, int depth, float alpha, float beta, bool maximizingPlayer) {
    if(depth == 0)
        return node->getBoard().eval();

    node->generateMoves();

    if(maximizingPlayer) {
        Node *temp;
        float maxEval = -INFINITY;
        for(auto &move : node->getMoveGenerator().getMoves()) {
            if(move.isItCastling())
                temp = new Node(node->getMoveGenerator().MakeCastlingMove(node->getBoard(), move), 0);
            else
                temp = new Node(node->getMoveGenerator().MakeAMove(node->getBoard(), move), 0);


            float eval = alphaBeta(temp, depth - 1, alpha, beta, false);
            maxEval = std::max(alpha, eval);
            alpha = std::max(alpha, maxEval);
            if(alpha >= beta) {
                delete temp;
                return maxEval;
            }
        }
        delete temp;
        return maxEval;
    } else {
        Node *temp;
        float minEval = INFINITY;
        for(auto &move : node->getMoveGenerator().getMoves()) {
            if(move.isItCastling())
                temp = new Node(node->getMoveGenerator().MakeCastlingMove(node->getBoard(), move), 0);
            else
                temp = new Node(node->getMoveGenerator().MakeAMove(node->getBoard(), move), 0);

            float eval = alphaBeta(temp, depth - 1, alpha, beta, true);
            minEval = std::min(beta, eval);
            beta = std::min(beta, minEval);
            if(beta <= alpha) {
                delete temp;
                return minEval;
            }
        }
        delete temp;
        return minEval;
    }
}
