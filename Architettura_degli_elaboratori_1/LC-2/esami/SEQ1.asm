SEQ1

; INPUT
; R0=intero N


; OUTPUT
; R0=ennesimo termine di S(N)

; S(N) = 2 x |S(n-1)| - 2 x S(n-2)
; S(1) = 1
; S(2) = 1

        ;salvataggio registri
        st  R1,saveR1       ; S(N-2)
        st  R2,saveR2       ; S(N-1)
        st  R3,saveR3       ; -2 x S(N-2)
        st  R4,saveR4       ; 2 x |S(N-1)|
        st  R5,saveR5       ; S(N)
        st  R6,saveR6       ; contatore

        NOT R0,R0
        ADD R0,R0,#1        ; cambio segno all'intero N per interropere il ciclo

        AND R1,R1,#0
        ADD R1,R1,#1        ; inizializzo S(N-2)
        ADD R2,R1,#0        ; inizializzo S(N-1)

        AND R5,R5,#0        ; inizializzo S(N) con N = 3

        ADD R6,R6,#1        ; inizializzo il contatore

loop    ADD R1,R2,#0        ; sposto con n-1
        ADD R2,R5,#0        ; sposto con n-1
        BRN mod             ; se negativo
calc    ADD R4,R2,R2        ; calcola 2 x |S(N-1)|
        ADD R3,R1,R1        ; calcola 2 x S(n-2)
        NOT R3,R3
        ADD R3,R3,#1        ; calcola  - 2 x S(n-2)
        ADD R5,R3,R4        ; calcola S(N)
        BRNZP next
        
mod     NOT R2,R2           ; calcola valore assoluto
        ADD R2,R2,#1
        BRNZP calc

next    ADD R6,R6,#1        
        ADD R1,R0,R6
        BRN end
        BRZP loop


end     ADD R0,R5,#0
        ld  R1,saveR1
        ld  R2,saveR2
        ld  R3,saveR3
        ld  R4,saveR4
        ld  R5,saveR5
        ld  R6,saveR6
        RET

        saveR1  .blkw   1
        saveR2  .blkw   1
        saveR3  .blkw   1
        saveR4  .blkw   1
        saveR5  .blkw   1   
        saveR6  .blkw   1