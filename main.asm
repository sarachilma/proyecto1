;Encender 5 seg y apagar 2 seg

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
COUNT3  RES 1   ; Reserva 1 byte de memoria para COUNT3

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
    CLRF TRISB        ; Configurar PORTB como salida
    MOVLB 0           ; Volver al banco 0

LOOP:
    BSF LATB, 0       ; Encender LED en RB0
    CALL DELAY_5S     ; Esperar 5 segundos
    BCF LATB, 0       ; Apagar LED en RB0
    CALL DELAY_2S     ; Esperar 2 segundos
    GOTO LOOP         ; Repetir ciclo

; -----------------------------
; Rutina de Retardo de 5 Segundos
; -----------------------------
DELAY_5S:
    MOVLW D'5'        ; 5 ciclos de 1 segundo
    MOVWF COUNT3
DELAY_1S_LOOP:
    CALL DELAY_1S
    DECFSZ COUNT3, F
    GOTO DELAY_1S_LOOP
    RETURN

; -----------------------------
; Rutina de Retardo de 2 Segundos
; -----------------------------
DELAY_2S:
    MOVLW D'2'        ; 2 ciclos de 1 segundo
    MOVWF COUNT3
DELAY_2S_LOOP:
    CALL DELAY_1S
    DECFSZ COUNT3, F
    GOTO DELAY_2S_LOOP
    RETURN

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


