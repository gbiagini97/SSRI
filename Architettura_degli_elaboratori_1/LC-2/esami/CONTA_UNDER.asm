CONTA_UNDER

; R0 = indirizzo della prima cella di memoria con una sequenza di numeri n(i)
; R1 = indirizzo della cella contenente l'ultimo numero della sequenza n(i)
; R2 = un numero negativo N 

; sostituire ogni numero di n(i) con il risultato della somma n(i) + N
; mettere in R2 il numero di traboccamenti

        st  R3,saveR3   ; registro dove carico l'elemento della sequenza 
        st  R4,saveR4   ; registro dove conto il numero di traboccamenti
        st  R5,saveR5   ; registro dove controllo se sono arrivato alla fine della sequenza
        
        AND R4,R4,#0    ; azzero il contatore



loop    AND R5,R0,R1    ; somma logica per vedere se R0 e R1 coincidono
        BRP end
        LDR R3,R0,#0    ; carico l'elemento i della sequenza in R3
        BRP discordi
        BRN concordi

concordi
        ADD R3,R3,R2    ; sommo il numero negativo n
        BRP trab


trab    ADD R4,R4,#1
        STR R4,R0,#0    ; carico nella sequenza n(i) + N
        BRNZP next


discordi
        ADD R3,R3,R2    ; sommo il numero negativo n
        STR R4,R0,#0    ; carico nella sequenza n(i) + N
        BRNZP next
        

next    ADD R0,R0,#1
        BRNZ loop


end     ADD R2,R4,#0
        ld  R3,saveR3
        ld  R4,saveR4
        ld  R5,saveR5
        RET


        saveR3  .blkw   1
        saveR4  .blkw   1
        saveR5  .blkw   1