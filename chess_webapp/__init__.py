from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_bcrypt import Bcrypt
from flask_login import LoginManager

app = Flask(__name__)
app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'
app.config['SQLALCHEMY_DATABASE_URI'] = "postgres://postgres:postgres@127.0.0.1:5432/chess"
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)
bcrypt = Bcrypt(app)
login_manager = LoginManager(app)
login_manager.login_view = 'login'

from chess_webapp.models import User
from chess_webapp import routes

db.create_all()
db.session.commit()
if User.query.filter_by(username='admin').first() is None:
    admin = User(username='admin', email='admin@example.com', password=bcrypt.generate_password_hash('admin').decode('utf-8'))
    db.session.add(admin)
    db.session.commit()

