# Gestione della memoria centrale
## Tecniche di base di primo livello
### Indirizzamento in memoria centrale
#### Indirizzi logici e indirizzi fisici
#### Collegamento degli indirizzi logici agli indirizzi fisici
#### Binding statico - Fase di compilazione
#### Binding statico - Fase di caricamento
#### Binding statico - Fase di esecuzione
#### Binding dinamico
### Partizionamento
#### Tecnica del partizionamento della memoria centrale
#### Obiettivi
#### Partizioni
#### Partizioni fisse (Statiche)
#### Partizioni variabili (Dinamiche)
#### Caratteristiche - Frammentazione
### Overlaying
#### Tecnica dell'overlaying della memoria centrale
#### Obiettivi
#### Caratteristiche
### Swapping
#### Tecnica dello swapping della memoria centrale
#### Obiettivi
#### Gestione
#### Estensione dello swapping
## Tecniche di base di secondo livello
### Paginazione[1]
#### Obiettivi
#### Tecnica di paginazione
#### Gestione
#### Supporti
### Paginazione[2]
#### Memoria ausiliaria di traduzione (Translation Look-Aside Buffer)
#### Tabella gerarchica delle pagine
#### Tabella delle pagine con hashing
#### Tabella invertita delle pagine
#### Condivisione delle pagine
### Segmentazione
#### Problemi
#### Obiettivi
#### Tecnica della segmentazione
#### Gestione
#### Supporti hardware
#### Protezione dei segmenti
#### Condivisione dei segmenti
#### Frammentazione
### Segmentazione con paginazione
#### Obiettivi
#### Tecnica della segmentazione con paginazione della memoria centrale
#### Gestione
#### Supporti hardware
## Memoria virtuale
### Concetti e tecniche fondamentali
#### Problemi di uso della memoria centrale fisica
#### Obiettivi
#### Concetto di memoria virtuale
#### Tecniche per la realizzazione della memoria virtuale
### Tecniche di sostituzione della pagina
#### Meccanismo di caricamento delle pagine
#### Meccanismo di scaricamento delle pagine
#### Sostituzione delle pagine
#### Politiche di selezione delle pagine da scaricare
#### Politiche di selezione delle pagine da caricare
### Tecniche di allocazione dei frame
#### Allocazione dei frame ai processi
#### Algoritmi di allocazione
### Thrashing
#### Fenomeno del thrashing
#### Tecniche di gestione
##### Tecnica del Working-Set
##### Tecninca del Page Fault Frequency
### Ottimizzazione delle prestazioni
#### Prepaginazione
#### Dimensionamento della pagina
#### Translation Look-aside Buffer
#### Tabella invertita delle pagine
#### Strutturazione del programma
#### Pagine residenti per dispositivi di I/O
#### Pagine residenti per processi in tempo reale



# Gestione dell'ingresso / uscita
## Sottosistemi di ingresso / uscita
### Struttura e funzioni dei sottosistemi di ingresso / uscita
#### Tipologie di periferiche
#### Caratteristiche delle periferiche
#### Software di gestione delle periferiche
##### Gestione del canale di comunicazione
##### Device Dependent Driver
##### Device Independent Driver
### Realizzazione del sottosistema di I/O
#### Funzioni di gestione
##### Schedulazione operazioni
##### Bufferizzazione
##### Caching
##### Spooling
##### Locking
##### Gestione errori
#### Strutture dati
#### Realizzazione di una richiesta di I/O
#### Prestazioni dell'I/O
## Gestione delle memorie di massa
### Schedulazione degli accessi al disco
#### Tempo di accesso al disco
#### Larghezza di banda
#### Obiettivi
#### Algoritmi di schedulazione degli accessi
##### First Come / First Served - FCFS
##### Shortest Seek Time First - SSTF
##### Scansione - Algoritmo dell'ascensore - SCAN
##### Circula Scan - CSCAN
##### Ricerca - LOOK
#### Selezione dell'algoritmo di schedulazione
### Organizzazione del disco
#### Configurazione del disco
##### Formattazione fisica
##### Partizionamento
##### Formattazione logica di ciascuna partizione
#### Blocco di avvio
#### Blocchi difettosi
#### Gestione dell'area di swap
### Dischi RAID
#### Obiettivi
##### Costi
##### Ridondanza
##### Mean Time To/Between Failure - MTTF/MTBF
##### Parallelismo
#### Livelli RAID
##### RAID 0
##### RAID 1
##### RAID 2
##### RAID 3
##### RAID 4
##### RAID 5
##### RAID 6
##### RAID 0+1 e RAID 1+0
### Memoria terziaria
#### Obiettivi
#### Periferiche di archiviazione terziaria
#### Gestione della memoria terziaria



