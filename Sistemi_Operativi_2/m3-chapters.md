Interfaccia del file system:
* file system come astrazione delle informazioni nei dispositivi fisici
* file - costrutore per contenere elementi omogenei in una struttura di dimensione non nota a priori
* descrittore di file - attributi nome/tipo/locazione/dimensione/dataCreaz/proprietario/protezione
* operazioni:
  * apertura:
    * verifica autorizzazioni
    * identificazione descrittore
    * identificazione locazione del file
    * verifica e gestione uso condiviso
    * caricamento delle informazioni di gestione in tabella dei file aperti
  * lettura/scrittura:
    * recupero posizione dei componenti del file tramite tabella dei file aperti
    * puntatore al file per identificare l'elemento corrente
    * blocco per accesso condiviso
  * chiusura:
    * aggiornamento informazioni di gestione
    * rilascio uso condiviso
    * cancellazione n tabella dei file aperti
* metodi di accesso:
  * scansione sequenziale con riavvolgimento
  * accesso diretto
  * accesso indicizzato - ricerca in un indice, utile per la compattazione
* direttori - collezione omogenea di attributi su gruppi di file (array di descrittori)
* struttura del file system:
  * singolo livello
  * due livelli (utente-direttori)
  * albero
  * grafo aciclico
  * grafo generale
* memorie di massa:
  * dischi multipli astratti con un unico file system
  * dischi grossi partizionati
  * montaggio del file system come associazione radice-punto di montaggio
* condivisione e protezione
  * autenticazione in ambienti multi-utente
  * file system in rete:
    * client/server -  FTP/HTTP
    * distribuiti - gestione trasparente
    * gestione della coerenza
    * controllo degli accessi:
      * ACL
      * Capabilities List
      * Password


Implementazione del file system:
* astrazione e gestione omogenea delle risorse informative e fisiche
* moduli os per gestione del file system:
  * gestione della periferica - canale comunicazione / dependent driver / independent driver
  * file system di base - organizzazione delle operazioni lettura/scrittura e memorizzazione
  * organizzazione dei file - concatena blocchi fisici per creare la visione del flusso di elementi logici
  * file system logico - astrazione del reperimento delle informazioni sul file system
* strutture dati per gestione file system:
  * su disco:
    * blocco controllo del boot
    * blocco controllo della partizione
    * direttori
    * blocchi di controllo dei file
  * su memoria centrale
    * tabella delle partizioni
    * descrittori dei direttori
    * tabella file aperti nel sistema
    * tabella file aperti per processo
    * tabella monitoraggio file system
* file system virtuali
* realizzazione direttori con lista/tabella di hash
* realizzazione file:
  * visualizzazione tramite record logici
  * byte stream:
    * visione logica omogenea a prescindere dalla tipizzazione
    * visione logica -> byte stream -> visione fisica
    * finestra di visualizzazione
  * gestione astrazione:
    * apertura
      * byte stream - posizione 0
      * blocchi fisici - primo blocco
    * lettura:
      * posizione byte stream = blocchi fisici
      * scorrimento finestra
    * scrittura:
      * spooling fino a riempire un blocco fisico
    * posizionamento/seek:
      * spostamento finestra
    * chiusura:
      * eventuale salvataggio se modificato
      * libera spazio nelle strutture dati
* allocazione blocchi:
  * allocazione contigua:
    * ordinamento sequenziale
    * accesso rapido al blocco successivo
    * accesso diretto lento (Scansione lineare)
    * frammentazione interna e esterna
  * allocazione collegata:
    * lista di blocchi con puntatori
    * no frammentazione esterna
    * accesso diretto lento
    * introduzione FAT con puntatori ai blocchi
  * allocazione indicizzata:
    * i-node con sequenza dei puntatori ai blocchi
    * no frammentazione esterna
    * accesso diretto e alta affidabilita
    * dimensione del blocco:
      * schema collegato - lista di indici
      * indice multilivello - indice su indici
      * schema combinato
  * miglioramento prestazioni - caching/read-ahead
  * gestione spazio libero: bitmap/lista collegata/conteggio
* miglioramento efficienza::
  * cluster dimensione variabile per ridurre frammentazione interna
  * dimensionamento blocchi/puntatori/metadati
  * FAT specifiche
* miglioramento prestazioni:
  * algoritmi di gestione semplici
  * supporti hardware - cache disco/pagine, vuffer cache, memoria virtuale unificata
* manutenzione file system:
  * controllore di coerenza dati e metadati scritti in modo sincrono
  * backup completo o incrementale
  * ripristino 
  * sistemi orientati al logging / journaling


Protezione:
* regole e meccanismi di utilizzo
* domini di protezione - coppie <Risorsa, Diritti>
* associazione processo dominio statica/dinamica
* revoca diritti
* realizzazione della protezione:
  * matrice completa degli accessi
  * liste di controllo accessi (colonne)
  * liste di capacita' dei domini (righe)
  * lock-key