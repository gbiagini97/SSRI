SOST_CHAR

; INPUT
; R0 indirizzo prima cella di memoria stringa terminata con 0
; R1 ascii lettera minuscola da eliminare
; R2 ascii lettera minuscola da inserire


; sostituire le lettere
; se la lettera da eliminare compare maiuscola, bisogna inserirla maiuscola


        st  R3,saveR3   ; registro di lettura
        st  R4,saveR4   ; registro di appoggio
        st  R5,saveR5   ; valore delta (32)

        NOT R1,R1   
        ADD R1,R1,#1    ; nego il valore da confrontare
        LD  R5,delta    ; carico il delta minusc-maiusc

loop    LDR R3,R0,#0    ; leggo il char dalla stringa
        BRZ end         ; se e' zero esci
        
        ADD R4,R1,R5    ; calcolo il valore della lettera maiuscola
        NOT R4,R4
        ADD R4,R4,#1    ; cambio segno alla lettera maiuscola

        ADD R4,R3,R4    ; tolgo al valore letto la lettera maiuscola
        BRZ maiuscola   ; trovata maiuscola
        ADD R4,R3,R1    ; sommo il valore letto al negato della lettera minuscola
        BRZ minuscola   ; trovata minuscola
     
next    ADD R0,R0,#1    ; incrementa l'indice
        BRNZP loop

minuscola
        STR R2,R0,#0    ; scrivi minuscola
        BRNZP next

maiuscola
        ADD R4,R2,R5    ; carica la maiuscola
        STR R4,R0,#0    ; scrivi maiuscola
        BRNZP next

end     LD  R3,saveR3
        LD  R4,saveR4
        LD  R5,saveR5
        RET

    
saveR3  .blkw   1
saveR4  .blkw   1
saveR4  .blkw   1
delta  .fill   -32
