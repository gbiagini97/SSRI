CONTA_VOLTE

; INPUT
; R0 prima cella di memoria contenente una stringa ascii
; R1 codice ascii di una lettera minuscola

; OUTPUT
; R0 contatore minuscola
; R1 contatore maiuscola

        st  R2,saveR2
        st  R3,saveR3   ; contatore minuscola
        st  R4,saveR3   ; contatore maiuscola
        st  R5,saveR5   ; holder 32

        AND R3,R3,#0
        AND R4,R4,#0

        NOT R1,R1
        ADD R1,R1,#1    

        ld  R5,num

loop    LDR R2,R0,#0
        BRZ end
        ADD R2,R2,R1    ; qui sottraggo il codice ascii delle due lettere
        BRZ minuscola
        ADD R2,R2,R5
        BRZ maiuscola
        BRNZP next

minuscola
        ADD R3,R3,#1
        BRNZP next

maiuscola
        ADD R4,R4,#1
        BRNZP next

next    ADD R0,R0,#1
        BRNZP   loop
        
end 
        ADD R0,R3,#0
        ADD R1,R4,#0
        ld  R2,saveR2
        ld  R3,saveR3
        ld  R4,saveR4
        ld  R5,saveR5
        RET

saveR2  .blkw   1
saveR3  .blkw   1
saveR4  .blkw   1
saveR5  .blkw   1
num     .fill   #32