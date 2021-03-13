function draw_board(board) {
    console.log(board)
}
function load_board() {
    const board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    draw_board(board)
}

window.onload = function() {
    load_board();
}