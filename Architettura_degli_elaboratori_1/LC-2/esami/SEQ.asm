SEQ


; INPUT
; R0 intero N

; OUTPUT
; R0 ennesimo termine S(N)
; S(N) = 4 x S(N - 1) - |S(N - 2)|
; S(1) = 1
; S(2) = 1


            st  R1,saveR1   ; S(N - 2)
            st  R2,saveR2   ; S(N - 1)
            st  R3,saveR3   ; 4 x S(N - 1)
            st  R4,saveR4   ; S(N)

            AND R1,R1,#0
            ADD R1,R1,#1    ; inizializzo con S(1)
            ADD R2,R1,#0    ; inizializzo con S(1)

            ADD R0,R0,#-2   ; poiche ho gia usato 2 valori di N lo decremento
            BRNZ end1       ; se e' gia negativo allosta stacca
            AND R4,R4,#0    ; inizializzo a zero

loop        ADD R0,R0,#-1   ; diminuisco il contatore
            BRNZ endN
            ADD R3,R2,R2    ; 2 x S(N - 1)
            ADD R3,R3,R3    ; 4 x S(N - 1)

            AND R1,R1,R1    ; controllo il segno di S(N - 2)
            BRP positivo
calc        ADD R4,R3,R1    ; calcolo S(N)
next        ADD R2,R4,#0    ; sposto S(N) in S(N - 1)
            ADD R1,R2,#0    ; sposto S(N - 1) in S(N - 2)
            BRNZP loop

positivo    NOT R1,R1
            ADD R1,R1,#1
            BRNZP calc

end1        ADD R0,R1,#0
            BRNZP end

endN        ADD R0,R4,#0
end         ld  R1,saveR1
            ld  R2,saveR2
            ld  R3,saveR3
            ld  R4,saveR4
            RET


saveR1      .blkw   1
saveR2      .blkw   1
saveR3      .blkw   1
saveR4      .blkw   1