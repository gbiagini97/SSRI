MAIUSC

; R0 contiene l'indirizzo della prima cella di una zona di memoria contennte una stringa di caratteri ASCII

; SOSTITUIRE LE MINUSCOLE CON LE MAIUSCOLE
; mettere in R0 il numero di lettere sostituite
; A=65  a=97
; Z=90  z=112

; salvataggio registri
        
        st  R1,saveR1   ; registro per caricamento carattere
        st  R2,saveR2   ; contatore sostituzioni
        st  R3,saveR3   ; registro contenitore valore -32


        AND R2,R2,#0    ; inizializzo il contatore


loop    
        ld  R3,valSpazio; carico il valore -32 in R3
        LDR R1,R0,#0    ; carico il carattere della stringa 
        BRZ end         ; se e' 0 allora end
        
        ADD R1,R1,R3    ; sottraggo 32 al valore letto
        BRZ next        ; spazio
        
; qui carattere

        AND R3,R1,valZ  ; controllo se e' minore di 90
        BRP next        ; char gia' maiuscolo, vado al char successivo
        ADD R1,R1,R3    ; trasformo da minuscolo a minuscolo

sost    STR R1,R0,#0    ; salvo il nuovo valore ascii nella stringa
        ADD R2,R2,#1
        
next    ADD R0,R0,#1
        BRNZP   loop


; caricamento registri
end     
        ADD R0,R2,#0
        ld  R1,saveR1   
        ld  R2,saveR2
        ld  R3,saveR3
        RET


saveR1  .blkw   1
saveR2  .blkw   1
saveR3  .blkw   1

valSpazio   .fill   #-32
valZ        .fill   #90