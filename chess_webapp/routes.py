from flask import render_template, flash, redirect, url_for, request
from chess_webapp import app, db, bcrypt, cur, conn
from chess_webapp.models import User
from chess_webapp.forms import LoginForm, RegistrationForm, SimpleProposal, HousingAssistanceProposal, VerifyProposalForm
from flask_login import login_user, current_user, logout_user, login_required
from flask_user import roles_required
from chess_webapp.utils import represents_int
from datetime import datetime
from random import randint

@app.route('/')
@app.route('/home')
def home():
    return render_template('home.html')


@app.route("/register", methods=['GET', 'POST'])
@login_required
def register():
    if current_user.role != 'admin':
        return render_template('no_access.html', title='No Access')
    form = RegistrationForm()
    if form.validate_on_submit():
        cur.execute("""INSERT INTO pracownik(imie, nazwisko, stanowisko, data_rozpoczecia_pracy, pesel,
                pensja, komisja_id_komisji) VALUES (%s, %s, %s, timestamp %s, %s, %s, %s) returning id_pracownika;""",
                    (form.first_name.data, form.last_name.data, form.position.data, form.work_start_date.data,
                     form.pesel.data, form.salary.data, randint(0, 5)))
        worker_id = cur.fetchone()[0]
        conn.commit()

        hashed_password = bcrypt.generate_password_hash(form.password.data).decode('utf-8')
        user = User(username=form.username.data, email=form.email.data, password=hashed_password, role=form.role.data, worker_id=worker_id)
        db.session.add(user)
        db.session.commit()

        return redirect(url_for('home'))

    cur.execute("""SELECT role from roles""")
    roles_list = cur.fetchall()
    roles_list = [role[0] for role in roles_list]

    return render_template('register.html', title='Register', form=form, roles_list=roles_list)


@app.route("/login", methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('home'))
    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()
        if user and bcrypt.check_password_hash(user.password, form.password.data):
            login_user(user, remember=True)
            next_page = request.args.get('next')
            return redirect(next_page) if next_page else redirect(url_for('home'))
        flash('Login Unsuccessful. Please check username and password')
    return render_template('login.html', title='Login', form=form)


@app.route("/logout")
def logout():
    logout_user()
    return redirect(url_for('home'))


@app.route("/new_proposal")
@login_required
def new_proposal():
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')
    return render_template('new_proposal.html')


@app.route("/new_proposal/sent")
@login_required
def new_proposal_sent():
    return render_template('new_proposal_sent.html')


@app.route("/new_proposal/healthcare", methods=['GET', 'POST'])
@login_required
def healthcare():
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')
    form = SimpleProposal()
    if form.validate_on_submit():
        cur.execute("""INSERT INTO uslugi(rodzaj_uslugi, wymagany_dokument, max_wartosc)
                        VALUES ('Opieka_medyczna', 'Zaswiadczenie', 1300) RETURNING id_uslugi;""")
        id_uslugi = cur.fetchone()[0]

        cur.execute("""INSERT INTO opieka_medyczna(id_uslugi, oczekiwana_refundacja) VALUES (%s, %s);""",
                    (id_uslugi, form.expected_refund.data))

        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (current_user.worker_id,))
        id_komisji = cur.fetchone()[0]

        cur.execute("""INSERT INTO wniosek(decyzja, uwaga, uwaga_komisji, data_zlozenia, data_zamkniecia,
                        pracownik_id_pracownika, uslugi_id_uslugi, komisja_id_komisji)
                        VALUES (%s, %s, %s, timestamp %s, timestamp %s, %s, %s, %s);""",
                    ('oczekujacy', form.comments1.data, '', datetime.today(),
                     datetime.today(), current_user.worker_id, id_uslugi, id_komisji))

        conn.commit()
        return redirect(url_for('new_proposal_sent'))

    return render_template('healthcare.html', title='Healthcare', form=form)


