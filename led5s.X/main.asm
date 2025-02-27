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

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
  
  
    ORG     0x00            ; Vector de reset
    GOTO    INICIO            ; Salta al inicio del programa

INICIO:
    ; Configuración del oscilador interno a 31 kHz
    ; OSCCON está en el Banco 1
    MOVLW   0x07              ; Configura el registro OSCCON para 31 kHz
    MOVWF   OSCCON            ; OSCCON está en el Banco 1

    ; Configura RB0 como salida
    ; TRISB está en el Banco 1
    MOVLW   0x00             ; 11111110 en binario (RB0 como salida, los demás como entrada)
    MOVWF   TRISB             ; TRISB está en el Banco 1
    CLRF    LATB
    
MAIN_LOOP:
    ; PORTB está en el Banco 0
    BSF     PORTB, 0          ; Enciende el LED (RB0 en alto)
    CALL    RETARDO_5S        ; Llama a la rutina de retardo de 5 segundos
    BCF     PORTB, 0          ; Apaga el LED (RB0 en bajo)
    CALL    RETARDO_2S        ; Llama a la rutina de retardo de 2 segundos
    GOTO    MAIN_LOOP         ; Repite el ciclo

; Rutina de retardo de 5 segundos
RETARDO_5S:
    MOVLW   0x05              ; Carga el valor 5 en W (5 iteraciones de 1 segundo)
    MOVWF   CONTADOR3         ; Carga el valor en el contador 3
RETARDO_5S_LOOP:
    CALL    RETARDO_1S        ; Llama a la rutina de retardo de 1 segundo
    DECFSZ  CONTADOR3, F      ; Decrementa CONTADOR3, salta si es cero
    GOTO    RETARDO_5S_LOOP   ; Repite el bucle
    RETURN                    ; Retorna de la rutina de retardo

; Rutina de retardo de 2 segundos
RETARDO_2S:
    MOVLW   0x02              ; Carga el valor 2 en W (2 iteraciones de 1 segundo)
    MOVWF   CONTADOR4         ; Carga el valor en el contador 4
RETARDO_2S_LOOP:
    CALL    RETARDO_1S        ; Llama a la rutina de retardo de 1 segundo
    DECFSZ  CONTADOR4, F      ; Decrementa CONTADOR4, salta si es cero
    GOTO    RETARDO_2S_LOOP   ; Repite el bucle
    RETURN                    ; Retorna de la rutina de retardo

; Rutina de retardo de 1 segundo
RETARDO_1S:
    MOVLW   0x9B              ; Carga el valor 155 en W
    MOVWF   CONTADOR1         ; Carga el valor en el contador 1
RETARDO_LOOP1:
    MOVLW   0x0A              ; Carga el valor 10 en W
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
CONTADOR3 EQU 0x22            ; Reserva espacio para el contador 3
CONTADOR4 EQU 0x23            ; Reserva espacio para el contador 4

    END                       ; Fin del programa
