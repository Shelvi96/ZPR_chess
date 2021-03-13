import psycopg2
import random
from datetime import datetime, timedelta
from chess_webapp import bcrypt


def random_date(start, end):
    delta = end - start
    int_delta = delta.days
    random_days = random.randrange(int_delta)
    dt = start + timedelta(days=random_days)
    return dt


def db_connect():
    conn = psycopg2.connect(
        host="localhost",
        database="bd2",
        user="root",
        password="root")

    cur = conn.cursor()
    cur.execute('SELECT version()')
    response = cur.fetchall()
    print(response)

    return conn


def generate_workers(num):
    pracownicy = []
    imiona = ['Adam', 'Bartosz', 'Damian', 'Jerzy', 'Arleta', 'Beata', 'Dominika', 'Julia']
    nazwiska = ['Kowalski', 'Nowak', 'Grzeskowiak', 'Adamiuk', 'Romanov', 'Parowka']
    stanowiska = ['junior', 'mid', 'senior', 'manager', 'CEO']
    id_komisji = [i for i in range(0, 6)]
    for id in range(num):
        pracownicy.append({
            'id': id+1,
            'imie': random.choice(imiona),
            'nazwisko': random.choice(nazwiska),
            'stanowisko': random.choice(stanowiska),
            'data_rozpoczecia': random_date(datetime(2015, 1, 1), datetime(2020, 1, 1)),
            'pesel': random.randint(10000000000, 99999999999),
            'pensja': random.randint(3, 12) * 1000,
            'id_komisji': (id+1)/2 if (id+1) % 2 == 0 else 0
        })
    return pracownicy


def generate_budget(num):
    budgets = []
    categories = ['pracowniczy', 'socjalny', 'swiateczny', 'prezesowski']
    limits = [10000, 15000, 20000, 25000, 30000]
    for id in range(num):
        budgets.append({
            'id': id,
            'category': random.choice(categories),
            'limit': random.choice(limits),
        })
    return budgets


def generate_uses(num):
    uses = []
    for id in range(num):
        uses.append({
            'used': 50000,
            'low_income': bool(random.getrandbits(1)),
            'budget_id': random.randint(1, 5),
            'worker_id': random.randint(1, 10)
        })
    return uses


def generate_attachments(num):
    attachments = []
    contents = ['C://Users/AdamNowak/zalacznik.pdf', 'C://Users/AlicjaKowalczyk/attachment.docx']
    for id in range(num):
        attachments.append({
            'id': id,
            'content': random.choice(contents),
            'proposal_id': random.randint(1, 5),
        })
    return attachments


def generate_single_service(num):
    services = []
    decisions = ['zaakceptowane', 'odrzucone']
    comments = ['Prosze o akceptacje mojego wniosku', 'Zwracam sie z uprzejma prosba o przyznanie mi funduszy',
                'Z niecierpliwoscia oczekuje na odpowiedz', 'Panie prezesie, wiem ze pana stac']
    comitee_comments = ['Przekroczono budzet', 'Nie stac nas przez pandemie', 'Przyznano wniosek bez zarzutow']
    for id in range(num):
        services.append({
            'id': id,
            'decision': random.choice(decisions),
            'comment': random.choice(comments),
            'comitee_comment': random.choice(comitee_comments),
            'submit_date': random_date(datetime(2019, 1, 1), datetime(2020, 1, 1)),
            'close_date': random_date(datetime(2019, 1, 1), datetime(2020, 1, 1)),
            'worker_id': random.randint(1, 10),
            'expected_refund': random.randint(1, 10) * 100
        })
    return services


def load_roles(cur):
    roles = ['admin', 'komisja', 'pracownik']

    for role in roles:
        query = """INSERT INTO roles(role)
                    VALUES ('{}');""".format(
            role)
        cur.execute(query)
        print(query)


def load_workers(cur, num=10):
    workers = generate_workers(num)

    hashed_password = bcrypt.generate_password_hash('admin').decode('utf-8')
    query = """INSERT INTO users(username, email, password, role, worker_id)
                VALUES ('{}', '{}@firma.com', '{}', '{}', null);""".format(
        'admin', 'admin', hashed_password, 'admin')
    cur.execute(query)
    print(query)

    for worker in workers:
        query = """INSERT INTO pracownik(imie, nazwisko, stanowisko, data_rozpoczecia_pracy, pesel,
                pensja, komisja_id_komisji)
                VALUES ('{}', '{}', '{}', timestamp '{}', '{}', {}, {});""".format(
            worker['imie'], worker['nazwisko'], worker['stanowisko'], worker['data_rozpoczecia'],
            worker['pesel'], worker['pensja'], worker['id_komisji'])
        cur.execute(query)
        print(query)

        role = 'pracownik' if worker['id_komisji'] == 0 else 'komisja'
        hashed_password = bcrypt.generate_password_hash(worker['imie']).decode('utf-8')
        query = """INSERT INTO users(username, email, password, role, worker_id)
                    VALUES ('{}{}', '{}{}@firma.com', '{}', '{}', {});""".format(
            worker['imie'], worker['id'], worker['imie'], worker['id']+1,
            hashed_password, role, worker['id'])
        cur.execute(query)
        print(query)


def load_committees(cur, num=5):
    for id in range(num + 1):
        query = "INSERT INTO komisja(id_komisji) VALUES ({});".format(id)
        cur.execute(query)
        print(query)


def load_budgets(cur, num=5):
    budgets = generate_budget(num)
    for budget in budgets:
        query = """INSERT INTO budzet(
                kategoria, prog)
                VALUES ('{}', {});""".format(
            budget['category'], budget['limit'])
        cur.execute(query)
        print(query)


