/* 
 * File:   main.c
 * Author: danis
 *
 * Created on 21 de abril de 2025, 09:17 AM
 */

/* 
 * File:   main.c
 * Author: danis
 *
 * Created on 21 de abril de 2025, 09:17 AM
 */

#include <xc.h>
#include "Config.h"
#include "LCD.h"
#include "RTC.h"

void main() {
    // Variables para fecha y hora
    uint8_t hour, min, sec, date, month, year;
    char time_str[9] = "00:00:00";
    char date_str[9] = "00/00/00";  // Reducido a 9 caracteres (DD/MM/YY)
    
    // Inicialización
    OSCCON = 0x72;
    LCD_Init();
    RTC_Init();
    
    // Configuración inicial (descomentar solo la primera vez)
    //RTC_SetDate(23, 4, 25);  // 21/04/25 (sin día de semana)
    //RTC_SetTime(8, 20, 0);   // 12:00:00
    
    LCD_Clear();
    
    while(1) {
        // Leer fecha y hora actual
        RTC_GetTime(&hour, &min, &sec);
        RTC_GetDate(&date, &month, &year);
        
        // Formatear hora (HH:MM:SS)
        time_str[0] = (hour / 10) + '0';
        time_str[1] = (hour % 10) + '0';
        time_str[3] = (min / 10) + '0';
        time_str[4] = (min % 10) + '0';
        time_str[6] = (sec / 10) + '0';
        time_str[7] = (sec % 10) + '0';
        
        // Formatear fecha (DD/MM/YY)
        date_str[0] = (date / 10) + '0';
        date_str[1] = (date % 10) + '0';
        date_str[3] = (month / 10) + '0';
        date_str[4] = (month % 10) + '0';
        date_str[6] = (year / 10) + '0';
        date_str[7] = (year % 10) + '0';
        
        // Mostrar en LCD
        LCD_String_xy(0, 0, "Date:");
        LCD_String_xy(0, 6, date_str);  // Ajustado a posición 6
        LCD_String_xy(1, 0, "Time:");
        LCD_String_xy(1, 6, time_str);  // Ajustado a posición 6
        
        __delay_ms(500);
    }
}
