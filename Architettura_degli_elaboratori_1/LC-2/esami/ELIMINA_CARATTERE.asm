ELIMINA_CARATTERE

;R0 inizio cella array
;R1 inteno n positivo
;R2 codice ascii di un carattere da eliminare

        st  R3,saveR3   ;op
        st  R4,saveR4   ;index counter
        st  R5,saveR5   ;char counter 

        and R4,R4,#0
        and R5,R5,#0

loop    ldr R3,R0,#0    ;leggo il valore
        brz loop2init   ;se e' finito vado al secondo loop
        not R3,R3
        add R3,R3,#1    ;nego il valore letto
        add R3,R3,R2    ;sommo il valore di N 
        brz charFound

charFound
        add R3,R3,R1    ;se nullo controllo se sono ad N=0
        add R4,R4,#1    ;aggiorno l'index counter
        not R5,R1
        add R5,R5,#1    ;ho una copia negata di R1 in R5
        add R5,R3,R5    
        brz loop2init   ;se la somma di R3 e R5 fa zero vuol dire che 
                        ;ho trovato il char da cancellare
        brnp loop
        
loop2init
        add R0,R0,R4    ;parto dalla posizione trovata

loop2   ldr R3,R0,#0
        str 





fine    ld  R3,saveR3
        ld  R4,saveR4
        ld  R5,saveR5
        ret


saveR3  .blkw   1
saveR4  .blkw   1
saveR5  .blkw   1
