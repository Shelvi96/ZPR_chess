#include <iostream>
#include <vector>
#include <string>

#include <iterator>
#include <sstream>
#include <numeric>
#include <algorithm>

#include "Board.h"
#include "Piece.h"


Board::Board() {
    width = 8;
    height = 8;
    board.assign(width * height, Piece());

    activeColor = Color::white;

    castlingWhiteK = true;
    castlingWhiteQ = true;
    castlingBlackK = true;
    castlingBlackQ = true;

    enPassantSquare = -1;
    halfmoveClock = 0;
    fullmoveNumber = 1;
}


// TODO FEN VALIDATION IDK ?
// works for valid FEN
Board::Board(const std::string& fen) {
    width = 8;
    height = 8;

     // split FEN
    std::istringstream iss(fen);
    std::vector<std::string> fenSplit(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    // iteration backwards over part of fen
    for (auto c = fenSplit[0].crbegin() ; c != fenSplit[0].crend(); ++c) {
        switch (*c) {
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
                if(isdigit(*c)) {
                    for(int i = 0; i < (int)*c - '0'; ++i) {
                        board.emplace_back(Color::empty, PieceType::empty);
                    }
                } else {
                    std::cout << "Invalid FEN";
                }
        }
    }

    if(fenSplit[1] == "w") {
        activeColor = Color::white;
    } else if(fenSplit[1] == "b") {
        activeColor = Color::black;
    }

    castlingWhiteK = false;
    castlingWhiteQ = false;
    castlingBlackK = false;
    castlingBlackQ = false;

    for (char const &c: fenSplit[2]) {
        switch (c) {
            case 'k':
                castlingBlackK = true; break;
            case 'q':
                castlingBlackQ = true; break;
            case 'K':
                castlingWhiteK = true; break;
            case 'Q':
                castlingWhiteQ = true; break;
            case '-':
                break;
            default:
                std::cout << "Invalid FEN";
        }
    }

    if(fenSplit[3] == "-") {
        enPassantSquare = -1;
    } else {
        enPassantSquare = 8 * ((int)fenSplit[3][1] - '1') + (int)fenSplit[3][0] - 'a';
    }

    halfmoveClock = std::stoi(fenSplit[4]);
    fullmoveNumber = std::stoi(fenSplit[5]);
}


Board::~Board() = default;


void Board::printBoard() {
    for(int i = width * height - 1; i >= 0; --i){
        board[i].printPiece();
        if(i % width == 0) {
            std::cout << "\n";
        }

    }

    std::cout << castlingWhiteK << " " << castlingWhiteQ << " " << castlingBlackK << " " << castlingBlackQ << "\n";
    std::cout << enPassantSquare << " " << halfmoveClock << " " << fullmoveNumber << "\n";
}


int Board::getWidth() const {
    return width;
}


int Board::getHeight() const {
    return height;
}

std::vector<Piece> Board::getBoard() {
    return board;
}

Color Board::getActiveColor() {
    return activeColor;
}


template<typename A>
void printVector(std::vector<A> &T) {
    std::cout << "[";
    for (auto i = T.begin(); i != T.end(); ++i)
        std::cout << *i << ',';
    std::cout << "]\n";
}


