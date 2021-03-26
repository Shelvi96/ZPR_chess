from chess_webapp import app

from ctypes import * 

libchesslib = CDLL("chess_engine/libchesslib.so") 


libchesslib._Z11printDupskov() 


if __name__ == '__main__':
    app.run(host='127.0.0.1', port=7890, debug=True)
