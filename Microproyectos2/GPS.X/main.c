/*
 * File:   main.c
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:14 PM
 */


/*
 * File:   main.c
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:14 PM
 */

/*
 * File:   main.c
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:14 PM
 */

#include <xc.h>
#include "Config.h"
#include "LCD.h"
#include "GPS.h"
#include <string.h>

void main() {
    // --- Configuración inicial ---
    OSCCON = 0x72;  // Configura oscilador interno a 8MHz
    
    LCD_Init();     // Inicializa la pantalla LCD
    LCD_String_xy(0, 0, "GPS GPRMC"); // Mensaje inicial
    __delay_ms(2000);
    
    GPS_Init();     // Inicializa el módulo GPS
    
    // --- Variables ---
    char buffer[100];   // Buffer para datos crudos del GPS
    char lat[10] = "";  // Almacena latitud (formato DDMM.MMM)
    char ns[2] = "";    // Almacena dirección N/S
    char lon[11] = "";  // Almacena longitud (formato DDDMM.MMM)
    char ew[2] = "";    // Almacena dirección E/W
    uint8_t last_valid = 0; // Bandera de datos válidos previos

    // --- Loop principal ---
    while(1) {
        // Limpieza de buffers en cada iteración
        memset(buffer, 0, sizeof(buffer));
        memset(lat, 0, sizeof(lat));
        memset(ns, 0, sizeof(ns));
        memset(lon, 0, sizeof(lon));
        memset(ew, 0, sizeof(ew));

        // Intenta leer una frase NMEA
        if(GPS_ReadSentence(buffer, sizeof(buffer), 1000)) {
            // Verifica si es una frase GPRMC
            if(strstr(buffer, "$GPRMC")) {
                // Parsea los datos de posición
                if(GPS_ParseGPRMC(buffer, lat, ns, lon, ew)) {
                    char formatted_lat[15] = {0}; // Buffer para latitud formateada
                    char formatted_lon[15] = {0}; // Buffer para longitud formateada

                    // Construye cadena de latitud (formato: DD°MM.MM' N/S)
                    strncpy(formatted_lat, lat, 2);    // Grados
                    strcat(formatted_lat, "\xDF");      // Símbolo °
                    strncat(formatted_lat, lat + 2, 5); // Minutos
                    strcat(formatted_lat, "' ");        // Símbolo ' y espacio
                    strcat(formatted_lat, ns);          // Dirección N/S

                    // Construye cadena de longitud (formato: DDD°MM.MM' E/W)
                    strncpy(formatted_lon, lon, 3);    // Grados
                    strcat(formatted_lon, "\xDF");      // Símbolo °
                    strncat(formatted_lon, lon + 3, 4); // Minutos
                    strcat(formatted_lon, "' ");        // Símbolo ' y espacio
                    strcat(formatted_lon, ew);          // Dirección E/W

                    // Muestra en LCD
                    LCD_Clear();
                    LCD_String_xy(0, 0, "Lat:");
                    LCD_String_xy(0, 5, formatted_lat); // Ej: 02°26.78' N
                    LCD_String_xy(1, 0, "Lon:");
                    LCD_String_xy(1, 5, formatted_lon); // Ej: 076°35.9' W

                    last_valid = 1; // Marca datos como válidos
                    __delay_ms(500); // Pequeña pausa
                    continue;
                }
            }
        }

        // Si no hay datos nuevos pero hubo válidos previamente
        if(last_valid) {
            __delay_ms(100);
            continue;
        }

        // Si no se han recibido datos válidos
        LCD_Clear();
        LCD_String_xy(0, 0, "Buscando...");
        __delay_ms(500);
    }
}