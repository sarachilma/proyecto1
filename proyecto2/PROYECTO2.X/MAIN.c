#include "Config.h"
#include "RTC.h"
#include "GPS.h"
#include "DTH11.h"
#include "LCD.h"
#include <stdio.h>
#include <string.h>

// Limpia una línea del LCD
void Clear_Line(uint8_t line) {
    LCD_String_xy(line, 0, "                "); // 16 espacios exactos
}

void main(void) {
    // Inicialización
    LCD_Init();
    RTC_Init();
    GPS_Init();
    __delay_ms(1000);

    LCD_Clear();
    LCD_String_xy(0, 0, "Estacion Met");
    LCD_String_xy(1, 0, "Iniciando...");
    __delay_ms(2000);

    // Variables
    uint8_t h, m, s, day, month, year;
    uint8_t hum = 0, temp = 0;
    char lat[8] = "", ns[2] = "", lon[9] = "", ew[2] = "";
    char nmea[100];
    char buffer[17];
    uint8_t estado = 0;

    while (1) {
        LCD_Clear();

        if (estado == 0) {  // RTC
            RTC_GetTime(&h, &m, &s);
            RTC_GetDate(&day, &month, &year);

            sprintf(buffer, "Fecha: %02u/%02u", day, month);
            LCD_String_xy(0, 0, buffer);
            sprintf(buffer, "Hora: %02u:%02u:%02u", h, m, s);
            LCD_String_xy(1, 0, buffer);
            __delay_ms(3000);
        }

        else if (estado == 1) {  // DHT11
            if (DHT11_Read(&hum, &temp)) {
                sprintf(buffer, "Temp: %u\xDF""C", temp);
                LCD_String_xy(0, 0, buffer);
                sprintf(buffer, "Hum: %u%%", hum);
                LCD_String_xy(1, 0, buffer);
            } else {
                LCD_String_xy(0, 0, "Error DHT11");
                LCD_String_xy(1, 0, "Reintentando...");
            }
            __delay_ms(3000);
        }

        else if (estado == 2) {  // GPS
            uint8_t intento = 0, success = 0;

            for (intento = 0; intento < 10 && !success; intento++) {
                if (GPS_ReadSentence(nmea, sizeof(nmea), 200)) {
                    if (strstr(nmea, "$GPRMC") && GPS_ParseGPRMC(nmea, lat, ns, lon, ew)) {
                        success = 1;
                    }
                }
                __delay_ms(100);
            }

            if (success) {
                sprintf(buffer, "Lat:%s%s", lat, ns);
                LCD_String_xy(0, 0, buffer);
                sprintf(buffer, "Lon:%s%s", lon, ew);
                LCD_String_xy(1, 0, buffer);
            } else {
                LCD_String_xy(0, 0, "GPS: Sin senal");
                LCD_String_xy(1, 0, "Buscando...");
            }
            __delay_ms(5000);
        }

        estado = (estado + 1) % 3;
    }
}
