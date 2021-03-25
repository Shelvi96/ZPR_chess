#include <iostream>
#include <vector>
#include <string>

#include "board.h"
#include "piece.h"

#define WIDTH 8
#define HEIGHT 8

Board::Board() {
    board.assign(WIDTH * HEIGHT, Piece());
}

Board::Board(std::string fen) {

    
}


Board::~Board() {}


void Board::printBoard() {
    for(int i = 0; i < WIDTH; ++i) {
        for(int j = 0; j < HEIGHT; ++j)
            board[i * WIDTH + j].printPiece();
        std::cout << "\n";
    }
}