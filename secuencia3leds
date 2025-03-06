; ---------------------------------------------------------------------
; Secuencia de 3 LEDs con retardos de 1 segundo
; Microcontrolador: PIC18F4550
; Oscilador interno configurado a 250 kHz
; ---------------------------------------------------------------------

; ---------------------------------------------------------------------
; CONFIGURACIÓN DE BITS (DIRECTIVAS DEL COMPILADOR)
; ---------------------------------------------------------------------
#include "p18f4550.inc"  ; Incluir archivo de definiciones del PIC18F4550

CONFIG  FOSC = INTOSCIO_EC    ; Usar oscilador interno con salida en RA6
CONFIG  WDT = OFF             ; Deshabilitar Watchdog Timer (evitar reset automático)
CONFIG  PBADEN = OFF          ; Deshabilitar conversión A/D en PORTB (configurar como digital)
CONFIG  LVP = OFF             ; Deshabilitar programación de bajo voltaje (LVP)

; ---------------------------------------------------------------------
; VARIABLES EN MEMORIA (SECCIÓN UDATA)
; ---------------------------------------------------------------------
UDATA
COUNT1  RES 1       ; Reservar 1 byte para COUNT1 (contador para bucle externo)
COUNT2  RES 1       ; Reservar 1 byte para COUNT2 (contador para bucle interno)

; ---------------------------------------------------------------------
; VECTOR DE RESET (INICIO DEL PROGRAMA)
; ---------------------------------------------------------------------
ORG     0x0000      ; Origen del programa en la dirección 0x0000
    GOTO    INICIO  ; Saltar a la etiqueta INICIO (inicio del programa principal)

; ---------------------------------------------------------------------
; PROGRAMA PRINCIPAL
; ---------------------------------------------------------------------
INICIO:
    ; -----------------------------------------------------------------
    ; CONFIGURACIÓN INICIAL DEL MICROCONTROLADOR
    ; -----------------------------------------------------------------
    MOVLB   1           ; Seleccionar banco 1 (para acceder a registros especiales)
    CLRF    TRISA       ; Configurar todos los pines de PORTA como salidas (TRISA = 0)
    MOVLW   B'00110000' ; Configurar OSCCON: IRCF3:IRCF0 = 011 (250 kHz), SCS = 00 (usar FOSC)
    MOVWF   OSCCON,FAST ; Cargar valor en OSCCON (configurar oscilador interno a 250 kHz)
    
    MOVLB   0           ; Volver al banco 0 (banco por defecto)
    CLRF    LATA        ; Apagar todos los LEDs (LATA = 0)

; ---------------------------------------------------------------------
; BUCLE PRINCIPAL (SECUENCIA DE LEDs)
; ---------------------------------------------------------------------
LOOP:
    ; Secuencia hacia adelante: RA0 -> RA1 -> RA2
    BSF     LATA, 0     ; Encender LED en RA0 (poner a 1 el bit 0 de LATA)
    CALL    DELAY_1S    ; Llamar a la rutina de retardo de 1 segundo
    BCF     LATA, 0     ; Apagar LED en RA0 (poner a 0 el bit 0 de LATA)

    BSF     LATA, 1     ; Encender LED en RA1
    CALL    DELAY_1S    ; Esperar 1 segundo
    BCF     LATA, 1     ; Apagar LED en RA1

    BSF     LATA, 2     ; Encender LED en RA2
    CALL    DELAY_1S    ; Esperar 1 segundo
    BCF     LATA, 2     ; Apagar LED en RA2

    ; Secuencia hacia atrás: RA2 -> RA1 -> RA0
    BSF     LATA, 2     ; Encender LED en RA2
    CALL    DELAY_1S    ; Esperar 1 segundo
    BCF     LATA, 2     ; Apagar LED en RA2

    BSF     LATA, 1     ; Encender LED en RA1
    CALL    DELAY_1S    ; Esperar 1 segundo
    BCF     LATA, 1     ; Apagar LED en RA1

    BSF     LATA, 0     ; Encender LED en RA0
    CALL    DELAY_1S    ; Esperar 1 segundo
    BCF     LATA, 0     ; Apagar LED en RA0

    GOTO    LOOP        ; Repetir el bucle indefinidamente

; ---------------------------------------------------------------------
; RUTINA DE RETARDO DE 1 SEGUNDO (PARA 250 kHz)
; ---------------------------------------------------------------------
DELAY_1S:
    ; -----------------------------------------------------------------
    ; Bucle externo (COUNT1 = 125 iteraciones)
    ; -----------------------------------------------------------------
    MOVLW   D'125'      ; Cargar valor 125 en W (para COUNT1)
    MOVWF   COUNT1      ; Mover W a COUNT1 (inicializar bucle externo)
DELAY_1S_LOOP1:
    ; -----------------------------------------------------------------
    ; Bucle interno (COUNT2 = 200 iteraciones)
    ; -----------------------------------------------------------------
    MOVLW   D'200'      ; Cargar valor 200 en W (para COUNT2)
    MOVWF   COUNT2      ; Mover W a COUNT2 (inicializar bucle interno)
DELAY_1S_LOOP2:
    NOP                 ; No operation (1 ciclo de retardo)
    DECFSZ  COUNT2,F    ; Decrementar COUNT2 y saltar si es cero (1 ciclo, 2 si salta)
    GOTO    DELAY_1S_LOOP2 ; Repetir bucle interno (2 ciclos)
    
    ; -----------------------------------------------------------------
    ; Ajustar bucle externo
    ; -----------------------------------------------------------------
    DECFSZ  COUNT1,F    ; Decrementar COUNT1 y saltar si es cero (1 ciclo, 2 si salta)
    GOTO    DELAY_1S_LOOP1 ; Repetir bucle externo (2 ciclos)
    RETURN              ; Retornar de la rutina de retardo

; ---------------------------------------------------------------------
; FIN DEL PROGRAMA
; ---------------------------------------------------------------------
    END                 ; Fin del código
