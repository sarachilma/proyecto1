#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "Config.h"
#include "USART_Header_File.h"

#define _XTAL_FREQ 8000000
#define LED LATDbits.LATD0


void main(void) {
    OSCCON = 0x72;         // Oscilador interno configurado a 8 MHz
    TRISD = 0x00;          // Puerto D como salida
    LATD = 0x00;           // Apagar todo el puerto D

    // Inicializa USART por software: TX = RB0, RX = RB1
    SoftUSART_Init();
    __delay_ms(200);

    SoftUSART_SendString("USART Software iniciado en RB0/RB1\r\n");

    char dato;
    char buf[32];

    while (1) {
        dato = SoftUSART_RxChar();  // Recibe un carácter desde Bluetooth (RB1)

        // Muestra el carácter recibido y su valor ASCII (para depuración)
        sprintf(buf, "Recibido: %c (%d)\r\n", dato, dato);
        SoftUSART_SendString(buf);

        // Control del LED en RD0
        if (dato == '1') {
            LED = 1;
            SoftUSART_SendString("LED ENCENDIDO\r\n");
        } else if (dato == '0') {
            LED = 0;
            SoftUSART_SendString("LED APAGADO\r\n");
        } 
        // Ignorar caracteres \r (13) y \n (10)
        else if (dato != '\r' && dato != '\n') {
            SoftUSART_SendString("Comando inválido. Usa 1 o 0\r\n");
        }

        __delay_ms(150); // Retardo para evitar rebotes o lecturas múltiples
    }
}
