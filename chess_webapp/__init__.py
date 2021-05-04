from flask import Flask

app = Flask(__name__)

from chess_webapp import routes
