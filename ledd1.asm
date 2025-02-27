; CONFIG1H
  CONFIG  FOSC = INTOSCIO_EC    ; Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
    
LIST P=18F4550                ; Especificamos el microcontrolador PIC18F4550
#include <p18f4550.inc>       ; Incluimos el archivo de definici�n para el PIC18F4550

; Configuraci�n del oscilador interno a 8 MHz
ORG 0x00                      ; La rutina comienza en la direcci�n 0x00
GOTO Main                      ; Saltamos a la etiqueta Main

; Configuraci�n de la memoria y los registros
ORG 0x04                      ; Direcci�n donde se ejecutar� el programa despu�s del reset
Main:
    ; Configuraci�n del oscilador
    ; La configuraci�n es 01110110, que corresponde a 0x76
    MOVLW   0x76               ; Cargamos el valor 0x76 (01110110) en el registro W
    MOVWF   OSCCON             ; Guardamos el valor de configuraci�n en el registro OSCCON

    ; Configuraci�n de RB1 como salida
    CLRF    TRISB              ; Configuramos todo el puerto B como salida
    BSF     TRISB, 1           ; Configuramos el pin RB1 como salida

    ; Rutina principal
MainLoop:
    ; Encender RB1
    BSF     LATB, 1            ; Set RB1 en alto (encender LED)

    ; Bucle infinito
    GOTO    MainLoop           ; Volver al inicio del bucle

END



