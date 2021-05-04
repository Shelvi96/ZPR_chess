from flask import render_template
from chess_webapp import app
import chessengine


@app.route('/')
@app.route('/home')
def home():
    return render_template('home.html')


@app.route("/check/<fen_string>/old/<i_old>.<j_old>/new/<i_new>.<j_new>", methods=['GET'])
def check_fen(fen_string, i_old, j_old, i_new, j_new):
    fen_string = fen_string.replace(':', '/')
    ret = chessengine.getNextFen(fen_string, int(i_old), int(j_old), int(i_new), int(j_new))
    return ret


@app.route("/no_access")
def no_access():
    return render_template('no_access.html', title='No access')


@app.route("/app")
def app():
    return render_template('app.html', title='App')