def load_uses(cur, num=5):
    uses = generate_uses(num)
    for use in uses:
        query = """INSERT INTO wykorzystanie(
                wykorzystanie, niski_dochod, budzet_id_budzetu, pracownik_id_pracownika)
                VALUES ({}, {}, {}, {});""".format(
            use['used'], use['low_income'], use['budget_id'], use['worker_id'])
        cur.execute(query)
        print(query)


def load_attachments(cur, num=5):
    attachments = generate_attachments(num)
    for attachment in attachments:
        query = """INSERT INTO zalaczniki(
                tresc, wniosek_id_wniosku)
                VALUES ('{}', {});""".format(
            attachment['content'], attachment['proposal_id'])
        cur.execute(query)
        print(query)


def load_service(cur, service_type, required_document, value):
    cur.execute("""INSERT INTO uslugi(rodzaj_uslugi, wymagany_dokument, max_wartosc) 
                VALUES (%s, %s, %s) RETURNING id_uslugi;""", (service_type, required_document, value))
    return cur.fetchone()[0]


def load_proposal(cur, decision, comment1, comment2, date1, date2, user_id, service_id, committee_id):
    cur.execute("""INSERT INTO wniosek(decyzja, uwaga, uwaga_komisji, data_zlozenia, data_zamkniecia,
                                            pracownik_id_pracownika, uslugi_id_uslugi, komisja_id_komisji)
                                            VALUES (%s, %s, %s, timestamp %s, timestamp %s, %s, %s, %s);""",
                (decision, comment1, comment2, date1, date2, user_id, service_id, committee_id))


def load_impreza_kulturalna(cur, num=5):
    services = generate_single_service(num)
    for service in services:
        id_uslugi = load_service(cur, 'Impreza_kulturalna', 'Faktura', 1300)

        cur.execute("""INSERT INTO impreza_kulturalna(id_uslugi, oczekiwana_wartosc) 
                    VALUES ({}, {});""".format(id_uslugi, service['expected_refund']))

        user = random.randint(1, 10)
        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (user,))
        id_komisji = cur.fetchone()[0]

        load_proposal(cur, service['decision'], service['comment'], service['comitee_comment'],
                      service['submit_date'], service['close_date'], user, id_uslugi, id_komisji)


def load_opieka_medyczna(cur, num=5):
    services = generate_single_service(num)
    for service in services:
        id_uslugi = load_service(cur, 'Opieka_medyczna', 'Zaswiadczenie', 1900)

        cur.execute("""INSERT INTO opieka_medyczna(id_uslugi, oczekiwana_refundacja) 
                        VALUES ({}, {});""".format(id_uslugi, service['expected_refund']))

        user = random.randint(1, 10)
        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (user,))
        id_komisji = cur.fetchone()[0]

        load_proposal(cur, service['decision'], service['comment'], service['comitee_comment'],
                      service['submit_date'], service['close_date'], user, id_uslugi, id_komisji)


def load_pomoc_mieszkaniowa(cur, num=5):
    services = generate_single_service(num)
    for service in services:
        id_uslugi = load_service(cur, 'Pomoc_mieszkaniowa', 'Zaswiadczenie', 1900)

        cur.execute("""INSERT INTO pomoc_mieszkaniowa(id_uslugi, oczekiwana_wartosc, dlugosc) VALUES (%s, %s, %s);""",
                    (id_uslugi, service['expected_refund'], random.randint(1, 20)))

        user = random.randint(1, 10)
        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (user,))
        id_komisji = cur.fetchone()[0]

        load_proposal(cur, service['decision'], service['comment'], service['comitee_comment'],
                      service['submit_date'], service['close_date'], user, id_uslugi, id_komisji)


def load_refundacja_wakacji(cur, num=5):
    services = generate_single_service(num)
    for service in services:
        id_uslugi = load_service(cur, 'Refundacja_wakacji', 'Faktura', 1000)

        cur.execute("""INSERT INTO refundacja_wakacji(id_uslugi, wartosc_oczrekiwana) VALUES (%s, %s);""",
                    (id_uslugi, service['expected_refund']))

        user = random.randint(1, 10)
        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (user,))
        id_komisji = cur.fetchone()[0]

        load_proposal(cur, service['decision'], service['comment'], service['comitee_comment'],
                      service['submit_date'], service['close_date'], user, id_uslugi, id_komisji)


def load_zapomoga(cur, num=5):
    services = generate_single_service(num)
    for service in services:
        id_uslugi = load_service(cur, 'Zapomoga', 'Faktura', 1000)

        cur.execute("""INSERT INTO zapomoga(id_uslugi, oczekiwana_wartosc) VALUES (%s, %s);""",
                    (id_uslugi, service['expected_refund']))

        user = random.randint(1, 10)
        cur.execute("""SELECT komisja_id_komisji FROM pracownik WHERE id_pracownika = %s;""",
                    (user,))
        id_komisji = cur.fetchone()[0]

        load_proposal(cur, service['decision'], service['comment'], service['comitee_comment'],
                      service['submit_date'], service['close_date'], user, id_uslugi, id_komisji)


def load_parameters(cur):
    query = """INSERT INTO public.parametry(
            parametr_niskodochodowy, oprocentowanie_uslug)
            VALUES (1.5, 4.2);"""
    cur.execute(query)
    print(query)


def main():
    conn = db_connect()
    cur = conn.cursor()

    load_committees(cur)
    load_roles(cur)
    load_workers(cur)
    load_budgets(cur)
    load_uses(cur)
    load_parameters(cur)
    load_opieka_medyczna(cur)
    load_refundacja_wakacji(cur)
    load_impreza_kulturalna(cur)
    load_zapomoga(cur)
    load_pomoc_mieszkaniowa(cur)
    load_attachments(cur)

    conn.commit()
    cur.close()
    conn.close()


if __name__ == "__main__":
    main()
