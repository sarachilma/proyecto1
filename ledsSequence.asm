LIST P=18F4550       ; Especifica el modelo del PIC
    #include <p18F4550.inc> ; Incluir archivo de definiciones del PIC18F4550
    CONFIG FOSC = INTOSCIO_EC  ; Oscilador interno activado
    CONFIG WDT = OFF         ; Desactivar Watchdog Timer
    CONFIG LVP = OFF         ; Desactivar programación de bajo voltaje

    ORG 0x00          ; Inicio del código en la dirección 0x00
    GOTO Inicio       ; Salto a la rutina principal

;===========================
; Configuración Inicial
;===========================
Inicio:
    CLRF TRISB        ; Configurar PORTB como salida (todos los pines)
    MOVLW 0x76        ; Cargar la configuración del oscilador interno (8 MHz)
    MOVWF OSCCON      ; Aplicar configuración

Loop:
    ; Encender RB0 por 1s
    BSF PORTB, 0      ; Encender LED en RB0
    CALL Retardo1s    ; Esperar 1 segundo
    BCF PORTB, 0      ; Apagar LED en RB0

    ; Encender RB1 por 1s
    BSF PORTB, 1      ; Encender LED en RB1
    CALL Retardo1s    ; Esperar 1 segundo
    BCF PORTB, 1      ; Apagar LED en RB1

    ; Encender RB2 por 1s
    BSF PORTB, 2      ; Encender LED en RB2
    CALL Retardo1s    ; Esperar 1 segundo
    BCF PORTB, 2      ; Apagar LED en RB2

    ; Encender todos los LEDs por 0.5s
    MOVLW B'00000111' ; Encender RB0, RB1 y RB2
    MOVWF PORTB
    CALL Retardo500ms ; Esperar 0.5 segundos
    CLRF PORTB        ; Apagar todos los LEDs

    ; Pausa de 1s antes de repetir la secuencia
    CALL Retardo1s
    GOTO Loop         ; Repetir la secuencia

;===========================
; Rutinas de retardo
;===========================

; Retardo de 1 segundo
Retardo1s:
    MOVLW D'20'       ; 20 iteraciones de 50ms ? 1s
    MOVWF cont1
R1s_1:
    CALL Retardo50ms  ; Llamar a rutina de 50ms
    DECFSZ cont1, F
    GOTO R1s_1
    RETURN

; Retardo de 0.5 segundos
Retardo500ms:
    MOVLW D'10'       ; 10 iteraciones de 50ms ? 500ms
    MOVWF cont1
R500ms_1:
    CALL Retardo50ms  ; Llamar a rutina de 50ms
    DECFSZ cont1, F
    GOTO R500ms_1
    RETURN

; Rutina de retardo de 50ms (corregida para 8 MHz)
Retardo50ms:
    MOVLW D'200'      ; Ajustado para 50ms (200 iteraciones)
    MOVWF cont2
R50ms_1:
    MOVLW D'250'      ; Ciclo interno de 250 iteraciones
    MOVWF cont3
R50ms_2:
    NOP               ; No operación (0.5 µs)
    NOP
    DECFSZ cont3, F   ; Decrementa cont3 hasta 0
    GOTO R50ms_2
    DECFSZ cont2, F   ; Decrementa cont2 hasta 0
    GOTO R50ms_1
    RETURN

;===========================
; Variables
;===========================
cont1 EQU 0x20
cont2 EQU 0x21
cont3 EQU 0x22

    END


