from flask import render_template, redirect, url_for
from chess_webapp import app
import chessengine

import webbrowser
import os

@app.route('/')
@app.route('/home')
def home():
    return render_template('home.html')


@app.route("/check/<fen_string>/old/<i_old>.<j_old>/new/<i_new>.<j_new>", methods=['GET'])
def check_fen(fen_string, i_old, j_old, i_new, j_new):
    fen_string = fen_string.replace(':', '/')
    ret = chessengine.getNextFen(fen_string, int(i_old), int(j_old), int(i_new), int(j_new))
    return ret


@app.route("/gameover/<fen_string>", methods=['GET'])
def is_game_over(fen_string):
    fen_string = fen_string.replace(':', '/')
    ret = chessengine.isGameOver(fen_string)
    return ret


@app.route("/no_access")
def no_access():
    return render_template('no_access.html', title='No access')


@app.route("/doc")
def doc():
    filename = 'chess_webapp/html/index.html'
    webbrowser.open('file://' + os.path.realpath(filename))
    return redirect(url_for('home'))


@app.route("/app")
def app():
    return render_template('app.html', title='App')
