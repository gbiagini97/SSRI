TROVARRAY

; INPUT
; R0 array A
; R1 array B

; OUTPUT
; R0 inizio sottosequenza, oppure zero

            st  R2,saveR2   ; appoggio A
            st  R3,saveR3   ; appoggio B
            st  R4,saveR4   ; indice inizio sequenza
            st  R5,saveR5   ; indice A

            AND R4,R4,#0
            ADD R5,R4,#0    

loop        LDR R2,R0,#0    ; carico elemento di A
            BRZ end
            LDR R3,R0,#0    ; carico elemento di B
            BRZ end
            NOT R3,R3       ; cambio segno elemento di b
            ADD R3,R3,#1

            ADD R3,R2,R3    ; sommo gli elementi
            BRZ seq         ; trovato il match 
            AND R4,R4,#0    ; se non matchano azzero l'indice di inizio sequenza

next        ADD R0,R0,#1
            ADD R5,R5,#1    ; incremento l'indice A
            BRNZP loop

seq         AND R4,R4,R4    ; controllo se la sequenza e' gia' iniziata
            ADD R1,R1,#1
            BRZ inizioSeq
            BRP next

inizioSeq   ADD R4,R5,#0    ; carico la posizione di inizio sequenza
            BRNZP next

end         ADD R0,R4,#0
            LD  R2,saveR2
            LD  R3,saveR3
            LD  R4,saveR4
            LD  R5,saveR5
            RET
            
saveR2      .blkw   1
saveR3      .blkw   1
saveR4      .blkw   1
saveR5      .blkw   1