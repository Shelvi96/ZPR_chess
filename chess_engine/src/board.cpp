#include <iostream>
#include <vector>
#include <string>

#include <iterator>
#include <sstream>
#include <numeric>
#include <algorithm>

#include "board.h"
#include "piece.h"


Board::Board() {
    width = 8;
    height = 8;
    board.assign(width * height, Piece());
}


// works for valid FEN
Board::Board(const std::string& fen) {
    width = 8;
    height = 8;

     // split FEN
     std::istringstream iss(fen);
     std::vector<std::string> fenSplit(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

     for (char const &c: fenSplit[0]) {
         switch (c) {
             case 'k':
                 board.emplace_back(Color::black, PieceType::king); break;
             case 'q':
                 board.emplace_back(Color::black, PieceType::queen); break;
             case 'r':
                 board.emplace_back(Color::black, PieceType::rook); break;
             case 'b':
                 board.emplace_back(Color::black, PieceType::bishop); break;
             case 'n':
                 board.emplace_back(Color::black, PieceType::knight); break;
             case 'p':
                 board.emplace_back(Color::black, PieceType::pawn); break;
             case 'K':
                 board.emplace_back(Color::white, PieceType::king); break;
             case 'Q':
                 board.emplace_back(Color::white, PieceType::queen); break;
             case 'R':
                 board.emplace_back(Color::white, PieceType::rook); break;
             case 'B':
                 board.emplace_back(Color::white, PieceType::bishop); break;
             case 'N':
                 board.emplace_back(Color::white, PieceType::knight); break;
             case 'P':
                 board.emplace_back(Color::white, PieceType::pawn); break;
             case '/':
                 break;
             default:
                 if(isdigit(c)) {
                     for(int i = 0; i < (int)c - '0'; ++i) {
                         board.emplace_back(Color::empty, PieceType::empty);
                     }
                 } else {
                     std::cout << "Invalid FEN";
                 }
         }
     }
}


Board::~Board() = default;


void Board::printBoard() {
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j)
            board[i * width + j].printPiece();
        std::cout << "\n";
    }
}


template<typename A>
void printVector(std::vector<A> &T) {
    std::cout << "[";
    for (auto i = T.begin(); i != T.end(); ++i)
        std::cout << *i << ',';
    std::cout << "]\n";
}


