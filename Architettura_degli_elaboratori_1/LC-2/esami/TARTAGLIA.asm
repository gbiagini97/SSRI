TARTAGLIA

; INPUT
; R0 prima cella array A di N numeri, terminata da 0
; 0 = N+1

; R1 prima cella array vuoto T lunga N + 1

; Riempire l'array T
; T[1] = 1
; T[N+1] = 1
; T[I] = A[I-1] + A[I]

            st  R2,saveR2   ; elemento I di A
            st  R3,saveR3   ; elemento I+1 di A
            st  R4,saveR4   ; appoggio per somme
            
            LDR R2,R0,#0    ; leggo il primo I di A
            STR R2,R1,#0    ; inserisco il primo I di T

            ADD R0,R0,#1    ; incremento indirizzo a A
            ADD R1,R1,#1    ; incremento indirizzo a T

loop        LDR R3,R0,#0    ; carico I di A
            BRZ end
            ADD R4,R3,R2    ; sommo I con I+1
            STR R4,R1,#0    ; salvo elemento in T
next        ADD R0,R0,#1    ; incremento indirizzo a A
            ADD R1,R1,#1    ; incremento indirizzo a T
            ADD R2,R3,#0    ; sposto R3 in R2
            BRNZP loop            

end         AND R3,R3,#0
            ADD R3,R3,#1
            STR R3,R1,#0
            ld  R2,saveR2
            ld  R3,saveR3   
            ld  R4,saveR4
            RET

saveR2      .blkw   1
saveR3      .blkw   1
saveR4      .blkw   1

