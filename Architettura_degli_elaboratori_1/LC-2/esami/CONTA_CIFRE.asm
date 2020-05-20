CONTA_CIFRE

; INPUT
; R0 indirizzo prima cella di memoria contenente una stringa S terminata da 0
; R1 indirizzo della prmima cella di un gruppo di 10 celle che costituiscono l'array C


; OUTPUT
; Calcolare quante volte sono ripetute le cifre da 0 a 9 nell'array C

            st R1,saveR1
            st R2,saveR2    ; index di C 
            st R3,saveR3    ; registro di caricamento char di S
            st R4,saveR4    ; registro di controllo numero

            AND R2,R2,#0
            ADD R2,R2,#10

            AND R4,R4,#0

;inizializzo a 0 i valori di C

init        STR R4,R1,#0
            ADD R1,R1,#1    ; aumento il riferimento per la cella di memoria successiva
            ADD R2,R2,#-1   ; diminuisco l'indice
            BRP init

loop        LDR R3,R0,#0    ; carico il valore letto
            BRZ end
            ADD R2,R2,#9    ; carico il valore 9
            ld  R1,saveR1   ; riparto dalla posizione iniziale di C
            ADD R1,R1,#10

check       AND R4,R4,#0    ; carico lo zero
            ADD R4,R4,R2    ; sommo il valore tra 0 e 9
            NOT R4,R4       ; cambio segno
            ADD R4,R4,#1
            ADD R3,R4,R3    ; sommo il valore letto col negato del valore ascii nel numero
            BRZ found
            ADD R2,R2,#-1   ; diminuisco il valore ascii
            ADD R1,R1,#-1   ; diminuisco la posizione del contatore
            BRP check       ; controllo il numero successivo
next        ADD R0,R0,#1    
            BRNZP loop      ; controllo il char successivo

found       LDR R3,R1,#0    ; leggo il valore vecchio
            ADD R3,R3,#1    ; aumento di 1
            STR R3,R1,#0    ; ricarico il nuovo valore
            ADD R1,R1,#-1   ; diminuisco la posizione del contatore
            BRNZP next

end         ld R1,saveR1
            ld R2,saveR2    
            ld R3,saveR3    
            ld R4,saveR4    
            RET
            
saveR1      .blkw   1
saveR2      .blkw   1
saveR3      .blkw   1
saveR4      .blkw   1
