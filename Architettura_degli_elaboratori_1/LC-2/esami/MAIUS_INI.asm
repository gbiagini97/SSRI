MAIUS_INI

;R0 indirizzo della prima cella
;La stringa e' terminata da 0

        st  R0,saveR0
        st  R1,saveR1
        st  R2,saveR2

ciclo   ldr R1,R0,#0        ;carico il valore dell'array
        brz fine
        ld  R2,valSpazio    ;carico il valore dello valSpazio
        add R2,R1,R2
        brz maiusc
        add R0,R0,#1
        brznp ciclo

maiusc  add R0,R0,#1
        add R1,R1,#-32
        str R1,R0,#0    
        brznp ciclo

fine    ld  R0,saveR0
        ld  R1,saveR1
        ld  R2,saveR2   
        ret

saveR0  .blkw   1
saveR1  .blkw   1
saveR2  .blkw   1

valSpazio   .fill   -32