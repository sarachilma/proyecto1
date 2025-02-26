
; PIC18F4550 Configuration Bit Settings

; Assembly source line config statements

#include "p18f4550.inc"

  CONFIG  FOSC = INTOSCIO_EC    ; Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))

  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))

  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)

COUNT1  RES 1  ; Reserva 1 byte de memoria para COUNT1
COUNT2  RES 1  ; Reserva 1 byte de memoria para COUNT2
COUNT3  RES 1  ; Reserva 1 byte de memoria para COUNT3

    ORG 0x00        ; Dirección de reinicio del programa
    GOTO START      ; Salta a la rutina principal

    ORG 0x100       ; Dirección donde comienza el código principal

START:
    ;Configura el oscilador interno
    MOVLW 0x72      ; Carga en W el valor para configurar 
    MOVWF OSCCON     ; Configura el archivo del oscilador
    ; Configura el puerto B para salida
    CLRF PORTB      ; Pone todos los pines de PORTB en bajo
    MOVLW 0x00      ; Carga en W el valor para configurar como salida
    MOVWF TRISB     ; Configura PORTB como salida (0 = salida)

LOOP:
    BSF LATB, 0     ; Enciende el LED en RB0
    CALL DELAY_5S   ; Llama a la subrutina de retardo de 5 segundos
    BCF LATB, 0     ; Apaga el LED en RB0
    CALL DELAY_2S   ; Llama a la subrutina de retardo de 2 segundos
    GOTO LOOP       ; Vuelve al inicio del bucle

; Subrutina para generar un retardo de 5 segundos
DELAY_5S:
    MOVLW D'50'     ; 50 ciclos de 100ms
    MOVWF COUNT1    ; Guarda en COUNT1
DELAY_LOOP_5S:
    CALL DELAY_100MS ; Llama a la subrutina de retardo de 100ms
    DECFSZ COUNT1, F ; Decrementa COUNT1, si es cero, sale del bucle
    GOTO DELAY_LOOP_5S ; Si no es cero, repite el ciclo
    RETURN          ; Retorna al código principal

; Subrutina para generar un retardo de 2 segundos
DELAY_2S:
    MOVLW D'20'     ; 20 ciclos de 100ms
    MOVWF COUNT1    ; Guarda en COUNT1
DELAY_LOOP_2S:
    CALL DELAY_100MS ; Llama a la subrutina de retardo de 100ms
    DECFSZ COUNT1, F ; Decrementa COUNT1, si es cero, sale del bucle
    GOTO DELAY_LOOP_2S ; Si no es cero, repite el ciclo
    RETURN          ; Retorna al código principal

; Subrutina para generar un retardo de 100ms
DELAY_100MS:
    MOVLW D'255'    ; Contador para el bucle externo
    MOVWF COUNT2    ; Guarda en COUNT2
LOOP1:
    MOVLW D'255'    ; Contador para el bucle interno
    MOVWF COUNT3    ; Guarda en COUNT3
LOOP2:
    NOP             ; No operation (1 ciclo)
    DECFSZ COUNT3, F ; Decrementa COUNT3, si no es cero, repite
    GOTO LOOP2      ; Repite LOOP2 hasta que COUNT3 sea cero
    DECFSZ COUNT2, F ; Decrementa COUNT2, si no es cero, repite
    GOTO LOOP1      ; Repite LOOP1 hasta que COUNT2 sea cero
    RETURN          ; Retorna al código principal

    END                ; Fin del programa



