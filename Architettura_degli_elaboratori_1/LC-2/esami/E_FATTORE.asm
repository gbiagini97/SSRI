E_FATTORE

; INPUT
; R0 numero N positivo
; R1 numero F positivo

; OUTPUT
; R0 = N/F
; Se F non e' fattore di N tornare 0


        st  R2,saveR2   ; contatore (I)

        NOT R1,R1
        ADD R1,R1,#1    ; cambio segno a F

        AND R2,R2,#0    ; azzero il contatore

loop    ADD R0,R0,R1    ; sottraggo F ad N
        BRN end0        ; se e' negativo, c'e' il resto
        BRZ endN        ; se e' nullo allora e' finito
        ADD R2,R2,#1    
        BRNZP  loop     ; se e' positivo loop

end0    AND R2,R2,#0
        BRNZP end    
endN    ADD R0,R2,#0
end     ld  R2,saveR2
        RET


saveR2  .blkw   1