CONTA_SE

; R0 prima cella di memoria
; R1 ultima cella di memoria
; R2 numero N

; contare quante volte compare nell'array il numero N
; inserire in R0 il conteggio

; contare quante volte compare nell'array l'opposto di N
; inserire in R1 il conteggio


        st  R3,saveR3   ; contatore N
        st  R4,saveR4   ; contatore opposto N
        st  R5,saveR5   ; registro per caricare elemento dell'array
        st  R6,saveR6   ; registro di controllo per valutare se sono arrivato all'ultima cella

; azzero i contatori
        AND R3,R3,#0
        AND R4,R4,#0    

; cambio segno all'indirizzo dell'ultima cella
        NOT R1,R1
        ADD R1,R1,#1
    

loop    ADD R6,R0,R1    ; sommo i valori degli indirizzi
        BRZ end         ; se la somma e' zero allora sono arrivato alla fine dell'array

        LDR R5,R0,#0    ;carico il valore della cella
        BRN neg
        
        ;qua positivo
        NOT R5,R5
        ADD R5,R5,#1    ;cambio segno al valore letto
        ADD R5,R5,R2    ;sommo N con l'input
        BRZ uguale
        BRNZP next



neg     ADD R5,R5,R2    ;numero negativo, sommo con N in input  
        BRZ opposto     ; se la somma fa zero allora e' opposto

opposto ADD R4,R4,#1    ;incremento il contatore
        BRZP next
        
uguale  ADD R3,R3,#1    ; incremento il contatore
        BRNZP   next



next    ADD R0,R0,#1
        BRNZP loop


end     ADD R0,R3,#0
        ADD R1,R4,#0
        ld  R3,saveR3
        ld  R4,saveR4
        ld  R5,saveR5
        ld  R6,saveR6
        RET


saveR3  .blkw   1
saveR4  .blkw   1
saveR5  .blkw   1
saveR6  .blkw   1