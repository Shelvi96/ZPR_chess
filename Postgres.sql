CREATE TABLE budzet (
    id_budzetu  SERIAL,
    kategoria   VARCHAR(255),
    prog       NUMERIC(7, 2)
);

ALTER TABLE budzet ADD CONSTRAINT budzet_pk PRIMARY KEY ( id_budzetu );

CREATE TABLE impreza_kulturalna (
    id_uslugi           INTEGER NOT NULL,
    id_imprezy          SERIAL,
    oczekiwana_wartosc  NUMERIC(6, 2) NOT NULL
);

ALTER TABLE impreza_kulturalna ADD CONSTRAINT impreza_kulturalna_pk PRIMARY KEY ( id_imprezy );

CREATE TABLE komisja (
    id_komisji SERIAL
);

ALTER TABLE komisja ADD CONSTRAINT komisja_pk PRIMARY KEY ( id_komisji );

CREATE TABLE opieka_medyczna (
    id_uslugi              INTEGER NOT NULL,
    id_opieki_medycznej    SERIAL,
    oczekiwana_refundacja  NUMERIC(6, 2) NOT NULL
);

ALTER TABLE opieka_medyczna ADD CONSTRAINT opieka_medyczna_pk PRIMARY KEY ( id_opieki_medycznej );

CREATE TABLE parametry (
    parametr_niskodochodowy  NUMERIC(3, 2) NOT NULL,
    oprocentowanie_uslug     NUMERIC(4, 2) NOT NULL
);

CREATE TABLE pomoc_mieszkaniowa (
    id_uslugi                INTEGER NOT NULL,
    id_pomocy_mieszkaniowej  SERIAL,
    oczekiwana_wartosc       NUMERIC(6, 2) NOT NULL,
    dlugosc                  NUMERIC(2)
);

ALTER TABLE pomoc_mieszkaniowa ADD CONSTRAINT pomoc_mieszkaniowa_pk PRIMARY KEY ( id_pomocy_mieszkaniowej );

CREATE TABLE pracownik (
    id_pracownika           SERIAL,
    imie                    VARCHAR(255 ) NOT NULL,
    nazwisko                VARCHAR(255 ) NOT NULL,
    stanowisko              VARCHAR(255 ) NOT NULL,
    data_rozpoczecia_pracy  TIMESTAMP WITH TIME ZONE NOT NULL,
    pesel                   VARCHAR(11) NOT NULL,
    pensja                  NUMERIC(12, 2) NOT NULL,
    komisja_id_komisji      INTEGER NOT NULL
);

ALTER TABLE pracownik ADD CONSTRAINT pracownik_pk PRIMARY KEY ( id_pracownika );

CREATE TABLE refundacja_wakacji (
    id_uslugi            INTEGER NOT NULL,
    id_refundacji        SERIAL,
    wartosc_oczrekiwana  NUMERIC(6, 2) NOT NULL
);

ALTER TABLE refundacja_wakacji ADD CONSTRAINT refundacja_wakacji_pk PRIMARY KEY ( id_refundacji );

CREATE TABLE uslugi (
    id_uslugi          SERIAL,
    rodzaj_uslugi      VARCHAR(255 ) NOT NULL,
    wymagany_dokument  VARCHAR(255 ) NOT NULL,
    max_wartosc        NUMERIC(10, 2)
);

ALTER TABLE uslugi ADD CONSTRAINT uslugi_pk PRIMARY KEY ( id_uslugi );

CREATE TABLE wniosek (
    id_wniosku               SERIAL,
    decyzja                  VARCHAR(255 ) NOT NULL,
    uwaga                    VARCHAR(255 ),
    uwaga_komisji            VARCHAR(255 ),
    data_zlozenia            TIMESTAMP WITH TIME ZONE NOT NULL,
    data_zamkniecia          TIMESTAMP WITH TIME ZONE NOT NULL,
    pracownik_id_pracownika  INTEGER NOT NULL,
    uslugi_id_uslugi         INTEGER NOT NULL,
    komisja_id_komisji       INTEGER NOT NULL
);

ALTER TABLE wniosek ADD CONSTRAINT wniosek_pk PRIMARY KEY ( id_wniosku );

