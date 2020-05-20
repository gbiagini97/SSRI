CONTAVOC_MAIU

; INPUT
; R0 prima cella zona di memoria stringa S terminata con 0
; R1 prima cella di 5 libere dell'array C

; OUTPUT
; C[1] = contatore A=65
; C[2] = contatore E=69
; C[3] = contatore I=73
; C[4] = contatore O=79
; C[5] = contatore U=85

        st  R2,saveR2       ; leggo il char dalla stringa
        st  R3,saveR3       ; char holder e confronti

        AND R3,R3,#0

        STR R3,R1,#0
        STR R3,R1,#1
        STR R3,R1,#2
        STR R3,R1,#3
        STR R3,R1,#4

loop    LDR R2,R0,#0    
        BRN end
A       ld  R3,charA
        ADD R3,R2,R3
        BRN trovA
E       ld  R3,charE
        ADD R3,R2,R3
        BRN trovE
I       ld  R3,charI
        ADD R3,R2,R3
        BRN trovI
O       ld  R3,charO
        ADD R3,R2,R3
        BRN trovO
U       ld  R3,charU
        ADD R3,R2,R3
        BRN trovU
next    ADD R0,R0,#1
        BRNZP loop        
              
trovA   LDR R3,R1,#0
        ADD R3,R3,#1
        STR R3,R1,#0
        BRNZP next
trovE   LDR R3,R1,#1
        ADD R3,R3,#1
        STR R3,R1,#1
        BRNZP next
trovI   LDR R3,R1,#2
        ADD R3,R3,#1
        STR R3,R1,#2
        BRNZP next
trovO   LDR R3,R1,#3
        ADD R3,R3,#1
        STR R3,R1,#3
        BRNZP next
trovU   LDR R3,R1,#4
        ADD R3,R3,#1
        STR R3,R1,#4
        BRNZP next

end     ld  R2,saveR2
        ld  R3,saveR3
        RET

charA   .fill   -65
charE   .fill   -69
charI   .fill   -73
charO   .fill   -79
charU   .fill   -85

saveR2  .blkw   1
saveR3  .blkw   1