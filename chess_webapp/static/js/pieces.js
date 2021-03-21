class Piece {
    constructor(color) {
        this.color = color;
    }
}

export class King extends Piece {
    constructor(color) {
        super(color);
        this.id = this.color === 'white' ? 'K' : 'k';
    }
    get_piece_icon() {
        return 'king_' + this.color + ".png";
    }
    get_piece_id() {
        return this.id;
    }
}

export class Queen extends Piece {
    constructor(color) {
        super(color);
        this.id = this.color === 'white' ? 'Q' : 'q';
    }
    get_piece_icon() {
        return 'queen_' + this.color + ".png";
    }
    get_piece_id() {
        return this.id;
    }
}

export class Rook extends Piece {
    constructor(color) {
        super(color);
        this.id = this.color === 'white' ? 'R' : 'r';
    }
    get_piece_icon() {
        return 'rook_' + this.color + ".png";
    }
    get_piece_id() {
        return this.id;
    }
}

export class Bishop extends Piece {
    constructor(color) {
        super(color);
        this.id = this.color === 'white' ? 'B' : 'b';
    }
    get_piece_icon() {
        return 'bishop_' + this.color + ".png";
    }
    get_piece_id() {
        return this.id;
    }
}

export class Knight extends Piece {
    constructor(color) {
        super(color);
        this.id = this.color === 'white' ? 'N' : 'n';
    }
    get_piece_icon() {
        return 'knight_' + this.color + ".png";
    }
    get_piece_id() {
        return this.id;
    }
}

export class Pawn extends Piece {
    constructor(color) {
        super(color);
        this.id = this.color === 'white' ? 'P' : 'p';
    }
    get_piece_icon() {
        return 'pawn_' + this.color + ".png";
    }
    get_piece_id() {
        return this.id;
    }
}

export function parse_string_to_piece(str) {
    switch(str) {
        case 'K':
            return new King('white');
        case 'k':
            return new King('black');
        case 'Q':
            return new Queen('white');
        case 'q':
            return new Queen('black');
        case 'R':
            return new Rook('white');
        case 'r':
            return new Rook('black');
        case 'B':
            return new Bishop('white');
        case 'b':
            return new Bishop('black');
        case 'N':
            return new Knight('white');
        case 'n':
            return new Knight('black');
        case 'P':
            return new Pawn('white');
        case 'p':
            return new Pawn('black');
        default:
            return new Piece('white');
    }
}