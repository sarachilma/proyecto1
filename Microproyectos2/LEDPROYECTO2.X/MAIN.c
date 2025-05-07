#include <xc.h>
#include "Config.h"

#define _XTAL_FREQ 8000000
#define LED LATDbits.LATD0

void main(void) {
    // Configuración inicial
    OSCCON = 0x72;      // Oscilador interno a 8MHz
    TRISD = 0x00;       // Puerto D como salida (LED en RD0)
    TRISB = 0x02;       // RB0 como salida (TX), RB1 como entrada (RX)
    LATBbits.LATB0 = 1; // Estado inicial HIGH (idle)
    
    while(1) {
        // Espera bit de inicio (flanco descendente en RB1)
        if(PORTBbits.RB1 == 0) {
            __delay_us(104); // Retardo medio bit (9600 baudios)
            
            // Cambia el estado del LED al detectar cualquier dato
            LED = !LED;
            
            // Espera a que termine el byte (10 bits = 1040µs)
            __delay_us(1040);
        }
    }
}


