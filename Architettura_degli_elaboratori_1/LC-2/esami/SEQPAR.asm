SEQPAR;

; INPUT
; R0 = numero intero N
; R1 = intero positivo P

; OUTPUT
; R0 = ennesimo termine della sequenza S(N)
; S(N) = S(N - 1) + P x S(N - 2)


        st  R2,saveR2   ; S(N - 1)
        st  R3,saveR3   ; S(N - 2)
        st  R4,saveR4   ; P x S(N - 2)
        st  R5,saveR5   ; S(N)
        st  R6,saveR6   ; contatore

        AND R2,R2,#0    ; azzero il registro contenente S(N - 1)
        AND R3,R3,#0    ; azzero il registro contenente S(N - 2)
        AND R5,R5,#0    ; azzero il registro contenente S(N)

        AND R0,R0,R0
        BRNZ  end       ; controllo se N passato in input e' positivo

        ADD R2,R2,#1    ; inizializzo S(N - 1) ad 1
        ADD R3,R3,#1    ; inizializzo S(N - 2) ad 1

loop    ADD R6,R1,#0    ; copio il valore di P per usarlo come contatore per la moltiplicazione

loopm   ADD R4,R3,R3    ; moltiplicazione
        ADD R6,R6,#-1   ; diminuisco il contatore
        BRP loopm

calc    ADD R5,R4,R2    ; calcolo il valore di S(N)

next    ADD R0,R0,#-1   ; decremento N
        BRN end
        ADD R3,R2,#0    ; sposto S(N - 1) a S(N - 2)
        ADD R2,R5,#0    ; sposto S(N) a S(N - 1)
        BRNZP loop


end     ADD R0,R5,#0
        ld  R2,saveR2
        ld  R3,saveR3
        ld  R4,saveR4
        ld  R5,saveR5
        ld  R6,saveR6
        RET


saveR2  .blkw   1
saveR3  .blkw   1
saveR4  .blkw   1
saveR5  .blkw   1
saveR6  .blkw   1