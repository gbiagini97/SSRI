TROVA_OCCORRENZA

; INPUT
; R0 infirizzo prima cella di memoria stringa S termina con 0
; R1 ascii carattere C
; R2 intero N

; OUPUT
; R0 indice dell'occorrenza
; se non c'e' tornare 0

            st  R3,saveR3   ; carico il carattere
            st  R4,saveR4   ; indice posizione

            AND R4,R4,#0    ; azzero l'indice

            NOT R1,R1
            ADD R1,R1,#1    ; cambio segno al codice ascii del carattere C

loop        LDR R3,R0,#0    ; carico il char
            BRZ end0        ; se trovo 0 esco
            ADD R3,R3,R1    ; controllo il char
            BRZ trovato
next        ADD R4,R4,#1
            ADD R0,R0,#1    
            BRNZP loop

trovato     ADD R2,R2,#-1   ; decremento il numero di occcorrenze trovate
            BRZ end         ; se sono giunto all'ultima esco
            BRP next

end0        AND R4,R4,#0
end         ADD R0,R4,#0    ; metto l'indice in R0
            LD  R3,saveR3
            LD  R4,saveR4
            RET

saveR3  .blkw   1
saveR4  .blkw   1

