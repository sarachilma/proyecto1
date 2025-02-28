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

; CONFIG2L
  CONFIG  PWRT = ON             ; Power-up Timer Enable bit (PWRT enabled)
  CONFIG  BOR = ON              ; Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
  CONFIG  BORV = 3              ; Brown-out Reset Voltage bits (Minimum setting 2.05V)
  CONFIG  VREGEN = OFF          ; USB Voltage Regulator Enable bit (USB voltage regulator disabled)

; CONFIG2H
  CONFIG  WDT = OFF             ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
  CONFIG  WDTPS = 32768         ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
  CONFIG  CCP2MX = ON           ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
  CONFIG  PBADEN = ON           ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
  CONFIG  LPT1OSC = OFF         ; Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
  CONFIG  MCLRE = ON            ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
  CONFIG  STVREN = ON           ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
  CONFIG  LVP = OFF             ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
  CONFIG  ICPRT = OFF           ; Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
  CONFIG  XINST = OFF           ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
  CONFIG  CP0 = OFF             ; Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
  CONFIG  CP1 = OFF             ; Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
  CONFIG  CP2 = OFF             ; Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
  CONFIG  CP3 = OFF             ; Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

; CONFIG5H
  CONFIG  CPB = OFF             ; Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
  CONFIG  CPD = OFF             ; Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

; CONFIG6L
  CONFIG  WRT0 = OFF            ; Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
  CONFIG  WRT1 = OFF            ; Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
  CONFIG  WRT2 = OFF            ; Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
  CONFIG  WRT3 = OFF            ; Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

; CONFIG6H
  CONFIG  WRTC = OFF            ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
  CONFIG  WRTB = OFF            ; Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
  CONFIG  WRTD = OFF            ; Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

; CONFIG7L
  CONFIG  EBTR0 = OFF           ; Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR1 = OFF           ; Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR2 = OFF           ; Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
  CONFIG  EBTR3 = OFF           ; Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

; CONFIG7H
  CONFIG  EBTRB = OFF           ; Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)


    ORG     0x00          ; Vector de reset
    GOTO    INICIO          ; Salta al inicio del programa

; Variables
CONTADOR EQU 0x20       ; Variable para contar los segundos

; Inicio del programa
INICIO:
    MOVLW   0x77     ; Configura el oscilador:
    MOVWF   OSCCON          ; Carga la configuración en OSCCON
    CLRF    TRISA           ; Configura el puerto B como salida
    CLRF    LATA           ; Apaga todos los pines del puerto B
    MOVLW   0x07            ; Configura el Timer0:
                            ; - Modo temporizador (T0CS = 0)
                            ; - Prescaler 1:256 (PS2:PS0 = 111)
    MOVWF   T0CON           ; Carga la configuración en T0CON
    CLRF    TMR0L           ; Limpia el registro TMR0L
    CLRF    TMR0H           ; Limpia el registro TMR0H

CICLO:
    BSF     PORTA, RB0      ; Enciende el LED en el pin RB0
    CALL    RETARDO_5S      ; Espera 5 segundos
    BCF     PORTA, RB0      ; Apaga el LED en el pin RB0
    CALL    RETARDO_2S      ; Espera 2 segundos
    GOTO    CICLO           ; Repite el ciclo infinitamente

; Subrutina de retardo de 5 segundos
RETARDO_5S:
    MOVLW   .5              ; Carga 5 en W (5 segundos)
    MOVWF   CONTADOR        ; Mueve W a CONTADOR
    CALL    RETARDO_TIMER0  ; Llama al retardo basado en Timer0
    RETURN

; Subrutina de retardo de 2 segundos
RETARDO_2S:
    MOVLW   .2              ; Carga 2 en W (2 segundos)
    MOVWF   CONTADOR        ; Mueve W a CONTADOR
    CALL    RETARDO_TIMER0  ; Llama al retardo basado en Timer0
    RETURN

; Subrutina de retardo basado en Timer0
RETARDO_TIMER0:
    BCF     INTCON, TMR0IF  ; Limpia la bandera de desbordamiento del Timer0
RETARDO_LOOP:
    BTFSS   INTCON, TMR0IF  ; Espera a que el Timer0 se desborde
    GOTO    RETARDO_LOOP    ; Si no hay desbordamiento, sigue esperando
    BCF     INTCON, TMR0IF  ; Limpia la bandera de desbordamiento
    DECFSZ  CONTADOR, F     ; Decrementa CONTADOR, salta si es cero
    GOTO    RETARDO_LOOP    ; Si CONTADOR no es cero, repite el bucle
    RETURN                  ; Retorna de la subrutina

    END                     ; Fin del programa


