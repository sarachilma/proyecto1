/* 
 * File:   main.c
 * Author: Esteban
 *
 * Created on 3 de abril de 2025, 03:26 PM
 */

#include <xc.h>
#include <pic18f4550.h>
#include <stdint.h>
#include <stdio.h>
#include "Config.h"
#include "LCD.h"
#include "DHT11.h"

void ClearLine(uint8_t line) {
    LCD_String_xy(line, 0, "                "); // 16 espacios para limpiar
}

void main() {
    // Configuración inicial
    OSCCON = 0x72;
    TRISAbits.TRISA0 = 1;
    ADCON1 = 0x0F;
    CMCON = 0x07;

    LCD_Init();
    LCD_Clear();

    while(1) {
        uint8_t hum_int, temp_int;
        
        if (DHT11_Read(&hum_int, &temp_int)) {
            char buffer[17]; // Buffer para 16 caracteres + null
            
            // Limpiar ambas líneas antes de escribir
            ClearLine(0);
            ClearLine(1);
            
            // Mostrar humedad (primer renglón)
            sprintf(buffer, "Humedad: %d%%", hum_int);
            LCD_String_xy(0, 0, buffer);
            
            // Mostrar temperatura (segundo renglón)
            sprintf(buffer, "Temp: %d\xDF""C", temp_int);
            LCD_String_xy(1, 0, buffer);
        } else {
            // Limpiar ambas líneas antes del error
            ClearLine(0);
            ClearLine(1);
            
            LCD_String_xy(0, 0, "Error de sensor");
            LCD_String_xy(1, 0, "Reintentando...");
        }
        __delay_ms(2000);
    }
}