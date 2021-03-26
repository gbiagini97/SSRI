SELECT I.NOME_BATT, I.COGNOME
FROM IMPIEGATO AS I
WHERE EXISTS (
	SELECT * 
    FROM PERSONA_A_CARICO AS C
    WHERE I.SSN=C.SSN_I AND I.SESSO=C.SESSO
    AND I.NOME_BATT=C.NOME_PERSONA_A_CARICO
);

SELECT * FROM IMPIEGATO;
----------------------------------------------
SELECT I.NOME_BATT, C.NOME_PERSONA_A_CARICO
FROM 	PERSONA_A_CARICO AS C,
		IMPIEGATO AS I
WHERE	I.SSN=C.SSN_I AND I.SESSO=C.SESSO;
----------------------------------------------

/* 
I7: Si elenchino i nomi dei dipendenti dirigenti di dipartimento che hanno almeno una persona a carico
*/

-- Versione con le EXISTS
SELECT I.NOME_BATT, I.COGNOME, I.SSN
FROM IMPIEGATO AS I
WHERE 
	EXISTS (
		SELECT * 
		FROM PERSONA_A_CARICO AS C
		WHERE I.SSN = C.SSN_I 
    )
	AND EXISTS (
		SELECT *
        FROM DIPARTIMENTO AS D
        WHERE I.SSN=D.SSN_DIR
    );

-- Versione con le IN
SELECT NOME_BATT, COGNOME, SSN
FROM IMPIEGATO
WHERE SSN IN (
	SELECT SSN_I 
	FROM PERSONA_A_CARICO 
	WHERE SSN_I IN ( 
		SELECT SSN_DIR 
		FROM DIPARTIMENTO
	)
);

------------------------------------------
/*
I3: Si recuperi il nome di ogni dipendente che lavora su tutti i progetti controllati dal dipartimento numero 5
*/


-- Versione con la COUNT (un po' brutta)
SELECT S.SSN_I, COUNT(*)
FROM LAVORA_SU AS S
WHERE S.N_P IN (
	SELECT P.NUMERO_P 
	FROM PROGETTO AS P 
	WHERE P.NUM_D=5
)
GROUP BY S.SSN_I
HAVING COUNT(*) = (
	SELECT COUNT(*)
    FROM PROGETTO AS P
    WHERE P.NUM_D = 5
);


-- Versione con le JOIN e ALL, molto meglio
SELECT I.NOME_BATT, I.COGNOME
FROM IMPIEGATO AS I
JOIN DIPARTIMENTO AS D ON (I.N_D=D.NUMERO_D)
JOIN LAVORA_SU AS S ON (I.SSN=S.SSN_I)
WHERE S.N_P=ALL (
	SELECT P.NUMERO_P
	FROM PROGETTO P
    WHERE NUM_D=5
);


-- Trova il dipendente che ha lavorato meno di tutti (sommando tutte le ore di lavoro sui progetti)
WITH DIPENDENTI_ORE AS (
	SELECT S.SSN_I, SUM(S.ORE) AS SOMMA
	FROM LAVORA_SU AS S
	GROUP BY S.SSN_I
) 	
SELECT D_O.SSN_I, I.NOME_BATT, I.COGNOME
FROM DIPENDENTI_ORE AS D_O, IMPIEGATO AS I
WHERE SOMMA = (
	SELECT MIN(SOMMA)
	FROM DIPENDENTI_ORE
) AND D_O.SSN_I=I.SSN;






 

