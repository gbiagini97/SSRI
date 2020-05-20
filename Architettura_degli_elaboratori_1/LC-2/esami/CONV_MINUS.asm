CONV_MINUS  

; INPUT
; R0 = prima cella di memoria contenente una stringa
; A=65
; Z=90

; OUTPUT
; R0 = contatore lettere cambiate

        st R1,saveR1    ; registro caricamento 
        st R2,saveR2    ; charA
        st R3,saveR3    ; charZ
        st R4,saveR4    ; contatore
        st R5,saveR5    ; registro di appoggio
        st R6,saveR6    ; registro per il delta 32

        LD  R2,charA
        LD  R3,charZ
        LD  R6,delta

        AND R4,R4,#0

loop    LDR R1,R0,#0    ; carico la lettera ascii
        BRZ end
        ADD R5,R1,R2    ; sommo il valore negato della lettera A
        BRNP char        ; se e' positivo allora puo' essere una lettera


char    ADD R5,R5,R6    ; sommo il valore negato di 
        BRNZ maiusc     ; se e' nullo o negativo allora e' una lettera maiuscola
        BRP

maiusc  ADD R1,R1,R6
        STR






saveR1  .blkw   1
saveR2  .blkw   1
saveR3  .blkw   1
saveR4  .blkw   1

charA       .fill   -65
charZ       .fill   -90
delta       .fill   32