@app.route("/new_proposal/housing_assistance", methods=['GET', 'POST'])
@login_required
def housing_assistance():
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')
    form = HousingAssistanceProposal()
    if form.validate_on_submit():
        cur.execute("""INSERT INTO uslugi(rodzaj_uslugi, wymagany_dokument, max_wartosc)
                        VALUES ('Housing_assistance', 'Zaswiadczenie', 1300) RETURNING id_uslugi;""")
        id_uslugi = cur.fetchone()[0]

        cur.execute("""INSERT INTO pomoc_mieszkaniowa(id_uslugi, oczekiwana_wartosc, dlugosc) VALUES (%s, %s, %s);""",
                    (id_uslugi, form.expected_refund.data, form.length.data))

        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (current_user.worker_id,))
        id_komisji = cur.fetchone()[0]

        cur.execute("""INSERT INTO wniosek(decyzja, uwaga, uwaga_komisji, data_zlozenia, data_zamkniecia,
                        pracownik_id_pracownika, uslugi_id_uslugi, komisja_id_komisji)
                        VALUES (%s, %s, %s, timestamp %s, timestamp %s, %s, %s, %s);""",
                    ('oczekujacy', form.comments1.data, '', datetime.today(),
                     datetime.today(), current_user.worker_id, id_uslugi, id_komisji))

        conn.commit()
        return redirect(url_for('new_proposal_sent'))

    return render_template('housing_assistance.html', title='Housing_assistance', form=form)


@app.route("/new_proposal/allowance", methods=['GET', 'POST'])
@login_required
def allowance():
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')
    form = SimpleProposal()
    if form.validate_on_submit():
        cur.execute("""INSERT INTO uslugi(rodzaj_uslugi, wymagany_dokument, max_wartosc)
                            VALUES ('Zapomoga', 'Brak', 1300) RETURNING id_uslugi;""")
        id_uslugi = cur.fetchone()[0]

        cur.execute("""INSERT INTO zapomoga(id_uslugi, oczekiwana_wartosc) VALUES (%s, %s);""",
                    (id_uslugi, form.expected_refund.data))

        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (current_user.worker_id,))
        id_komisji = cur.fetchone()[0]

        cur.execute("""INSERT INTO wniosek(decyzja, uwaga, uwaga_komisji, data_zlozenia, data_zamkniecia,
                            pracownik_id_pracownika, uslugi_id_uslugi, komisja_id_komisji)
                            VALUES (%s, %s, %s, timestamp %s, timestamp %s, %s, %s, %s);""",
                    ('oczekujacy', form.comments1.data, '', datetime.today(),
                     datetime.today(), current_user.worker_id, id_uslugi, id_komisji))

        conn.commit()
        return redirect(url_for('new_proposal_sent'))

    return render_template('allowance.html', title='Allowance', form=form)


@app.route("/new_proposal/cultural_event", methods=['GET', 'POST'])
@login_required
def cultural_event():
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')
    form = SimpleProposal()
    if form.validate_on_submit():
        cur.execute("""INSERT INTO uslugi(rodzaj_uslugi, wymagany_dokument, max_wartosc)
                                VALUES ('Impreza_kulturalna', 'Faktura', 1300) RETURNING id_uslugi;""")
        id_uslugi = cur.fetchone()[0]

        cur.execute("""INSERT INTO impreza_kulturalna(id_uslugi, oczekiwana_wartosc) VALUES (%s, %s);""",
                    (id_uslugi, form.expected_refund.data))

        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (current_user.worker_id,))
        id_komisji = cur.fetchone()[0]

        cur.execute("""INSERT INTO wniosek(decyzja, uwaga, uwaga_komisji, data_zlozenia, data_zamkniecia,
                                pracownik_id_pracownika, uslugi_id_uslugi, komisja_id_komisji)
                                VALUES (%s, %s, %s, timestamp %s, timestamp %s, %s, %s, %s);""",
                    ('oczekujacy', form.comments1.data, '', datetime.today(),
                     datetime.today(), current_user.worker_id, id_uslugi, id_komisji))

        conn.commit()
        return redirect(url_for('new_proposal_sent'))

    return render_template('cultural_event.html', title='Cultural_event', form=form)


@app.route("/new_proposal/vacation_refund", methods=['GET', 'POST'])
@login_required
def vacation_refund():
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')
    form = SimpleProposal()
    if form.validate_on_submit():
        cur.execute("""INSERT INTO uslugi(rodzaj_uslugi, wymagany_dokument, max_wartosc)
                                VALUES ('Refundacja_wakacji', 'Faktura', 1300) RETURNING id_uslugi;""")
        id_uslugi = cur.fetchone()[0]

        cur.execute("""INSERT INTO refundacja_wakacji(id_uslugi, wartosc_oczrekiwana) VALUES (%s, %s);""",
                    (id_uslugi, form.expected_refund.data))

        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (current_user.worker_id,))
        id_komisji = cur.fetchone()[0]

        cur.execute("""INSERT INTO wniosek(decyzja, uwaga, uwaga_komisji, data_zlozenia, data_zamkniecia,
                                pracownik_id_pracownika, uslugi_id_uslugi, komisja_id_komisji)
                                VALUES (%s, %s, %s, timestamp %s, timestamp %s, %s, %s, %s);""",
                    ('oczekujacy', form.comments1.data, '', datetime.today(),
                     datetime.today(), current_user.worker_id, id_uslugi, id_komisji))

        conn.commit()
        return redirect(url_for('new_proposal_sent'))

    return render_template('vacation_refund.html', title='Vacation_refund', form=form)


