;Encender led
    
; PIC18F4550 Configuration Bit Settings

#include "p18f4550.inc"

CONFIG  FOSC = INTOSCIO_EC    ; Oscilador interno a 8 MHz
CONFIG  WDT = OFF             ; Deshabilitar Watchdog Timer
CONFIG  PBADEN = OFF          ; Configurar PORTB como digital
CONFIG  LVP = OFF             ; Deshabilitar programación de baja tensión

; -------------------------------------------------
; Código Principal
; -------------------------------------------------

ORG 0x00
    GOTO INICIO   ; Salta a la rutina principal

; -------------------------------------------------
; Rutina Principal
; -------------------------------------------------
INICIO:
    BSF TRISB, 0   ;
    BCF LATB,0     ;
    BSF LATB, 0    ; Enciende el LED en RB0

END


