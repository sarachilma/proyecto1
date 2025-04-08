/* 
 * File:   main.c
 * Author: Esteban
 *
 * Created on 3 de abril de 2025, 03:26 PM
 */

#include <xc.h>
#include <pic18f4550.h>
#include <stdint.h>
#include "Config.h"
#include "LCD.h"
#include "DHT11.h"

void main() {
    OSCCON = 0x72;          // Oscilador a 8MHz
    TRISAbits.TRISA0 = 1;   // RA0 como entrada
    ADCON1 = 0x0F;          // Pines AN como digitales
    CMCON = 0x07;           // Deshabilitar comparadores

    LCD_Init();             // Inicializar LCD
    LCD_Clear();            // Limpiar pantalla
    LCD_String_xy(0, 0, "Temperatura:"); // Texto completo

    while(1) {
        uint8_t temp = DHT11_GetTemperature();
        
        if (temp != 255) {
            char buffer[6];
            // Formato: "24 C"
            buffer[0] = (temp/10) + '0';  // Decenas
            buffer[1] = (temp%10) + '0';  // Unidades
            buffer[2] = ' ';
            buffer[3] = 'C';
            buffer[4] = '\0';
            
            LCD_String_xy(1, 0, buffer);  // Mostrar en segunda fila
        } else {
            LCD_String_xy(1, 0, "Error "); 
        }
        __delay_ms(2000);
    }
}