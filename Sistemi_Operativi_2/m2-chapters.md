Struttura sottosistemi I/O:
* caratteristiche periferiche:
  * direzione I/O - R/W/RW
  * condivisione - mutua esclusine o condivisibile
  * metodo di accesso - sequenziale o diretto
  * trasferimento dei dati - a carattere o a blocchi
  * schedulazione trasferimento - sincrono o asincrono
  * velocita' dispositivi - latenza, tempo di ricerca, tempo di trasferimento, ritardo tra operazioni
* software gestione periferiche:
  * interfaccia unica con astrazione e virtualizzazione delle periferiche
  * standardizzazione della gestione
  * strato di gestione del canale di comunicazione:
    * garantice che le comunicazioni CPU-periferica siano trasparenti
  * strato di device dependent driver:
    * standardizzare il linguaggio di comando e trattamento di periferiche dello stesso tipo
  * strato di device independent driver:
    * strazione per mostrare tutte le tipologie di periferiche allo stesso modo
* realizzione sottosistema I/O:
  * schedulazione operazioni:
    * ordinamento delle richiestte tramite una coda FIFO/priorita'/scadenza
  * bufferizzazione:
    * adattare le velocita' e la dimensione dei dati durante la comunicazione CPU-periferica
  * caching
  * spooling:
    * bufferizzazione in area di spooling
    * separazione richiesta emissione dei dati / effettiva emissione da parte della periferica
  * locking:
    * prenotazione delle periferiche tramite coda di attesa
  * gestione errori
* strutture dati:
  * tabella di tutti i file aperti e periferiche in uso


Gestione memorie di massa:
* access time = seek time + rotational latency
* bandwidth = byte traferiti / tempo totale trasferimento
* algoritmi di schedulazione degli accessi:
  * First Come / First Served - coda, testina a zigzag
  * Shortest Seek Time First - tempo di accesso minore, percorso ottimo
  * Scan - coda, processamento delle richieste lungo il percorso [0, estremo del disco]
  * Circular Scan - effetto pacman, tempo di attesa uniforme, spostamento della testina senza letture
  * Ricerca/Look - effetto pacman anche se non si sono raggiunti gli estremi del disco
* organizzazione disco:
  * formattazione fisica:
    * formattazione di basso livello
    * suddivisione in settori, ogni settore ha header/dati/terminatore
    * checksum nel terminatore per controllo errori
  * partizionamento:
    * disco in porzioni gestite come dischi logici
    * un disco = una partizione
  * formattazione logica di ogni partizione:
    * formattazione ad alto livello
    * permette creazione file ssytem (oppure raw disk come in area di swap)
  * blocco di avvio - Boot Block:
    * contiene os o un loader
* blocchi difettosi - Bad Block:
  * techinche di sostituzione dei settori guasti:
    * in maniera automatica durante la formattazione
    * Sector Sparing - sostituzione con un blocco spare
    * Sector Forwarding - spare blocks in fondo, spostamento di tutto il disco in avanti
    * Sector slipping - spostamento porzioni di disco in blocco
* gestione area swap:
  * raw disk che contiene processi/pagine/segmenti
  * locazione - partizione dedicata / file regolato dal file system
  * strutturata con una mappa con indici ai blocchi all'interno del disco
* RAID:
  * ridondanza
  * mean time between failure
  * parallelismo negli accessi - data striping:
    * bit level striping
    * block level striping
  * 0 - striping non ridondante
  * 1 - mirroring dei dischi
  * 2 - error correcting codes
  * 3 - bit interleaved parity
  * 4 - block interleaved parity
  * 5 - block interleaved distributed parity
  * 6 - P + Q redundancy
  * 0+1 - mirror di stripe
  * 1+0 - stripe di mirror
* memoria terziaria:
  * veloci/affidabili/basso costo
  * hierarchical storage management:
    * estensione del file system per includere la memoria terziaria
    * univoca denominazione nel file system 