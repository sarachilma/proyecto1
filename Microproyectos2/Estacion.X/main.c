/*
 * File:   main.c (FIXED GPS)
 * Author: ChatGPT
 *
 * Integración DHT11, RTC y GPS con retry y timeout mayor para GPS.
 */
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "Config.h"
#include "LCD.h"
#include "DHT11.h"
#include "GPS.h"
#include "ds1307.h"
#include "i2c.h"

#define GPS_TIMEOUT 2000    // timeout parameter aumentado (2000 -> 200ms)
#define GPS_ATTEMPTS 5      // número de reintentos para obtener frase GPRMC

char lcd_buffer[17];

enum DisplayState { SHOW_DHT11, SHOW_GPS, SHOW_RTC, NUM_DISPLAYS };
enum DisplayState current_display = SHOW_DHT11;

void Clear_Line(uint8_t line) {
    LCD_String_xy(line, 0, "                ");
}

void Display_DHT11() {
    uint8_t hum, temp;
    Clear_Line(0); Clear_Line(1);
    if(DHT11_Read(&hum, &temp)) {
        sprintf(lcd_buffer, "H:%u%% T:%uC", hum, temp);
        LCD_String_xy(0,0,lcd_buffer);
    } else {
        LCD_String_xy(0,0,"DHT11: Error");
        LCD_String_xy(1,0,"Reintentando...");
    }
}

void Display_GPS() {
    char buffer[100], lat[10] = "", ns[2] = "", lon[11] = "", ew[2] = "";
    uint8_t valid = 0;

    // Intentar varias veces leer y parsear GPRMC
    for(uint8_t i=0; i<GPS_ATTEMPTS && !valid; i++) {
        if(GPS_ReadSentence(buffer, sizeof(buffer), GPS_TIMEOUT)) {
            valid = GPS_ParseGPRMC(buffer, lat, ns, lon, ew);
        }
        __delay_ms(50);  // breve pausa antes de reintentar
    }

    Clear_Line(0); Clear_Line(1);
    if(valid) {
        char formatted_lat[17] = {0};
        char formatted_lon[17] = {0};

        // Formatear latitud: DD°MM.MM' N
        strncpy(formatted_lat, lat, 2);          // Grados
        strcat(formatted_lat, "\xDF");           // Símbolo °
        strncat(formatted_lat, lat + 2, 5);      // Minutos con decimales
        strcat(formatted_lat, "' ");             // Minutos
        strcat(formatted_lat, ns);               // N/S

        // Formatear longitud: DDD°MM.MM' W
        strncpy(formatted_lon, lon, 3);          // Grados
        strcat(formatted_lon, "\xDF");           // Símbolo °
        strncat(formatted_lon, lon + 3, 5);      // Minutos con decimales
        strcat(formatted_lon, "' ");             // Minutos
        strcat(formatted_lon, ew);               // E/W

        LCD_String_xy(0,0,"Lat:");
        LCD_String_xy(0,4,formatted_lat);
        LCD_String_xy(1,0,"Lon:");
        LCD_String_xy(1,4,formatted_lon);
    } else {
        LCD_String_xy(0,0,"GPS: Sin senal");
        LCD_String_xy(1,0,"Reintentando");
    }
}




void Display_RTC() {
    unsigned char h,m,s,day,mon,year;
    for(uint8_t cnt=0; cnt<5; cnt++) {
        RTC_GetDateTime(&h,&m,&s,&day,&mon,&year);
        Clear_Line(0);
        sprintf(lcd_buffer, "%02u/%02u/20%02u", day,mon,year);
        LCD_String_xy(0,0,lcd_buffer);
        Clear_Line(1);
        sprintf(lcd_buffer, "%02u:%02u:%02u", h,m,s);
        LCD_String_xy(1,0,lcd_buffer);
        __delay_ms(1000);
    }
}

void main() {
    OSCCON = 0x72;        // 8MHz
    ADCON1 = 0x0F;        // todos digitales
    CMCON  = 0x07;        // comparadores off
    LCD_Init();
    I2C_Master_Init(100000);
    RTC_Init();
    GPS_Init();

    LCD_Clear();
    LCD_String_xy(0,0,"Estacion Met");
    LCD_String_xy(1,0,"Iniciando...");
    __delay_ms(2000);

    while(1) {
        switch(current_display) {
            case SHOW_DHT11: Display_DHT11(); break;
            case SHOW_GPS:   Display_GPS();   break;
            case SHOW_RTC:   Display_RTC();   break;
        }
        current_display = (current_display + 1) % NUM_DISPLAYS;
        __delay_ms(5000);
    }
}

