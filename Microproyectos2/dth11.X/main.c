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
    OSCCON = 0x72;          // Oscilador interno a 8MHz
    TRISAbits.TRISA0 = 1;   // RA0 como entrada
    ADCON1 = 0x0F;          // Todos los pines AN como digitales
    CMCON = 0x07;           // Deshabilitar comparadores

    LCD_Init();
    LCD_String_xy(0, 0, "Temperatura:");

    while(1) {
        uint8_t temp = DHT11_GetTemperature();
        char buffer[5];  // Tamaño optimizado: "28 C\0"
        
        if (temp != 255) {
            buffer[0] = (temp/10) + '0';  // Decenas
            buffer[1] = (temp%10) + '0';  // Unidades
            buffer[2] = ' ';
            buffer[3] = 'C';
            buffer[4] = '\0';  // Fin de cadena
            LCD_String_xy(1, 0, buffer);
        } else {
            LCD_String_xy(1, 0, "Error");
        }
        __delay_ms(2000);
    }
}