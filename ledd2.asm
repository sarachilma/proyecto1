    LIST P=18F4550                ; Especificamos el microcontrolador PIC18F4550
    #include <p18f4550.inc>       ; Incluimos el archivo de definición para el PIC18F4550
;secuenciaaa
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

        ; Configuración de RB1, RB2, RB3, RB4 como salida
        CLRF    TRISB              ; Configuramos todo el puerto B como salida
        BSF     TRISB, 1           ; Configuramos el pin RB1 como salida
        BSF     TRISB, 2           ; Configuramos el pin RB2 como salida
        BSF     TRISB, 3           ; Configuramos el pin RB3 como salida
        BSF     TRISB, 4           ; Configuramos el pin RB4 como salida

        ; Rutina principal
    MainLoop:
        ; Encender RB1, RB2, RB3, RB4 uno por uno con retraso
        CALL    TurnOnLEDs
        CALL    Delay500ms         ; Delay de 500 ms

        ; Apagar RB1, RB2, RB3, RB4 uno por uno con retraso
        CALL    TurnOffLEDs
        CALL    Delay500ms         ; Delay de 500 ms

        ; Volver al inicio del bucle
        GOTO    MainLoop

    ; Rutina para encender los LEDs en secuencia
    TurnOnLEDs:
        BSF     LATB, 1            ; Enciende RB1
        CALL    Delay500ms         ; Delay de 500 ms
        BSF     LATB, 2            ; Enciende RB2
        CALL    Delay500ms         ; Delay de 500 ms
        BSF     LATB, 3            ; Enciende RB3
        CALL    Delay500ms         ; Delay de 500 ms
        BSF     LATB, 4            ; Enciende RB4
        RETURN

    ; Rutina para apagar los LEDs en secuencia
    TurnOffLEDs:
        BCF     LATB, 1            ; Apaga RB1
        CALL    Delay500ms         ; Delay de 500 ms
        BCF     LATB, 2            ; Apaga RB2
        CALL    Delay500ms         ; Delay de 500 ms
        BCF     LATB, 3            ; Apaga RB3
        CALL    Delay500ms         ; Delay de 500 ms
        BCF     LATB, 4            ; Apaga RB4
        RETURN

    ; Rutina de delay de 500 ms
    Delay500ms:
        MOVLW   500                ; Cargamos el valor de 500 ciclos en W (500 ms)
        MOVWF   Count1             ; Guardamos el valor en el contador Count1
    Delay500msLoop1:
        MOVLW   1000               ; Cargamos el valor de 1000 ciclos en W (para 1 segundo)
        MOVWF   Count2             ; Guardamos el valor en el contador Count2
    Delay500msLoop2:
        NOP                         ; No hacer nada, solo esperar
        NOP
        DECFSZ  Count2, f          ; Decrementamos el contador Count2 y repetimos si no llega a 0
        GOTO    Delay500msLoop2
        DECFSZ  Count1, f          ; Decrementamos el contador Count1 y repetimos si no llega a 0
        GOTO    Delay500msLoop1
        RETURN

    ; Definición de registros para el contador
    Count1  equ     0x20            ; Primer contador
    Count2  equ     0x21            ; Segundo contador

    END



