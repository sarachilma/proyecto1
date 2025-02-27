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
    CLRF TRISB        ; Configurar PORTB como salida
    BSF TRISB, 0      ; Configurar RB0 como salida
    MOVLW 0x76        ; Cargar la configuración del oscilador interno (8 MHz)
    MOVWF OSCCON      ; Aplicar configuración

Loop:
    BSF PORTB, 0      ; Encender RB0
    CALL Retardo5s    ; Esperar 5 segundos
    BCF PORTB, 0      ; Apagar RB0
    CALL Retardo2s    ; Esperar 2 segundos
    GOTO Loop         ; Repetir ciclo

;===========================
; Rutina de retardo de 5 segundos
;===========================
Retardo5s:
    MOVLW D'100'      ; 100 iteraciones de 50ms ? 5000ms (5s)
    MOVWF cont1
R5s_1:
    CALL Retardo50ms  ; Llamar a rutina de 50ms
    DECFSZ cont1, F
    GOTO R5s_1
    RETURN

;===========================
; Rutina de retardo de 2 segundos
;===========================
Retardo2s:
    MOVLW D'40'       ; 40 iteraciones de 50ms ? 2000ms (2s)
    MOVWF cont1
R2s_1:
    CALL Retardo50ms  ; Llamar a rutina de 50ms
    DECFSZ cont1, F
    GOTO R2s_1
    RETURN

;===========================
; Rutina de retardo de 50ms
;===========================
Retardo50ms:
    MOVLW D'198'      ; Ajustado para 50ms
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


