GRAFFE

; INPUT 
; R0 = indirizzo prima cella di memoria contenente una sequenza di caratteri ascii
; R1 = indirizzo ultima cella di memoria della sequenza

; OUTPUT
; R0 = graffe aperte - graffe chiuse


        st  R2,saveR4   ; ascii graffe aperte
        st  R3,saveR3   ; ascii graffe chiuse
        st  R4,saveR4   ; registro di caricamento
        st  R5,saveR5   ; registro di appoggio
        st  R6,saveR6   ; contatore graffe aperte - chiuse

        NOT R1,R1
        ADD R1,R1,#1

        ld  R2,grafA
        ld  R3,grafB

        AND R6,R6,#0

loop    ADD R4,R0,R1    
        BRZ end 
        LDR R4,R0,#0
        NOT R4,R4
        ADD R4,R4,#1
        ADD R5,R4,R2
        BRZ aperte
        ADD R5,R4,R3
        BRZ chiuse
next    ADD R0,R0,#1
        BRNZP loop

aperte  ADD R6,R6,#1
        BRNZP next       

chiuse  ADD R6,R6,#-1
        BRNZP next
        
end     ADD R0,R6,#0
        ld  R2,saveR4 
        ld  R3,saveR3 
        ld  R4,saveR4 
        ld  R5,saveR5 
        ld  R6,saveR6 
        RET
        
saveR2  .blkw   1
saveR3  .blkw   1
saveR4  .blkw   1
saveR5  .blkw   1

grafA   .fill   x7B
grafC   .fill   x7D