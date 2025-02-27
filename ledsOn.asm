LIST P=18F4550       ; Especifica el modelo del PIC
    #include <p18F4550.inc> ; Incluir archivo de definiciones del PIC18F4550
    CONFIG FOSC = INTOSCIO_EC  ; Oscilador interno activado
    CONFIG WDT = OFF         ; Desactivar Watchdog Timer
    CONFIG LVP = OFF         ; Desactivar programaci�n de bajo voltaje

    ORG 0x00          ; Inicio del c�digo en la direcci�n 0x00
    GOTO Inicio       ; Salto a la rutina principal

;===========================
; Configuraci�n Inicial
;===========================
Inicio:
    CLRF TRISB        ; Configurar PORTB como salida
    BCF TRISB, 0      ; Asegurar que RB0 es salida
    MOVLW 0x76        ; Cargar la configuraci�n del oscilador interno (8 MHz)
    MOVWF OSCCON      ; Aplicar configuraci�n

Encender_LED:
    BSF PORTB, 0      ; Encender RB0 (LED encendido)
    GOTO Encender_LED ; Bucle infinito, mantiene el LED encendido

    END