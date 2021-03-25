#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "piece.h"

class Board {
    private:
        std::vector<Piece> board;
        
    public:
        Board();
        Board(std::string fen);
        ~Board();
        

        void printBoard();
};


#endif // BOARD_H