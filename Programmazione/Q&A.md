### Quali sono le caratteristiche di un linguaggio di programmazione?
Un linguaggio di programmazione e' un linguaggio formale che tramite un set di istruzioni puo' produrre dati in output.
Ce ne sono oltre 2500 e sono distinti principalmente dalla famiglia di riferimento:
* Imperativi
* Funzionali
* Logici

A seconda del livello di astrazione sono piu' vicini al linguaggio macchina (basso livello) o a quello umano (alto livello).
___

### Cosa sono i paradigmi di programmazione?
Per paradigma di indica lo stile di programmazione che un linguaggio predilige.
In generale si fa sempre riferimento alle 3 famiglie principali: [imperativo, funzinale, logico](###quali-sono-le-caratteristiche-di-un-linguaggio-di-programmazione?), ma tendenzialmente ogni linguaggio cerca di estendere i concetti di base fornendo strumenti di astrazione ulteriori. 
___

### Cosa sono i costrutti in un linguaggio di programmazione?
Nella programmazione strutturata i costrutti di controllo di un linguaggio sono delle istruzioni sintattiche che permettono di combinare istruzioni elementari creando istruzioni complesse o blocchi di istruzioni mantenendo il **controllo sul flusso** di esecuzione.
I costrutti di controllo fondamentali sono:
* **Esecuzione in sequenza**: il modo piu' semplice per combinare le istruzioni e' farle eseguire una dopo l'altra.
* **Costrutti iterativi**: servono per eseguire dei cicli su un blocco di istruzioni, che verra' eseguito finche' non viene soddisfatta una condizione, che viene controllata ad ogni iterazione.
* **Costrutti di selezione**: a seconda di quanto espresso nella condizione, il programma seleziona da quale alternativa (tra due o piu') riprendere l'esecuzione.
___

### Quali sono i vantaggi della programmazione strutturata?
La programmazione strutturata rappresenta la naturale estensione dell'approccio top down al processo di scrittura del codice. Il modo piu' spontaneo in cui ragiona la mente umana, focalizzandosi sulla scomposizione in sottoproblemi partendo dal quesito generale.
Nella programmazione l'approccio strutturato consente di eliminare completamente dal codice i salti incodizionati che davano vita a spaghetti code.
___

### A cosa serve il teorema di Bohm Jacopini?
Serve a stabilire che un dato programma P, e' possibile costruire un programma strutturato SP equivalente a P. 
Il programma strutturato e' munito di strutture di controllo quali: [sequenza, iterazione e selezione](###quali-sono-le-caratteristiche-di-un-linguaggio-di-programmazione?).
___

### Cosa dimostra il teorema di Ashcroft e Manna?
E' una tecnica dimostrativa del teorema di [Bohm Jacopini](###a-cosa-serve-il-teorema-di-bohm-jacopini?), sfruttando i concetti di programma proprio e scomposizione gerarchica di un programma in sottoprogrammi propri.
La dimostrazione fa leva sul preservare la struttura logica del programma non considerando gli stati iniziale e finale.
Regole per effettuare la trasformazione:
* Il blocco contiene un solo test oppure non contiene cicli.
* Il blocco contiene piu’ di un test e almeno un ciclo:
  * Si identificano i **punti di taglio**, in modo che ciascun ciclo contenga almeno uno di tali punti e che uno di questi sia sull’unica freccia uscente.
  * Si traduce il blocco con un while esterno in modo che ogni iterazione segua l’esecuzione da un punto dell’insieme di taglio successivo.
  * Si introducono variabili booleane necessarie a distinguere tutti i punti di taglio definiti.
  * Il numero di variabili booleane e’ log2n (dove n e’ il numero dei punti di taglio e n e' la base del logaritmo).
___

### Cosa e' lo scope?
Lo scope e' l'ambito di visibilita' di un identificatore (variabile, classe, ecc) e cio' che rende quell'identificatore richiamabile in un determinato punto del programma.
Puo' essere:
* **Locale**: identificatori dichiarati in un determinato blocco e la loro visibilita' termina alla fine del blocco.
* **Globale**: identificatori dichiarati fuori da una funzione (variabili globali). Questi identificatori sono noti a tutte le funzioni dopo la dichiarazione.
___

### Cosa e' il side effect?
Il side effect, o effetto collaterale, avviene quando una funzione modifica il valore di una variabile o cambia lo stato di un programma al di fuori del proprio scope.
___

### Cosa e' la trasparenza referenziale?
Si tratta di un'espressione, dunque anche una funzione, che [**non ha effetti collaterali**](###cosa-e'-il-side-effect?) e che a parita' di parametro di input ritorna sempre lo stesso valore.
Dunque, la suddetta espressione puo' essere sostituita direttamente dal suo valore (**memoizzazione**).
Un'espressione che prende come parametri una o piu' funzioni, e che soddisfa la trasparenza referenziale, si definisce funzione di ordine superiore (**high-order function**).
___

### Cosa si intende per complessita' asintotica?
L'analisi asintotica e' una stima di complessita' computazionale che consente di valutare l'efficienza di un algoritmo in termini di:
* **Tempo**:
  * Numero totale di operazioni elementari eseguite.
  * Indipendente dal tipo di macchina.
  * Tempo necessario uguale per tutte le operazioni.
* **Spazio**:
  * Quantita’ massima di informazioni da mantenere (escludendo dati iniziali e risultati).
  
La crescita del tempo di calcolo cresce all'aumentare della dimensione dell'istanza del problema.
La bonta' di un algoritmo va valutata in base al suo comportamento asintotico ossia quando la dimensione dell'istanza tende all'infinito.
Cio' che interessa veramente non e' la quantita' precisa di risorse necessarie, ma la sua crescita di domanda di risorse al crescere delle dimensioni in ingresso.
Si tiene principalmente conto del caso peggiore (e non il caso medio, tantomeno il migliore).
___

### Cosa sono i parametri formali e quelli attuali?
I **parametri formali** sono quelli che vengono passati come argomento di una funzione al momento della dichiarazione di quella funzione.
L'istanza di quei dati, all'interno della funzione che li elabora genera dei **parametri attuali**.
___

### Cosa sono le funzioni variadiche?
Le funzioni variadiche sono quelle funzioni con **arieta'** variabile, ossia una funzione che puo' accettare un numero variabile di argomenti (ad esempio le operazioni di somma e concatenazione di stringhe).
Bisogna fare caso al tipo delle variabili che immettiamo nelle funzioni **varagrs**, potrebbero non essere supportate per determinate operazioni, per evitare problemi di sicurezza come i **format string attacks**.
___

### Cosa e' il principio di sostituzione di Liskov?
Nella programmazione orientata agli oggetti, il principio di Liskov e' tra i 5 principi del paradigma di design SOLID.
Barbara Liskov, nel 1993, affermo' che: 
> Se q(x) e' una proprieta' che si puo' dimostrare valida per oggetti x di tipo T, allora q(y) deve essere valida per oggetti y di tipo S dove S e' un sottotipo di T.