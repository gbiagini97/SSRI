CONTA_PARI_DISPARI

; INPUT
; R0 indirizzo prima cella di memoria con sequenza di numeri
; R1 ultima cella della sequenza


; OUTPUT
; R0 quanti numeri pari
; R1 quanti numeri dispari

        st  R2,saveR2   ; lettura
        st  R3,saveR3   ; conta pari
        st  R4,saveR4   ; conta dispari

        NOT R1,R1
        ADD R1,R1,#1    ; nego l'ultimo indirizzo della cella

        AND R3,R3,#0    ; inizializzo contatore pari
        ADD R4,R3,#0    ; inizializzo contatore dispari

loop    ADD R2,R0,R1    ; sommo l'ultimo valore della sequenza
        BRZ end         ; se zero esci

        LDR R2,R0,#0    ; carico elemento della sequenza
        AND R2,R2,#1    ; controllo se dispari
        BRP dispari
        ADD R3,R3,#1    ; aumento contatore pari
next    ADD R0,R0,#1    ; passo all'elemento successivo
        BRNZP loop

dispari ADD R4,R4,#1    ; aumento contatore dispari
        BRNZP next

end     ADD R0,R4,#0
        ADD R1,R4,#0
        LD  R2,saveR2
        LD  R3,saveR3
        LD  R4,saveR4
        RET

saveR2  .blkw   1
saveR3  .blkw   1
saveR4  .blkw   1