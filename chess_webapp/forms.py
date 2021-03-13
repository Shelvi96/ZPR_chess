from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField, IntegerField, DecimalField, DateTimeField
from wtforms.validators import DataRequired, Length, Email, EqualTo, ValidationError, NumberRange
from chess_webapp.models import User


class RegistrationForm(FlaskForm):
    first_name = StringField('Imie', validators=[DataRequired(), Length(min=2, max=20)])
    last_name = StringField('Nazwisko', validators=[DataRequired(), Length(min=2, max=20)])
    pesel = IntegerField('Pesel', validators=[DataRequired(), NumberRange(min=10000000000, max=99999999999)])

    username = StringField('Username', validators=[DataRequired(), Length(min=2, max=20)])
    email = StringField('Email', validators=[DataRequired(), Email()])
    position = StringField('Stanowisko', validators=[DataRequired(), Length(min=2, max=20)])
    work_start_date = DateTimeField('Data rozpoczecia pracy (yyyy-mm-dd)', format='%Y-%m-%d', validators=[DataRequired()])

    salary = DecimalField('Pensja', validators=[DataRequired(), NumberRange(min=0, max=9999999999.99)])

    password = PasswordField('Password', validators=[DataRequired()])
    confirm_password = PasswordField('Confirm', validators=[DataRequired(), EqualTo('password')])

    role = StringField('Role', validators=[DataRequired(), Length(min=2, max=20)])

    submit = SubmitField('Dodaj')

    def validate_username(self, username):
        user = User.query.filter_by(username=username.data).first()
        if user:
            raise ValidationError('That username is taken. Please choose a different one.')

    def validate_email(self, email):
        user = User.query.filter_by(email=email.data).first()
        if user:
            raise ValidationError('That email is taken. Please choose a different one.')


class LoginForm(FlaskForm):
    username = StringField('Username', validators=[DataRequired(), Length(min=2, max=20)])
    password = PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Login')


class SimpleProposal(FlaskForm):
    comments1 = StringField('Uwagi', validators=[DataRequired(), Length(min=2, max=255)])
    expected_refund = DecimalField('Wartosc', validators=[DataRequired(), NumberRange(min=0, max=9999.99)])
    submit = SubmitField('Wyslij')


class HousingAssistanceProposal(FlaskForm):
    comments1 = StringField('Uwagi', validators=[DataRequired(), Length(min=2, max=255)])
    expected_refund = DecimalField('Wartosc', validators=[DataRequired(), NumberRange(min=0, max=9999.99)])
    length = IntegerField('Dlugosc', validators=[DataRequired(), NumberRange(min=1, max=99)])
    submit = SubmitField('Wyslij')


class VerifyProposalForm(FlaskForm):
    opinion = StringField('Opinion', validators=[DataRequired(), Length(min=2, max=200)])
    submit_reject = SubmitField('Odrzuć')
    submit_accept = SubmitField('Zaakceptuj')
