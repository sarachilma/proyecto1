;Secuencia de 3 leds

; PIC18F4550 Configuration Bit Settings
#include "p18f4550.inc"

CONFIG  FOSC = INTOSCIO_EC    ; Usa el oscilador interno a 8 MHz
CONFIG  WDT = OFF             ; Deshabilitar Watchdog Timer
CONFIG  PBADEN = OFF          ; Configurar PORTB como digital
CONFIG  LVP = OFF             ; Deshabilitar programación de baja tensión

; ------------------------------------------
; Definición de variables en memoria UDATA
; ------------------------------------------
UDATA
COUNT1  RES 1   ; Reserva 1 byte de memoria para COUNT1
COUNT2  RES 1   ; Reserva 1 byte de memoria para COUNT2

; ------------------------------------------
; Código principal
; ------------------------------------------
ORG 0x00
    GOTO INICIO   ; Salto a la rutina principal

; -----------------------------
; Rutina Principal
; -----------------------------
INICIO:
    MOVLB 1           ; Seleccionar banco 1
    CLRF TRISB        ; Configurar PORTB como salida (todo como salida)
    MOVLB 0           ; Volver al banco 0
    CLRF LATB         ; Apagar todos los LEDs al inicio

LOOP:
    ; Encender LEDs en secuencia
    BSF LATB, 0       ; Encender LED en RB0
    CALL DELAY_1S     ; Esperar 1 segundo
    BCF LATB, 0       ; Apagar LED en RB0

    BSF LATB, 1       ; Encender LED en RB1
    CALL DELAY_1S     ; Esperar 1 segundo
    BCF LATB, 1       ; Apagar LED en RB1

    BSF LATB, 2       ; Encender LED en RB2
    CALL DELAY_1S     ; Esperar 1 segundo
    BCF LATB, 2       ; Apagar LED en RB2

    ; Apagar LEDs en orden inverso
    BSF LATB, 2       ; Encender LED en RB2
    CALL DELAY_1S     ; Esperar 1 segundo
    BCF LATB, 2       ; Apagar LED en RB2

    BSF LATB, 1       ; Encender LED en RB1
    CALL DELAY_1S     ; Esperar 1 segundo
    BCF LATB, 1       ; Apagar LED en RB1

    BSF LATB, 0       ; Encender LED en RB0
    CALL DELAY_1S     ; Esperar 1 segundo
    BCF LATB, 0       ; Apagar LED en RB0

    GOTO LOOP         ; Repetir ciclo

; -----------------------------
; Rutina de Retardo de 1 Segundo (Ajustado para 8 MHz)
; -----------------------------
DELAY_1S:
    MOVLW D'125'       
    MOVWF COUNT1
DELAY_1S_LOOP1:
    MOVLW D'200'
    MOVWF COUNT2
DELAY_1S_LOOP2:
    NOP
    DECFSZ COUNT2, F
    GOTO DELAY_1S_LOOP2
    DECFSZ COUNT1, F
    GOTO DELAY_1S_LOOP1
    RETURN

END



