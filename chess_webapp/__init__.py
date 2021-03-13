import psycopg2
import psycopg2.extras
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_bcrypt import Bcrypt
from flask_login import LoginManager


app = Flask(__name__)
app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'
app.config['SQLALCHEMY_DATABASE_URI'] = "postgres://root:root@127.0.0.1:5432/bd2"
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)
bcrypt = Bcrypt(app)
login_manager = LoginManager(app)
login_manager.login_view = 'login'

conn = psycopg2.connect(
    host="localhost",
    database="bd2",
    user="root",
    password="root")
cur = conn.cursor(cursor_factory=psycopg2.extras.DictCursor)

from chess_webapp import routes