@app.route("/my_proposals")
@login_required
def my_proposals():
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')

    query = """select * from uslugi
                join wniosek on wniosek.uslugi_id_uslugi = uslugi.id_uslugi
                where wniosek.pracownik_id_pracownika = """ + str(current_user.worker_id) + """
                order by wniosek.data_zlozenia desc;"""

    cur.execute(query)
    data = cur.fetchall()
    return render_template('my_proposals.html', data=data)


@app.route("/proposal_details/<proposal_id>")
@login_required
def proposal_details(proposal_id):
    if current_user.role == 'admin':
        return render_template('no_access.html', title='No Access')

    if not represents_int(proposal_id):
        return render_template('no_access.html', title='No Access')

    if current_user.role == 'pracownik':
        query = """select * from uslugi
                   join wniosek on wniosek.uslugi_id_uslugi = uslugi.id_uslugi
                   where wniosek.id_wniosku = """ + str(proposal_id) + """
                    and wniosek.pracownik_id_pracownika = """ + str(current_user.worker_id) + """
                    limit 1;"""
        cur.execute(query)
        data = cur.fetchall()
        if len(data) == 1:
            return render_template('proposal_details.html', title='Proposal details', data=data[0])
        else:
            return render_template('no_access.html', title='No Access')

    if current_user.role == 'komisja':
        query = """select komisja_id_komisji from pracownik where id_pracownika =""" + str(current_user.worker_id)
        cur.execute(query)
        comission_id = cur.fetchall()[0][0]
        query = """select * from uslugi
                           join wniosek on wniosek.uslugi_id_uslugi = uslugi.id_uslugi
                           where wniosek.id_wniosku = """ + str(proposal_id) + """
                            and wniosek.komisja_id_komisji = """ + str(comission_id) + """
                            limit 1;"""
        cur.execute(query)
        data = cur.fetchall()
        if len(data) == 1:
            return render_template('proposal_details.html', title='Proposal details', data=data[0])
        else:
            return render_template('no_access.html', title='No Access')


@app.route("/verify_proposals", methods=['GET', 'POST'])
@login_required
def verify_proposals():
    if current_user.role != 'komisja':
        return render_template('no_access.html', title='No Access')

    query = """select komisja_id_komisji from pracownik where id_pracownika =""" + str(current_user.worker_id)
    cur.execute(query)
    comission_id = cur.fetchall()[0][0]
    print(comission_id)
    query = """select * from uslugi
                join wniosek on wniosek.uslugi_id_uslugi = uslugi.id_uslugi
                where wniosek.komisja_id_komisji = """ + str(comission_id) + """
                order by wniosek.data_zlozenia desc;"""
    cur.execute(query)
    data = cur.fetchall()
    return render_template('verify_proposals.html', data=data)


@app.route("/verify_proposal/<proposal_id>", methods=['GET', 'POST'])
@login_required
def verify_proposal(proposal_id):
    if current_user.role == 'komisja':
        query = """select komisja_id_komisji from pracownik where id_pracownika =""" + str(current_user.worker_id)
        cur.execute(query)
        comission_id = cur.fetchall()[0][0]
        query = """select * from uslugi
                              join wniosek on wniosek.uslugi_id_uslugi = uslugi.id_uslugi
                              where wniosek.id_wniosku = """ + str(proposal_id) + """
                               and wniosek.komisja_id_komisji = """ + str(comission_id) + """
                               and wniosek.decyzja = 'oczekujacy' limit 1;"""
        cur.execute(query)
        data = cur.fetchall()
        if len(data) == 1:
            form = VerifyProposalForm()
            if form.validate_on_submit():
                decision = 'zaakceptowane' if form.submit_accept.data else 'odrzucone'
                query = """update wniosek set decyzja = '""" + decision + """', uwaga_komisji = '""" + form.opinion.data +"""'
                    where id_wniosku = """ + str(proposal_id) + ";"
                cur.execute(query)
                conn.commit()
                return redirect(url_for('verify_proposals'))
            return render_template('verify_proposal.html', title='Proposal details', data=data[0], form=form)
        else:
            return render_template('no_access.html', title='No Access')
    else:
        return render_template('no_access.html', title='No Access')
