#include <iostream>
#include <vector>
#include <string>

#include "piece.h"
#include "board.h"
#include "move.h"


void printDupsko() {
    std::cout << "Dupsko\n";

    Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    std::cout << "------------------------------------\n";
    board.printBoard();
    std::cout << "\n------------------------------------\n";
}

// bool isValid(std::string previousBoard, std::string currentBoard) {


// }
