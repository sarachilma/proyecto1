
    INCLUDE "P18F4550.INC"

    ORG 0x00         ; Dirección de inicio del programa
    BSF  TRISB, 0    ; Configurar RB0 como salida
    BCF  LATB, 0     ; Asegurar que RB0 empieza apagado
    BSF  LATB, 0     ; Encender el LED en RB0

    END
    



