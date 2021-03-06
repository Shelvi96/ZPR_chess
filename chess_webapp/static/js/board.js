import { King, Queen, Rook, Bishop, Knight, Pawn, parse_string_to_piece } from './pieces.js';
import { is_numeric } from './utils.js'

class Field {
    constructor(x, y, color) {
        this.color = color;
        this.piece = null;
        this.game_over = false;
        this.dom_element = document.getElementById('box_' + x + '_' + y);
        this.set_color();
    }
    set_color() {
        this.dom_element.classList.add(this.color);
    }
    get_dom_element() {
        return this.dom_element;
    }
    get_piece() {
        return this.piece;
    }
    set_piece(pawn) {
        this.piece = pawn;
    }
    draw_piece() {
        this.dom_element.innerHTML = null;
        if (this.piece !== null) {
            let img = document.createElement('img')
            img.src = 'static/img/' + this.piece.get_piece_icon();
            this.dom_element.append(img);
        }
    }
}

export class Board {
    constructor(board_config) {
        this.board_size = 8;
        this.board_config = board_config;
        this.active_square = null;
        this.fields = this.init();
        this.update_board();
    }

    init() {
        let board = []
        for (let i = 0; i < this.board_size; ++i) {
            let tmp_fields = [];
            for (let j = 0; j < this.board_size; ++j) {
                const color = (i+j)%2 ? 'dark' : 'light';
                let field = new Field(i, j, color)
                field.get_dom_element().addEventListener('click', () => {
                    this.field_event(i, j);
                })
                tmp_fields.push(field);
            }
            board.push(tmp_fields);
        }
        return board;
    }

    board_config_to_pieces() {
        const pieces_setup = this.board_config.split(' ')[0];
        const board_rows = pieces_setup.split('/');
        let row_idx = 0

        for (let file = 0; file < this.board_size; ++file) {
            row_idx = 0;
            for (let rank = 0; rank < this.board_size; ++rank) {
                if (is_numeric(board_rows[file][row_idx]))
                    rank += parseInt(board_rows[file][row_idx]) - 1;
                else
                    this.fields[file][rank].set_piece(parse_string_to_piece(board_rows[file][row_idx]));
                row_idx += 1;
            }
        }
    }

    field_event(i, j) {
        if (this.active_square) {
            this.get_square(this.active_square[0], this.active_square[1]).classList.remove('active');
            this.check_move(this.active_square[0], this.active_square[1], i, j)
            this.active_square = null;
        } else {
            this.get_square(i, j).classList.add('active')
            this.active_square = [i, j]
        }
    }

    get_square(i, j) {
        return document.getElementById('box_' + i + '_' + j)
    }

    draw_pieces() {
        for (let i = 0; i < this.board_size; ++i) {
            for (let j = 0; j < this.board_size; j++) {
                this.fields[i][j].draw_piece();
            }
        }
    }

    check_move(i_old, j_old, i_new, j_new) {
        if (this.game_over)
            return;

        const board_config_parsed = this.board_config.replace(/\//g, ":");
        const board = this;
        document.getElementById('fen').innerHTML = "Waiting for the opponent's response...";
        fetch(`/check/${board_config_parsed}/old/${7-i_old}.${7-j_old}/new/${7-i_new}.${7-j_new}`)
            .then(function (response) {
                return response.text();
            }).then(function (newFEN) {
                if (newFEN !== "") {
                    document.getElementById('fen').innerHTML = newFEN;
                    board.board_config = newFEN;
                    board.update_board();
                    board.check_game_over();
                }
                else
                    document.getElementById('fen').innerHTML = "Invalid move. Please try again.";
            });
    }
    update_board() {
        this.clear_board();
        this.board_config_to_pieces();
        this.draw_pieces();
    }
    clear_board() {
        for (let file = 0; file < this.board_size; ++file) {
            for (let rank = 0; rank < this.board_size; ++rank) {
                this.fields[file][rank].set_piece(null);
            }
        }
    }
    check_game_over() {
        const board_config_parsed = this.board_config.replace(/\//g, ":");
        const board = this;
        fetch(`/gameover/${board_config_parsed}`)
            .then(function (response) {
                return response.text();
            }).then(function (gameStatus) {
                if (gameStatus === "GAME_OVER") {
                    board.game_over = true;
                    document.getElementById('fen').innerHTML = "GAME OVER!";
                }
            })
    }
}

