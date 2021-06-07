#include "api.h"
#include "Board.h"
#include "MoveGenerator.h"
#include "GameTree.h"


std::string isGameOver(std::string newFen) {
    Board new_b = Board(newFen);
    MoveGenerator new_m = MoveGenerator(new_b);
    int legal_moves = 0;
    for (auto & move: new_m.getMoves()) {
        Board temp = new_m.MakeAMove(new_b, move);
        if (new_m.isMoveLegal(temp)) {
            legal_moves++;
        }
    }
    return legal_moves > 0 ? "KEEP_PLAYING" : "GAME_OVER";
}

std::string getNextFen(std::string fenString, int i_old, int j_old, int i_new, int j_new) {
    Board b = Board(fenString);
    MoveGenerator m = MoveGenerator(b);
    int from = i_old * WIDTH + j_old;
    int to = i_new * WIDTH + j_new;

    for (auto & move: m.getMoves()) {
        if (move.getFrom() == from && move.getTo() == to) {
            Board temp = m.MakeAMove(b, move);
            if(m.isMoveLegal(temp)) {
                if(move.isItCastling()) {
                    temp = m.MakeCastlingMove(b, move);
                }
                GameTree tree(temp);
                return tree.getBestMove(5, false);
            }
        }
    }
    return "";
}
