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


// works for valid FEN
Board::Board(const std::string& fen, std::string prevMove) {
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
        enPassantSquare = 8 * ((int)fenSplit[3][1] - '1') + 'h' - (int)fenSplit[3][0];
    }

    halfmoveClock = std::stoi(fenSplit[4]);
    fullmoveNumber = std::stoi(fenSplit[5]);
    previousMove = prevMove;
}


Board::~Board() = default;


std::vector<Piece>& Board::getBoard() {
    return board;
}


void Board::setPiece(int square, const Piece& piece) {
    if(0 <= square && square < (int)board.size())
        board[square] = piece;
}


const int& Board::getWidth() const {
    return width;
}


const int& Board::getHeight() const {
    return height;
}


Color& Board::getActiveColor() {
    return activeColor;
}


void Board::changeActiveColor() {
    if(activeColor == Color::white) {
        activeColor = Color::black;
    } else {
        activeColor = Color::white;
    }
}


bool Board::getCastlingWhiteK() const {
    return castlingWhiteK;
}

bool Board::getCastlingWhiteQ() const {
    return castlingWhiteQ;
}

bool Board::getCastlingBlackK() const {
    return castlingBlackK;
}

bool Board::getCastlingBlackQ() const {
    return castlingBlackQ;
}


void Board::takeAwayCastlingWhiteK() {
    castlingWhiteK = false;
}

void Board::takeAwayCastlingWhiteQ() {
    castlingWhiteQ = false;
}

void Board::takeAwayCastlingBlackK() {
    castlingBlackK = false;
}

void Board::takeAwayCastlingBlackQ() {
    castlingBlackQ = false;
}


int Board::getEnPassantSquare() const {
    return enPassantSquare;
}


void Board::setEnPassantSquare(int square) {
    enPassantSquare = square;
}


void Board::printBoard() {
    for(int i = width * height - 1; i >= 0; --i){
        board[i].printPiece();
        if(i % width == 0) {
            std::cout << "\n";
        }
    }
}

void Board::setPreviousMove(std::string prevMove) {
    previousMove = prevMove;
}

std::string Board::getPreviousMove() {
    return previousMove;
}

std::string Board::boardToFen() {
    std::string fen_board = "";
    int empty = 0, position = 0;
    for (auto & piece: board) {
        ++position;
        const char fenSymbol = piece.getFenSymbol();
        if (fenSymbol != '0') {
            if (empty != 0) {
                fen_board += ('0' + empty);
                empty = 0;
            }
            fen_board += fenSymbol;
        }
        else {
            ++empty;
        }
        if (position % width == 0) {
            if (empty != 0) {
                fen_board += ('0' + empty);
                empty = 0;
            }
            fen_board += '/';
        }
    }
    fen_board = fen_board.substr(0, fen_board.size()-1);
    reverse(fen_board.begin(), fen_board.end());
    return fen_board;
}

std::string Board::colorToFen() {
    return activeColor == Color::white ? "w" : "b";
}

std::string Board::castlingToFen() {
    std::string castling = castlingWhiteK ? "K" : "-";
    castling += castlingWhiteQ ? 'Q' : '-';
    castling += castlingBlackK ? 'k' : '-';
    castling += castlingBlackQ ? 'q' : '-';
    return castling;
}

std::string Board::enPassantToFen() {
    if (enPassantSquare == -1)
        return "-";
    std::string ret = "";
    std::string file = "hgfedcba";
    std::string row = "12345678";
    ret += file[enPassantSquare % 8];
    ret += row[enPassantSquare / 8];
    return ret;
}

std::string Board::halfMoveToFen() {
    return "0"; // TODO
}

std::string Board::fullMoveToFen() {
    return "1"; // TODO
}

std::string Board::getFenString() {
    return boardToFen() + " " + colorToFen() + " " + castlingToFen() + " " +
        enPassantToFen() + " " + halfMoveToFen() + " " + fullMoveToFen();
}


template<typename A>
void printVector(std::vector<A> &T) {
    std::cout << "[";
    for (auto i = T.begin(); i != T.end(); ++i)
        std::cout << *i << ',';
    std::cout << "]\n";
}


