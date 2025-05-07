#include <xc.h>
#include <pic18f4550.h>
#include "Config.h"
#include "LCD.h"
#include "gps.h"
#include <string.h>

void main() {
    OSCCON = 0x72;  // Configurar oscilador interno a 8MHz
    
    LCD_Init();     // Inicializar LCD
    GPS_Init();     // Inicializar GPS
    
    LCD_String_xy(0, 0, "GPS NEO-6M Test");
    LCD_String_xy(1, 0, "Inicializando...");
    __delay_ms(2000);
    LCD_Clear();
    
    while(1) {
        GPS_ReadData();  // Leer datos del GPS
        
        // Mostrar datos en LCD
        LCD_String_xy(0, 0, "Hora:");
        LCD_String_xy(0, 6, gps_time);
        
        if(gps_valid == 'A') {
            LCD_String_xy(1, 0, "Lat:");
            LCD_String_xy(1, 5, gps_latitude);
        } else {
            LCD_String_xy(1, 0, "Esperando senal...");
        }
        
        __delay_ms(500);
        
        LCD_String_xy(0, 0, "Lon:");
        LCD_String_xy(0, 5, gps_longitude);
        LCD_String_xy(1, 0, "Sats:");
        LCD_String_xy(1, 6, gps_sats);
        
        __delay_ms(500);
    }
}