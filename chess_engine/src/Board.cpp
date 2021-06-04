#include <iostream>
#include <vector>
#include <string>

#include <iterator>
#include <sstream>
#include <algorithm>

#include "Board.h"
#include "Piece.h"


Board::Board() {
    board_.assign(WIDTH * HEIGHT, Piece());

    activeColor_ = Color::WHITE;

    castlingWhiteK_ = true;
    castlingWhiteQ_ = true;
    castlingBlackK_ = true;
    castlingBlackQ_ = true;

    enPassantSquare_ = -1;
    halfmoveClock_ = 0;
    fullmoveNumber_ = 1;
    score_ = 0;
}


// works for valid FEN
Board::Board(const std::string& fen, std::string prevMove) {
     // split FEN
    std::istringstream iss(fen);
    std::vector<std::string> fenSplit(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    // iteration backwards over part of fen
    for (auto c = fenSplit[0].crbegin() ; c != fenSplit[0].crend(); ++c) {
        switch (*c) {
            case 'k':
                board_.emplace_back(Color::BLACK, PieceType::KING); break;
            case 'q':
                board_.emplace_back(Color::BLACK, PieceType::QUEEN); break;
            case 'r':
                board_.emplace_back(Color::BLACK, PieceType::ROOK); break;
            case 'b':
                board_.emplace_back(Color::BLACK, PieceType::BISHOP); break;
            case 'n':
                board_.emplace_back(Color::BLACK, PieceType::KNIGHT); break;
            case 'p':
                board_.emplace_back(Color::BLACK, PieceType::PAWN); break;
            case 'K':
                board_.emplace_back(Color::WHITE, PieceType::KING); break;
            case 'Q':
                board_.emplace_back(Color::WHITE, PieceType::QUEEN); break;
            case 'R':
                board_.emplace_back(Color::WHITE, PieceType::ROOK); break;
            case 'B':
                board_.emplace_back(Color::WHITE, PieceType::BISHOP); break;
            case 'N':
                board_.emplace_back(Color::WHITE, PieceType::KNIGHT); break;
            case 'P':
                board_.emplace_back(Color::WHITE, PieceType::PAWN); break;
            case '/':
                break;
            default:
                if(isdigit(*c)) {
                    for(int i = 0; i < (int)*c - '0'; ++i) {
                        board_.emplace_back(Color::EMPTY, PieceType::EMPTY);
                    }
                } else {
                    std::cout << "Invalid FEN";
                }
        }
    }

    if(fenSplit[1] == "w") {
        activeColor_ = Color::WHITE;
    } else if(fenSplit[1] == "b") {
        activeColor_ = Color::BLACK;
    }

    castlingWhiteK_ = false;
    castlingWhiteQ_ = false;
    castlingBlackK_ = false;
    castlingBlackQ_ = false;

    for (char const &c: fenSplit[2]) {
        switch (c) {
            case 'k':
                castlingBlackK_ = true; break;
            case 'q':
                castlingBlackQ_ = true; break;
            case 'K':
                castlingWhiteK_ = true; break;
            case 'Q':
                castlingWhiteQ_ = true; break;
            case '-':
                break;
            default:
                std::cout << "Invalid FEN";
        }
    }

    if(fenSplit[3] == "-") {
        enPassantSquare_ = -1;
    } else {
        enPassantSquare_ = WIDTH * ((int)fenSplit[3][1] - '1') + 'h' - (int)fenSplit[3][0];
    }

    halfmoveClock_ = std::stoi(fenSplit[4]);
    fullmoveNumber_ = std::stoi(fenSplit[5]);
    previousMove_ = prevMove;
    score_ = 0;
}


Board::~Board() = default;


std::vector<Piece>& Board::getBoard() {
    return board_;
}


void Board::setPiece(int square, const Piece& piece) {
    if(0 <= square && square < (int)board_.size())
        board_[square] = piece;
}



Color& Board::getActiveColor() {
    return activeColor_;
}


void Board::changeActiveColor() {
    if(activeColor_ == Color::WHITE) {
        activeColor_ = Color::BLACK;
    } else {
        activeColor_ = Color::WHITE;
    }
}


bool Board::getCastlingWhiteK() const {
    return castlingWhiteK_;
}

bool Board::getCastlingWhiteQ() const {
    return castlingWhiteQ_;
}

bool Board::getCastlingBlackK() const {
    return castlingBlackK_;
}

bool Board::getCastlingBlackQ() const {
    return castlingBlackQ_;
}


void Board::takeAwayCastlingWhiteK() {
    castlingWhiteK_ = false;
}

void Board::takeAwayCastlingWhiteQ() {
    castlingWhiteQ_ = false;
}

void Board::takeAwayCastlingBlackK() {
    castlingBlackK_ = false;
}

void Board::takeAwayCastlingBlackQ() {
    castlingBlackQ_ = false;
}


int Board::getEnPassantSquare() const {
    return enPassantSquare_;
}


void Board::setEnPassantSquare(int square) {
    enPassantSquare_ = square;
}


void Board::printBoard() {
    for(int i = WIDTH * HEIGHT - 1; i >= 0; --i){
        board_[i].printPiece();
        if(i % WIDTH == 0) {
            std::cout << "\n";
        }
    }
}

void Board::setPreviousMove(std::string prevMove) {
    previousMove_ = prevMove;
}

std::string Board::getPreviousMove() {
    return previousMove_;
}

std::string Board::boardToFen() {
    std::string fen_board = "";
    int empty = 0, position = 0;
    for (auto & piece: board_) {
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
        if (position % WIDTH == 0) {
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
    return activeColor_ == Color::WHITE ? "w" : "b";
}

std::string Board::castlingToFen() {
    std::string castling = castlingWhiteK_ ? "K" : "-";
    castling += castlingWhiteQ_ ? 'Q' : '-';
    castling += castlingBlackK_ ? 'k' : '-';
    castling += castlingBlackQ_ ? 'q' : '-';
    return castling;
}

std::string Board::enPassantToFen() {
    if (enPassantSquare_ == -1)
        return "-";
    std::string ret = "";
    std::string file = "hgfedcba";
    std::string row = "12345678";
    ret += file[enPassantSquare_ % 8];
    ret += row[enPassantSquare_ / 8];
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

float Board::getScore() const {
    return score_;
}


float Board::eval() {
    for(int i = 0; i < int(board_.size()); ++i) {
        switch (board_[i].getPieceType()) {
            case PieceType::EMPTY:
                break;
            case PieceType::KING:
                if(board_[i].getColor() == Color::WHITE) {
                    score_ += KING_VALUE;
                    score_ += KING_TABLE[i];
                } else {
                    score_ -= KING_VALUE;
                    score_ -= KING_TABLE[63 - i];
                }
                break;
            case PieceType::QUEEN:
                if(board_[i].getColor() == Color::WHITE) {
                    score_ += QUEEN_VALUE;
                    score_ += QUEEN_TABLE[i];
                } else {
                    score_ -= QUEEN_VALUE;
                    score_ -= QUEEN_TABLE[63 - i];
                }
                break;
            case PieceType::ROOK:
                if(board_[i].getColor() == Color::WHITE) {
                    score_ += ROOK_VALUE;
                    score_ += ROOK_TABLE[i];
                } else {
                    score_ -= ROOK_VALUE;
                    score_ -= ROOK_TABLE[63 - i];
                }
                break;
            case PieceType::BISHOP:
                if(board_[i].getColor() == Color::WHITE) {
                    score_ += BISHOP_VALUE;
                    score_ += BISHOP_TABLE[i];
                } else {
                    score_ -= BISHOP_VALUE;
                    score_ -= BISHOP_TABLE[63 - i];
                }
                break;
            case PieceType::KNIGHT:
                if(board_[i].getColor() == Color::WHITE) {
                    score_ += KNIGHT_VALUE;
                    score_ += KNIGHT_TABLE[i];
                } else {
                    score_ -= KNIGHT_VALUE;
                    score_ -= KNIGHT_TABLE[63 - i];
                }
                break;
            case PieceType::PAWN:
                if(board_[i].getColor() == Color::WHITE) {
                    score_ += PAWN_VALUE;
                    score_ += PAWN_TABLE[i];
                } else {
                    score_ -= PAWN_VALUE;
                    score_ -= PAWN_TABLE[63 - i];
                }
                break;
            default:
                std::cout << "Invalid piece";
        }
    }
    return score_;
}


template<typename A>
void printVector(std::vector<A> &T) {
    std::cout << "[";
    for (auto i = T.begin(); i != T.end(); ++i)
        std::cout << *i << ',';
    std::cout << "]\n";
}


