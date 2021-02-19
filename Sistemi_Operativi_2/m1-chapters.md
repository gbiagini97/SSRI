Indirizzamento memoria centrale:
    * indirizzo fisico: indirizzo base + indirizzo logico
    * compilatore e linker definiscono lo spazio di indirizzamento logico - linking
    * l'operazione di caricamento associa il valore logico a quello fisico - binding
      *  binding statico:
         *  compilazione - all'interno del codice
         *  caricamento - caricamento statico con rilocazione del codice durante il caricamento
         *  esecuzione - caricamento statico con rilocazione del codice in esecuzione (MMU)
      *  binding dinamico: caricamento in memoria di una porzione di programma - librerie

Partizionamento:
    * spazio di indirizzamento di processi e os =  memoria centrale
    * partizioni statiche al bootstrap
    * partizioni dinamiche in esecuzione
    * frammentazione

Overlaying:
    * porzioni di codice usate sempre vs porzioni in mutua esclusione
    * porzioni con dimensioni omogenee 
    * operazioni di verifica da parte del compilatore
    * caricamento e scaricamento massivi - overlay multipli
    * sottopartizionamento - overlay gerarchici

Swapping:
    * liberare memoria occupata da processi in wait
    * gestita da os
    * step:
      * identificazione dei processi in wait
      * salvataggio in area di swap
      * rimozione memoria centrale
      * caricamento di nuovi processi

Paginazione:
    * pagina fisica (frame) = pagina logica (pagina)
    * tabella delle pagine: tabella[pagina] = frame
    * gestione:
      * solo le pagine che servono nell'immediato vanno in memoria centrale
      * le pagine possono non essere contigue
      * le pagine non caricate sono in area di swap
      * i frame modificati vengono salvati in swap prima di essere rimossi
    * os gestisce in maniera trasparente
    * MMU contiene tabella delle pagine, se non c'e' una pagina lancia TRAP
    * tabella delle pagine troppo grande:
      * translation look-aside buffer - memoria associativa che contiene le ultime pagine
      * tabella gerarchica: porzione ridotta della tabella caricata in MMU (localita')
      * tabella con hashing: accodamenti in caso di collisione
      * tabella invertita: tabellainvertita[frame] = processo, pagina logica
    * protezione delle pagine dai processi - bit di protezione
    * condivisione - codice condiviso

Segmentazione:
    * tipizzazione degli spazi di indirizzamento logici
    * memoria centrale fisica divisa in frame
    * spazio di indirizzamento del processo diviso in segmenti logici - bidimensionale
    * tabella dei segmenti[segmento] = frame, dimensione segmento
    * gestione:
      * solo i segmenti che servono nell'immediato vanno in memoria centrale
      * i segmenti possono essere non contigui
      * i segmenti non caricati sono in area di swap
      * i frame modificati vengono salvati in swap prima di essere rimossi
    * il prorgammatore configura i segmenti tramite strutturazione del programma in moduli
    * compilatore e linker generano segmenti diversi per codice/dati/tabellasimboli/stack/heap
    * MMU contiene tabella dei segmenti
    * l'accesso da parte di un processo a memoria fuori dai propri segmenti: segmentation fault
    * bit di protezione RW/R/X
    * condivisione - codice condiviso
    * frammentazione esterna della memoria - garbage collection

Memoria virtuale:
    * astrazione sulla memoria centrale fisica
    * virtualizzazione - ogni processo puo' usare tutto lo spazio di indirizzamento della cpu
    * memoria virtuale come somma degli spazio di indirizzamento di tutti i processi
    * spazio di indirizzamento dei processi diviso in porzioni
    * memoria centrale divisa in frame
    * caricamento pagine tramite stringa di riferimento - sequenza pagine richieste dal processo
    * scaricamento pagine sull'area di swap se modificato (tranne frame residenti - per os)
    * sostituzione pagine:
      * locale - il processo seleziona frame da scaricare solo tra i frame a lui assegnati
      * globale - il processo seleziona frame da scaricare tra tutti i frame
      * step:
        * scaricamento pagina
        * miglioramento del bit di modifica
        * caricamento pagina
        * aggiornamento tabella delle pagine
    * politiche selezione scaricamento:
      * First In First Out - frame piu' vecchio
      * Sostituzione ottima - frame che non sara' usato per tanto tempo (stringa di riferimento)
      * Last Recently Used - frame meno usato recentemente
      * Reference Bits - bit di riferimento a 0 (decadimento dei bit a 1)
      * Second Chance - RiferimentoModifica R0M0 sost. R0M1 salv. R1M0 presto in uso R1M1 presto in uso, salv.
      * Least Frequently Used - meno frequentemente (decadimento dei contatori)
      * Most Frequently Used -  con contatore maggiore
    * politiche selezione caricamento:
      * richiesta esplicita da parte del sistema
      * previsione delle pagine che saranno richieste (n pagine successive o stringa riferimento)
    * algoritmi allocazione frame per processo:
      * omogenea - numero frame = numero processi / frame totali
      * proporzionale - numero frame = frame totali * dimensione processo / sommatoria dimensione processi
      * priorita' - numero frame = frame totali * priorita' processo / sommatoria priorita' processi
    * thrashing:
      * spreco di tempo di gestione per elevati cambiamenti di pagina
      * prevenzione tramite identificazione del numero di frame per contenere la localita' del processo:
        * working set - identificazione delle pagine usate recentemente nel tempo di esecuzione
        * page fault frequency - maggiore numero di frame disponibili = minore page fault
      * ottimizzazione delle prestazioni:
        * prepaginazione - caricamento in anticipo delle pagine (es. working set o stringa riferimento)
        * dimensionamento pagina 
        * translation look-aside buffer - memoria associativa come cache
        * tabella invertita di pagine 
        * strutturazione del programma - agire sulla localita'
        * pagine residenti per I/O
        * pagine residenti per processi in tempo reale