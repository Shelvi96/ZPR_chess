#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

#include "piece.h"


class Board {
private:
    std::vector<Piece> board;
    int height;
    int width;

public:
    Board();
    explicit Board(const std::string& fen);
    ~Board();


    void printBoard();
};


template<typename A>
void printVector(std::vector<A> &T);


#endif // BOARD_H