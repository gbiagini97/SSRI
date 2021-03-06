INSERT INTO IMPIEGATO VALUES(
    'John', 
    'B',
    'Smith',
    123456789,
    '1965-01-09',
    '731 Fondren, Houston, TX',
    'M',
    30000,
    333445555,
    5   
);


INSERT INTO IMPIEGATO VALUES(
    'Franklin', 
    'T',
    'Wong',
    333445555,
    '1955-12-08',
    '638 Voss, Houston, TX',
    'M',
    40000,
    888665555,
    5   
);


INSERT INTO IMPIEGATO VALUES(
    'Alicia', 
    'J',
    'Zelaya',
    999887777,
    '1968-07-19',
    '3321 Castle, Spring, TX',
    'F',
    25000,
    987654321,
    4   
);


INSERT INTO IMPIEGATO VALUES(
    'Jennifer', 
    'S',
    'Wallace',
    987654321,
    '1941-06-20',
    '291 Benny, Bellaire, TX',
    'F',
    43000,
    888665555,
    4   
);


INSERT INTO IMPIEGATO VALUES(
    'Ramesh', 
    'K',
    'Narayan',
    666884444,
    '1962-09-15',
    '975 Fire Oak, Humble, TX',
    'M',
    38000,
    333445555,
    5   
);


INSERT INTO IMPIEGATO VALUES(
    'Joyce', 
    'A',
    'English',
    453453453,
    '1972-07-31',
    '5631 Rice, Houston, TX',
    'F',
    25000,
    333445555,
    5   
);


INSERT INTO IMPIEGATO VALUES(
    'Ahmad', 
    'V',
    'Jabbar',
    987987987,
    '1969-03-29',
    '980 Dallas, Houston, TX',
    'M',
    25000,
    987654321,
    4   
);


INSERT INTO IMPIEGATO VALUES(
    'James', 
    'E',
    'Borg',
    888665555,
    '1937-11-10',
    '450 Stone, Houston, TX',
    'M',
    55000,
    NULL,
    1   
);

SELECT * FROM IMPIEGATO;



INSERT INTO DIPARTIMENTO VALUES ('Ricerca',5,333445555,'1988-05-22');
INSERT INTO DIPARTIMENTO VALUES ('Amministrazione',4,987654321,'1995-01-01');
INSERT INTO DIPARTIMENTO VALUES ('Sede Centrale',1,888665555,'1981-06-19');
SELECT * FROM DIPARTIMENTO;


INSERT INTO SEDI_DIP VALUES (1,'Houston');
INSERT INTO SEDI_DIP VALUES (4,'Stafford');
INSERT INTO SEDI_DIP VALUES (5,'Bellaire');
INSERT INTO SEDI_DIP VALUES (5,'Sugarland');
INSERT INTO SEDI_DIP VALUES (5,'Houston');
SELECT * FROM SEDI_DIP;


INSERT INTO LAVORA_SU VALUES (123456789,1,32.5);
INSERT INTO LAVORA_SU VALUES (123456789,2,7.5);
INSERT INTO LAVORA_SU VALUES (666884444,3,40);
INSERT INTO LAVORA_SU VALUES (453453453,1,20);
INSERT INTO LAVORA_SU VALUES (453453453,2,20);
INSERT INTO LAVORA_SU VALUES (333445555,2,10);
INSERT INTO LAVORA_SU VALUES (333445555,3,10);
INSERT INTO LAVORA_SU VALUES (333445555,10,10);
INSERT INTO LAVORA_SU VALUES (333445555,20,10);
INSERT INTO LAVORA_SU VALUES (999887777,30,30);
INSERT INTO LAVORA_SU VALUES (999887777,10,10);
INSERT INTO LAVORA_SU VALUES (987987987,10,35);
INSERT INTO LAVORA_SU VALUES (987987987,30,5);
INSERT INTO LAVORA_SU VALUES (987654321,30,20);
INSERT INTO LAVORA_SU VALUES (987654321,20,15);
INSERT INTO LAVORA_SU VALUES (888665555,20,null);
SELECT * FROM LAVORA_SU;

INSERT INTO PROGETTO VALUES ('ProdottoX',1,'Bellaire',5);
INSERT INTO PROGETTO VALUES ('ProdottoY',2,'Sugarland',5);
INSERT INTO PROGETTO VALUES ('ProdottoZ',3,'Houston',5);
INSERT INTO PROGETTO VALUES ('Informatizzazione',10,'Stafford',4);
INSERT INTO PROGETTO VALUES ('Riorganizzazione',20,'Houston',1);
INSERT INTO PROGETTO VALUES ('Nuove opportunita',30,'Stafford',4);
SELECT * FROM PROGETTO;

INSERT INTO PERSONA_A_CARICO VALUES (333445555,'Alice','F','1986-04-05','FIGLIA');
INSERT INTO PERSONA_A_CARICO VALUES (333445555,'Theodore','M','1983-10-25','FIGLIO');
INSERT INTO PERSONA_A_CARICO VALUES (333445555,'Joy','F','1958-05-03','CONIUGE');
INSERT INTO PERSONA_A_CARICO VALUES (987654321,'Abner','M','1942-02-28','CONIUGE');
INSERT INTO PERSONA_A_CARICO VALUES (123456789,'Michael','M','1988-01-04','FIGLIO');
INSERT INTO PERSONA_A_CARICO VALUES (123456789,'Alice','F','1988-12-30','FIGLIA');
INSERT INTO PERSONA_A_CARICO VALUES (123456789,'Elizabeth','F','1967-05-05','CONIUGE');
SELECT * FROM PERSONA_A_CARICO;

