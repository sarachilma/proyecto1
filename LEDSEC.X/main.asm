; PIC18F4550 Configuration Bit Settings

; Assembly source line config statements

#include "p18f4550.inc"

; CONFIG1L
  CONFIG  PLLDIV = 1            ; PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
  CONFIG  CPUDIV = OSC1_PLL2    ; System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
  CONFIG  USBDIV = 2            ; USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

; CONFIG1H
  CONFIG  FOSC = INTOSCIO_EC    ; Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)


    ORG     0x00            ; Vector de reset
    GOTO    INICIO            ; Salta al inicio del programa

INICIO:
    ; Configuración del oscilador interno a 31 kHz
    ; OSCCON está en el Banco 1
    MOVLW   0x07              ; Configura el registro OSCCON para 31 kHz
    MOVWF   OSCCON            ; OSCCON está en el Banco 1

    ; Configura RB0, RB1, RB2 y RB3 como salidas
    ; TRISB está en el Banco 1
    MOVLW   0xF0              ; 11110000 en binario (RB0, RB1, RB2, RB3 como salidas, los demás como entradas)
    MOVWF   TRISB             ; TRISB está en el Banco 1
    CLRF    LATB              ; Limpia el puerto B
    
MAIN_LOOP:
    ; Enciende RB0, apaga los demás
    MOVLW   0x01              ; 00000001 en binario (RB0 en alto)
    MOVWF   LATB              ; Actualiza el puerto B
    CALL    RETARDO_1S        ; Llama a la rutina de retardo de 1 segundo

    ; Enciende RB1, apaga los demás
    MOVLW   0x02              ; 00000010 en binario (RB1 en alto)
    MOVWF   LATB              ; Actualiza el puerto B
    CALL    RETARDO_1S        ; Llama a la rutina de retardo de 1 segundo

    ; Enciende RB2, apaga los demás
    MOVLW   0x04              ; 00000100 en binario (RB2 en alto)
    MOVWF   LATB              ; Actualiza el puerto B
    CALL    RETARDO_1S        ; Llama a la rutina de retardo de 1 segundo

    ; Enciende RB3, apaga los demás
    MOVLW   0x08              ; 00001000 en binario (RB3 en alto)
    MOVWF   LATB              ; Actualiza el puerto B
    CALL    RETARDO_1S        ; Llama a la rutina de retardo de 1 segundo

    GOTO    MAIN_LOOP         ; Repite el ciclo

; Rutina de retardo de 1 segundo
RETARDO_1S:
    MOVLW   0x9B              ; Carga el valor 255 en W
    MOVWF   CONTADOR1         ; Carga el valor en el contador 1
RETARDO_LOOP1:
    MOVLW   0x0A              ; Carga el valor 255 en W
    MOVWF   CONTADOR2         ; Carga el valor en el contador 2
RETARDO_LOOP2:
    DECFSZ  CONTADOR2, F      ; Decrementa CONTADOR2, salta si es cero
    GOTO    RETARDO_LOOP2     ; Repite el bucle interno
    DECFSZ  CONTADOR1, F      ; Decrementa CONTADOR1, salta si es cero
    GOTO    RETARDO_LOOP1     ; Repite el bucle externo
    RETURN                    ; Retorna de la rutina de retardo

; Variables
CONTADOR1 EQU 0x20            ; Reserva espacio para el contador 1
CONTADOR2 EQU 0x21            ; Reserva espacio para el contador 2

    END                       ; Fin del programa


