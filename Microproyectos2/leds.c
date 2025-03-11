#include <stdio.h>

// Definición de pines para los LEDs
#define LED_VERDE   LATBbits.LATB0  // LED verde en RB0
#define LED_AMARILLO LATBbits.LATB1  // LED amarillo en RB1
#define LED_ROJO    LATBbits.LATB2  // LED rojo en RB2

void main() {
    // Configurar los pines como salidas
    TRISB = 0x00;  // Configurar todos los pines del PORTB como salidas
    LATB = 0x00;   // Apagar todos los LEDs inicialmente

    // Variable para almacenar el valor de entrada
    unsigned char valor = 0;

    while (1) {
        // Simular la lectura de un valor (puede ser un ADC, por ejemplo)
        valor = 100;  // Cambia este valor para probar diferentes casos

        // Controlar los LEDs según el valor de la variable
        if (valor > 127) {
            LED_VERDE = 1;      // Encender LED verde
            LED_AMARILLO = 0;   // Apagar LED amarillo
            LED_ROJO = 0;       // Apagar LED rojo
        } else if (valor >= 64 && valor <= 127) {
            LED_VERDE = 0;      // Apagar LED verde
            LED_AMARILLO = 1;  // Encender LED amarillo
            LED_ROJO = 0;       // Apagar LED rojo
        } else {
            LED_VERDE = 0;      // Apagar LED verde
            LED_AMARILLO = 0;   // Apagar LED amarillo
            LED_ROJO = 1;       // Encender LED rojo
        }
    }
}