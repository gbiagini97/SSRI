### Thread
* 3 tipi di attivita': controllo flusso, I/O, elaborazione
* Thread come flussi di controllo dell'esecuzione del programma
* Alta disponibilita'
* Bassi tempi di riposta
* Gestione I/O non bloccante
* Memoria condivisa per lo scambio rapido di informazioni
* Codice/Dati/File condivisi, copia di Stack e Registri
* Benefici: prontezza, condivisione di risorse/informazioni, economia occupazione memoria, economia esecuzione operazioni di accesso, multiprocessore
* Gestione: livello utente/kernel
* Libreria gestione dei Thread
* Supporto ai Thread nel SO
* Molti a uno: serializzazione computazione, basso parallelismo, separazione concettuale
* Uno a uno: massima parallelizzazione, overhead
* Molti a molti: N<M, risolve parallelismo e efficienza
* Due livellli: sottogruppi, specializzazione dei thread
* Cooperazione: simmetrici, gerarchici, pipeline
* Funzioni di gestione: fork, exec, cancellazione asincrona, cancellazione differita
* Comunicazione e sincronizzazione: con tutti, sottoinsieme, uno solo
* Processi leggeri: processori virtuali affidati ai processi, disaccoppiano la gestione del parallelismo dal mappaggio livello utente/kernel ed esecuzione a livello kernel.

### Schedulazione processi
* Livelli: breve/lungo/medio termine
* Attivazione: pre-emption/non pre-emption
* Criteri di valutazione: utilizzo della CPU, throughput, turnaround time
* Metodi di valutazione: analitica, statistica, simulazione, implementazione
* Politiche di schedulazione: FCFS, SJF, Priorita', RR, C+L, C+LR

### Comunicazione processi
* Tipologie processi: indipendenti/cooperanti
* Vantaggi cooperazione: modularita', parallelizzazione, scalabilita', specializzazione, qualita' di progetto
* Comunicazione come insieme di politiche e meccanismi che permettono a due processi di scambiarsi informazioni in modo da realizzare la cooperazione
* Entita' coinvolte + canale di comunicazione
* Caratteristiche per scegliere il canale di comunicazione: quantita', velocita', scalabilita', usabilita', omogeneita', integrazione delle primitive nel codice, affidabilita', sicurezza, protezione
* Implementazione: diretta/indiretta
* Memoria condivisa: variabili globali/buffer, area comune copiata dal SO, area comune fisicamente condivisa
* Messaggi: numero illimitato/limitato/nullo, funzioni, comunicazione simmetrica/asimmetrica
* Mailbox: dimensione illimitata/limitata/nulla, funzioni, piu' mittenti/piu' riceventi
* File condivisi: file su HDD, pipe su memoria centrale + FIFO, ordinamento processi secondo filesystem, comunicazione diretta con un solo processo
* Socket: tronconi pipe, indirizzo + porta, gestione varia a seconda del SO e protocolli

### Sincronizzazione processi
* Problema della mutua esclusione con processi concorrenti
* Sezioni critiche: mutua esclusione, progresso, attesa limitata
* Variabili di turno: turno di una risorsa tra un insieme di processi
* Variabili di lock: stato di utilizzo della risorsa
* Disabilitazione interruzioni
* Implementazione HW: TEST-AND-SET
* Semaforo binario: stato di uso di una risorsa, acquire/release, attesa attiva, sospensione e riattivazione
* Generalizzazione del semaforo: n risorse omogenee
* Monitor: costrutto linguistico di sincronizzazione, informazioni condivise per rappresentare la risorsa comune, operazioni effettuabili sulla risorsa, codice di init dell'ambiente operativo, variabile di condizione

### Deadlock
* Insieme di processi in attesa indefinita di risorse detenuti da altri processi anche loro in attesa di risorse occupate
* Condizioni contemporanee: mutua esclusione, possesso e attesa, no pre-emptio, attesa circolare
* Verificare presenza deadlock
* Grafo allocazione risorse: nodi processi e risorse, archi assegnazioni e richieste, cicli deadlock
* Ignorare
* Prevenzione:
  * Rimuovere mutua esclusione se non necessaria
  * Imporre che il processo non possieda altre risorse quando fa richiesta di risorsa
  * Forzare rilascio anticipato 
  * Ordinamento globale univoco, imponendo rilascio risorse se deve richiederne altre precedenti nell'ordinamento
* Evitare: numero massimo di risorse processo, risorse assegnate, risorse disponibili, richieste e rilasci futuri
  * Stato sicuro: sequenza di processi e' una sequenza sicura se le richieste per ogni processo Pi possono essere soddisfatte dalla risorse disponibili ora + le risorse dei processi <i
  * Passare da uno stato sicuro all'altro
  * Grafo allocazione risorse + arco di prenotazione: ciclo -> stato non sicuro, risorse uniche
  * Algoritmo Banchiere: determina se lo stato e' sicuro per la sequenza di processi considerata che richiedono n istanze di risorse
* Rilevazione e ripristino: deadlock gia' avvenuto
  * Rilevazione con grafo di attesa: dipendenze tra processi dovute al possesso di risorse
  * Se istanze multiple di risorse, algoritmo di verifica effettiva allocazione risorse, valuta se e' possibile terminare l'allocazione risorse, da attivare ogni volta che non si soddisfa la richiesta/intervalli
  * Ripristino tramite abort di tutti i processi/ uno ad uno con politica
  * Ripristino tramite rilascio di risorse con rollback a stato sicuro (starvation)