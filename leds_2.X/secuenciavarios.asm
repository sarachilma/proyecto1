; Configuracio?n del procesador
PROCESSOR 18F4550
#include <p18f4550.inc>

CONFIG  FOSC = INTOSCIO_EC    ; Oscilador interno 8 MHz
CONFIG  PWRT = ON             ; Power-up Timer habilitado
CONFIG  WDT = OFF             ; Watchdog Timer deshabilitado
CONFIG  LVP = OFF             ; Low Voltage Programming deshabilitado

; Variables para retardos
CBLOCK 0x20
    count1      ; Contador interno
    count2      ; Contador interno
    count3      ; Contador externo
ENDC

ORG 0x00
    GOTO INICIO

ORG 0x08
    GOTO INICIO

; Subrutina para configurar el oscilador interno a 8 MHz
INICIO:
    CLRF PORTB               ; Limpiar el puerto B
    MOVLW 0x76               ; Configurar OSCCON para 8MHz
    MOVWF OSCCON
    MOVLW 0x00
    MOVWF TRISB              ; Configurar PORTB como salida

BUCLE:
;enciende rb0
    BSF PORTB, 0
    CALL RETARDO_1S
    BCF PORTB, 0

    ; enciende RB1 y esperar 1s
    BSF PORTB, 1
    CALL RETARDO_1S
    BCF PORTB, 1

    ; enciende RB2 y esperar 1s
    BSF PORTB, 2
    CALL RETARDO_1S
    BCF PORTB, 2

    ; eniceinde RB1 de nuevo y esperar 1s
    BSF PORTB, 1
    CALL RETARDO_1S
    BCF PORTB, 1

    GOTO BUCLE               


;  Retardo de 1 segundo
RETARDO_1S:
    MOVLW 25                 ; 25 iteraciones de 40ms = 1s
    MOVWF count3
L3:
    CALL RETARDO_40MS        ; Llamar retardo de 40ms
    DECFSZ count3, f
    GOTO L3
    RETURN


;  Retardo de aproximadamente 40ms

RETARDO_40MS:
    MOVLW 100
    MOVWF count1
L40MS_1:
    MOVLW 250
    MOVWF count2
L40MS_2:
    NOP
    NOP
    DECFSZ count2, f
    GOTO L40MS_2
    DECFSZ count1, f
    GOTO L40MS_1
    RETURN

END


