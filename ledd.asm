; CONFIG1H
  CONFIG  FOSC = INTOSCIO_EC    ; Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
  CONFIG  FCMEN = OFF           ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
  CONFIG  IESO = OFF            ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
    
    LIST P=18F4550                ; Especificamos el microcontrolador PIC18F4550
    #include <p18f4550.inc>       ; Incluimos el archivo de definición para el PIC18F4550

    ; Configuración del oscilador interno a 8 MHz
    ORG 0x00                      ; La rutina comienza en la dirección 0x00
    GOTO Main                      ; Saltamos a la etiqueta Main

    ; Configuración de la memoria y los registros
    ORG 0x04                      ; Dirección donde se ejecutará el programa después del reset
    Main:
        ; Configuración del oscilador
        ; La configuración es 01110110, que corresponde a 0x76
        MOVLW   0x76               ; Cargamos el valor 0x76 (01110110) en el registro W
        MOVWF   OSCCON             ; Guardamos el valor de configuración en el registro OSCCON

        ; Configuración de RB1 como salida
        CLRF    TRISB              ; Configuramos todo el puerto B como salida
        BSF     TRISB, 1           ; Configuramos el pin RB1 como salida

        ; Rutina principal
    MainLoop:
        ; Encender RB1
        BSF     LATB, 1            ; Set RB1 en alto (encender LED)

        ; Esperar 5 segundos (5000 ms)
        CALL    Delay5s

        ; Apagar RB1
        BCF     LATB, 1            ; Clear RB1 en bajo (apagar LED)

        ; Esperar 2 segundos (2000 ms)
        CALL    Delay2s

        ; Volver al inicio del bucle
        GOTO    MainLoop

    ; Rutina de delay de 5 segundos
    Delay5s:
        MOVLW   D5                  ; Cargamos el valor de 5 segundos (en ciclos de 1 ms) en W
        MOVWF   Count1              ; Guardamos el valor en el contador Count1
    Delay5sLoop1:
        MOVLW   D1000               ; Cargamos el valor de 1 segundo (en ciclos de 1 ms) en W
        MOVWF   Count2              ; Guardamos el valor en el contador Count2
    Delay5sLoop2:
        NOP                          ; No hacer nada, solo esperar
        NOP
        DECFSZ  Count2, f           ; Decrementamos el contador Count2 y repetimos si no llega a 0
        GOTO    Delay5sLoop2
        DECFSZ  Count1, f           ; Decrementamos el contador Count1 y repetimos si no llega a 0
        GOTO    Delay5sLoop1
        RETURN

    ; Rutina de delay de 2 segundos
    Delay2s:
        MOVLW   D2                  ; Cargamos el valor de 2 segundos (en ciclos de 1 ms) en W
        MOVWF   Count1              ; Guardamos el valor en el contador Count1
    Delay2sLoop1:
        MOVLW   D1000               ; Cargamos el valor de 1 segundo (en ciclos de 1 ms) en W
        MOVWF   Count2              ; Guardamos el valor en el contador Count2
    Delay2sLoop2:
        NOP                          ; No hacer nada, solo esperar
        NOP
        DECFSZ  Count2, f           ; Decrementamos el contador Count2 y repetimos si no llega a 0
        GOTO    Delay2sLoop2
        DECFSZ  Count1, f           ; Decrementamos el contador Count1 y repetimos si no llega a 0
        GOTO    Delay2sLoop1
        RETURN

    ; Definición de constantes para los delays
    D5      equ     5000             ; 5000 ms para 5 segundos
    D2      equ     2000             ; 2000 ms para 2 segundos
    D1000   equ     1000             ; 1000 ms para 1 segundo

    ; Definición de registros para el contador
    Count1  equ     0x20             ; Primer contador
    Count2  equ     0x21             ; Segundo contador

    END