CREATE TABLE wykorzystanie (
    wykorzystanie            NUMERIC(7, 2),
    niski_dochod             BOOLEAN,
    budzet_id_budzetu        INTEGER NOT NULL,
    pracownik_id_pracownika  INTEGER NOT NULL
);

CREATE TABLE zapomoga (
    id_uslugi           INTEGER NOT NULL,
    id_zapomogi         SERIAL,
    oczekiwana_wartosc  NUMERIC(6, 2) NOT NULL
);

ALTER TABLE zapomoga ADD CONSTRAINT zapomoga_pk PRIMARY KEY ( id_zapomogi );

CREATE TABLE zalaczniki (
    id_zalacznika       SERIAL,
    tresc               VARCHAR(255) NOT NULL,
    wniosek_id_wniosku  INTEGER NOT NULL
);

ALTER TABLE zalaczniki ADD CONSTRAINT zalaczniki_pk PRIMARY KEY ( id_zalacznika );

CREATE TABLE users (
    id         	SERIAL,
    username        VARCHAR(20) NOT NULL,
    email		    VARCHAR(120) NOT NULL,
    password		VARCHAR(60) NOT NULL,
    role            VARCHAR(20) NOT NULL,
    worker_id       INTEGER
);
ALTER TABLE users ADD CONSTRAINT users_pk PRIMARY KEY ( id );

CREATE TABLE roles (
    id         	SERIAL,
    role        VARCHAR(20) NOT NULL
);
ALTER TABLE roles ADD CONSTRAINT roles_pk PRIMARY KEY ( id );

ALTER TABLE users
    ADD CONSTRAINT users_workers_fk FOREIGN KEY ( worker_id )
        REFERENCES pracownik ( id_pracownika );

ALTER TABLE impreza_kulturalna
    ADD CONSTRAINT impreza_kulturalna_uslugi_fk FOREIGN KEY ( id_uslugi )
        REFERENCES uslugi ( id_uslugi );

ALTER TABLE opieka_medyczna
    ADD CONSTRAINT opieka_medyczna_uslugi_fk FOREIGN KEY ( id_uslugi )
        REFERENCES uslugi ( id_uslugi );

ALTER TABLE pomoc_mieszkaniowa
    ADD CONSTRAINT pomoc_mieszkaniowa_uslugi_fk FOREIGN KEY ( id_uslugi )
        REFERENCES uslugi ( id_uslugi );

ALTER TABLE pracownik
    ADD CONSTRAINT pracownik_komisja_fk FOREIGN KEY ( komisja_id_komisji )
        REFERENCES komisja ( id_komisji );

ALTER TABLE refundacja_wakacji
    ADD CONSTRAINT refundacja_wakacji_uslugi_fk FOREIGN KEY ( id_uslugi )
        REFERENCES uslugi ( id_uslugi );

ALTER TABLE wniosek
    ADD CONSTRAINT wniosek_komisja_fk FOREIGN KEY ( komisja_id_komisji )
        REFERENCES komisja ( id_komisji );

ALTER TABLE wniosek
    ADD CONSTRAINT wniosek_pracownik_fk FOREIGN KEY ( pracownik_id_pracownika )
        REFERENCES pracownik ( id_pracownika );

ALTER TABLE wniosek
    ADD CONSTRAINT wniosek_uslugi_fk FOREIGN KEY ( uslugi_id_uslugi )
        REFERENCES uslugi ( id_uslugi );

ALTER TABLE wykorzystanie
    ADD CONSTRAINT wykorzystanie_budzet_fk FOREIGN KEY ( budzet_id_budzetu )
        REFERENCES budzet ( id_budzetu );

ALTER TABLE wykorzystanie
    ADD CONSTRAINT wykorzystanie_pracownik_fk FOREIGN KEY ( pracownik_id_pracownika )
        REFERENCES pracownik ( id_pracownika );

ALTER TABLE zapomoga
    ADD CONSTRAINT zapomoga_uslugi_fk FOREIGN KEY ( id_uslugi )
        REFERENCES uslugi ( id_uslugi );

ALTER TABLE zalaczniki
    ADD CONSTRAINT zalaczniki_wniosek_fk FOREIGN KEY ( wniosek_id_wniosku )
        REFERENCES wniosek ( id_wniosku );