# File system
## Interfaccia del file system
### File e le loro caratteristiche
#### File system
#### Aggregazione di informazioni
#### Concetto di file
#### Tipi di file
#### Struttura dei file
#### Attributi
#### Operazioni
#### Uso del file
#### Metodo di accesso
##### Accesso sequenziale
##### Accesso diretto
##### Accesso indicizzato
### Direttori e le loro caratteristiche
#### Concetto di direttorio
#### Operazioni sui direttori
#### Struttura del file system
##### Direttorio a singolo livello
##### Direttorio a due livelli
##### Visione logica del file system
##### Direttorio ad albero
##### Direttorio a grafo aciclico
##### Direttorio a grafo generale
#### Memorie di massa a dischi multipli
#### Memorie di massa con grossi dischi
#### Partizioni
#### Montaggio del file system
### Condivisione dei file e protezione
#### Condivisione dei file
#### Sistemi multi-utente
#### File system remoti
##### Trasferimento di file con modalita' anonima o autenticata
#### File system in rete
#### Coerenza
##### Coerenza in caso di guasti
#### Protezione
##### Controllo dell'accesso
## Implementazione del file system
### Struttura e realizzazione
#### Obiettivo
#### Supporto fisico del file system
#### Visione utente delle informazioni nel file system
#### File system
#### Struttura della gestione del file system
#### Strutture dati per la gestione del file system
##### Strutture dati su disco
##### Strutture dati in memoria centrale
##### Apertura file
##### Lettura file
##### File system virtuali
### Realizzazione dei direttori
#### Tecniche per la realizzazione dei direttori
##### Lista
##### Tabella di hash
### Realizzazione dei file: Gestione all'astrazione dei file
#### Visione logica del file
#### Visione fisica del file
#### Mapping della visione logica sulla visione fisica
#### Visione logica omogenea del file
#### Mapping del byte stream
#### Gestione dell'astrazione dei file
##### Apertura
##### Lettura
##### Scrittura
##### Posizionamento (Seek)
##### Chiusura
### Realizzazione del file system: allocazione dei blocchi
#### Allocazione dei blocchi fisici
##### Allocazione contigua
##### Allocazione collegata
##### Allocazione indicizzata
#### Miglioramento delle prestazioni per allocazione
#### Gestione dello spazio libero
##### Bitmap (vettore di bit)
##### Lista collegata
##### Conteggio
### Valutazione dell'efficienza e delle prestazioni del sistema
#### Efficienza
#### Tecniche per migliorare l'efficienza
#### Prestazioni
#### Tecniche per migliorare le prestazioni
### Manutenzione del file system
#### Errori nel file system
#### Coerenza del file system
#### Backup e ripristino del file system
## Protezione
### Concetti fondamentali della protezione
#### Obiettivi
#### Domini di protezione
#### Associazione processo-dominio
### Tecniche di realizzazione della protezione
#### Realizzazione dei domini di protezione
#### Matrice degli accessi
#### Liste di controllo degli accessi
#### Liste dei capacita' dei domini
#### Revoca dei diritti
#### Confronto
#### Meccanismo serratura-chiave
#### Sistemi operativi basati sulle capacita'
#### Protezione basata sul linguaggio


    
# Sistemi distribuiti
## Funzioni di un sistema distribuito
### Obiettivi e funzioni
#### Architetture di elaborazione distribuite
#### Sistemi operativi per architetture di elaborazione distribuite
#### Sistema operativo di rete
#### Sistema operativo distribuito
#### Robustezza
#### Aspetti progettuali
## Comunicazioni in rete
### Protocolli di comunicazione
#### Problemi
#### Obiettivi
#### Soluzione
#### Modello teorico
#### Strato fisico 
#### Strato data-link
#### Strato rete
#### Strato trasporto
#### Strato sessione
#### Strato presentazione
#### Strato applicazione
#### Pila del protocollo ISO/OSI
#### Messaggi nel protocollo ISO/OSI
#### Modelli reali
#### Relazione tra TCP/IP, UDP/IP e ISO/OSI
#### Internet Protocol (IP)
#### Protocolli di trasporto 
#### Strati TCP/IP
## Computazione distribuita
### Distribuzione della computazione
#### Motivazioni
#### Obiettivi
#### Tecniche per la distribuzione della computazione
#### Tecniche di supporto alla computazione distribuita
### Chiamata di procedura remota
#### Obiettivo
#### Chiamata di procedura remota
#### Realizzazione
#### Vantaggi
#### Problemi
#### Esempio di uso delle RPC
#### Invocazione di un metodo remoto
### Allocazione dei processi
#### Obiettivi
#### Allocazione statica
#### Allocazione dinamica
### Agenti mobili
#### Obiettivi
#### Modello della computazione ad oggetti
#### Modello della computazione ad agenti
#### Agenti mobili
### Coordinamento distribuito tra processi
#### Sincronizzazione dei processi
#### Relazione 'accaduto prima'
#### Ordinamento globale
#### Marca di tempo
#### Orologio logico
#### Mutua esclusione
#### Atomicita'
#### Concorrenza
##### Protocolli bloccanti
#### Coordinatore
##### Algoritmo del bullo
##### Algoritmo dell'anello
### Deadlock in ambiente distribuito
#### Prevenzione dello stallo
#### Marche di tempo con rilascio della risorsa
##### Schema wait-die
##### Schema wound-wait
#### Rilevamento dello stallo
##### Grafo di attesa in ambiente distribuito
##### Grafo di attesa centralizzato
##### Algoritmo di rilevamento centralizzato
##### Algoritmo di rilevamento distribuito
##### Problema di gestione della rilevazione
#### Gestione dello stallo
### Comunicazione tra processi in rete
#### Scambio di messaggi
#### Mailbox
#### File
#### Socket
#### Realizzazione
## File system distribuiti
### Struttura e funzioni
#### Obiettivi
#### Network File System - NFS
#### Distributed File System - DFS
#### Nomi dei file
#### Accesso ai file
#### Stato del file server
#### Replica dei 