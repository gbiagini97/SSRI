INS_ORD

; INPUT
; R0 prima cella di memoria sequenza ordinata (crescente)
; R1 indirizzo dell'ultima cella di memoria dell'ultimo numero della sequenza
; R2 N

; OUTPUT
; R0 prima cella di memoria sequenza ordinata (crescente)
; R1 indirizzo dell'ultima cella di memoria dell'ultimo numero della sequenza
; R2 N

        st  R0,saveR0
        st  R3,saveR3   ;
        st  R4,saveR4   ;
        st  R5,saveR5   ;

        ADD R1,R1,#1
        NOT R1,R1
        ADD R1,R1,#1    ; cambio segno ad R1 per capire
                        ; che sono arrivato alla fine

loop    LDR R3,R0,#0    ; leggo l'elemento della sequenza
        NOT R3,R3
        ADD R3,R3,#1    ; cambio il segno
        ADD R3,R3,R2    ; sommo N in input
        BRN inserisci   ;
        ADD R0,R0,#1    ; incremento il contatore
        BRNZP loop

inserisci
        LDR R4,R0,#0
        STR R0,R2,#0
        BRNZP   next

loop2   LDR R3,R0,#0
        STR R0,R4,#0
        
next    ADD R5,R0,R1
        BRZ end
        ADD R0,R0,#1
        BRNZP loop2

end     ld  R0,saveR0
        ld  R3,saveR3   
        ld  R4,saveR4
        ld  R5,saveR5
        RET

saveR0  .blkw   1
saveR3  .blkw   1
saveR4  .blkw   1
saveR5  .blkw   1