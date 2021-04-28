#include "api.h"
#include "Board.h"
#include "MoveGenerator.h"

std::string getNextFen(std::string fenString, int i_old, int j_old, int i_new, int j_new) {
    Board b = Board(fenString);
    MoveGenerator m = MoveGenerator(b);
    int from = i_old * b.getWidth() + j_old;
    int to = i_new * b.getWidth() + j_new;

    for (auto & move: m.getMoves()) {
        if (move.getFrom() == from && move.getTo() == to) {
            Board temp = m.MakeAMove(b, move);
            if(m.isMoveLegal(temp)) {
                if(move.isItCastling()) {
                    Board temp = m.MakeCastlingMove(b, move);
                    return temp.getFenString();
                } else {
                    return temp.getFenString();
                }
            }
        }
    }
    return "";
}
