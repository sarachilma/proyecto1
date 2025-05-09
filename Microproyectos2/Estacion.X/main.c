#include <xc.h>           // Librería para configuración y manejo del PIC
#include <stdio.h>        // Librería estándar de entrada y salida
#include <string.h>       // Librería para manipulación de cadenas
#include "Config.h"       // Archivos de configuración del sistema
#include "LCD.h"          // Librería para el manejo de la pantalla LCD
#include "DHT11.h"        // Librería para el manejo del sensor DHT11
#include "GPS.h"          // Librería para el manejo del módulo GPS
#include "ds1307.h"       // Librería para el manejo del RTC DS1307
#include "i2c.h"          // Librería para el manejo del bus I2C

// Definición de parámetros para la conexión GPS
#define GPS_TIMEOUT 2000    // Timeout de 2000ms (2 segundos) para el GPS
#define GPS_ATTEMPTS 5      // Número de intentos para obtener una frase GPRMC válida

// Buffer para la cadena de caracteres que se mostrará en el LCD
char lcd_buffer[17];

// Enumeración para los diferentes estados de la pantalla LCD (DHT11, GPS, RTC)
enum DisplayState { SHOW_DHT11, SHOW_GPS, SHOW_RTC, NUM_DISPLAYS };
enum DisplayState current_display = SHOW_DHT11;  // Inicia mostrando el DHT11

// Función para limpiar una línea del LCD
void Clear_Line(uint8_t line) {
    // Limpia la línea especificada en el LCD (usando 16 espacios)
    LCD_String_xy(line, 0, "                ");
}

// Función para mostrar los datos del sensor DHT11
void Display_DHT11() {
    uint8_t hum, temp;
    Clear_Line(0); Clear_Line(1);  // Limpia ambas líneas del LCD

    // Lee los valores de temperatura y humedad del DHT11
    if(DHT11_Read(&hum, &temp)) {
        // Si la lectura fue exitosa, muestra los datos
        sprintf(lcd_buffer, "H:%u%% T:%uC", hum, temp);
        LCD_String_xy(0,0,lcd_buffer);  // Muestra la humedad y temperatura en la línea 0
    } else {
        // Si hubo un error en la lectura, muestra un mensaje de error
        LCD_String_xy(0,0,"DHT11: Error");
        LCD_String_xy(1,0,"Reintentando...");  // Solicita un nuevo intento
    }
}

// Función para mostrar los datos de GPS
void Display_GPS() {
    char buffer[100], lat[10] = "", ns[2] = "", lon[11] = "", ew[2] = "";
    uint8_t valid = 0;

    // Intentar varias veces leer y parsear una frase GPRMC válida
    for(uint8_t i=0; i<GPS_ATTEMPTS && !valid; i++) {
        if(GPS_ReadSentence(buffer, sizeof(buffer), GPS_TIMEOUT)) {
            // Si se leyó correctamente una frase del GPS, intenta parsearla
            valid = GPS_ParseGPRMC(buffer, lat, ns, lon, ew);
        }
        __delay_ms(50);  // Breve pausa antes de reintentar
    }

    Clear_Line(0); Clear_Line(1);  // Limpia ambas líneas del LCD
    if(valid) {
        char formatted_lat[17] = {0};  // Buffer para latitud formateada
        char formatted_lon[17] = {0};  // Buffer para longitud formateada

        // Formatear latitud: DD°MM.MM' N
        strncpy(formatted_lat, lat, 2);          // Copia los primeros 2 caracteres (grados)
        strcat(formatted_lat, "\xDF");           // Agrega el símbolo °
        strncat(formatted_lat, lat + 2, 5);      // Copia los minutos con decimales
        strcat(formatted_lat, "' ");             // Agrega el símbolo ' y espacio
        strcat(formatted_lat, ns);               // Agrega la dirección (N/S)

        // Formatear longitud: DDD°MM.MM' W
        strncpy(formatted_lon, lon, 3);          // Copia los primeros 3 caracteres (grados)
        strcat(formatted_lon, "\xDF");           // Agrega el símbolo °
        strncat(formatted_lon, lon + 3, 5);      // Copia los minutos con decimales
        strcat(formatted_lon, "' ");             // Agrega el símbolo ' y espacio
        strcat(formatted_lon, ew);               // Agrega la dirección (E/W)

        // Muestra la latitud y longitud formateada en el LCD
        LCD_String_xy(0,0,"Lat:");
        LCD_String_xy(0,4,formatted_lat);       // Ej: 02°26.78' N
        LCD_String_xy(1,0,"Lon:");
        LCD_String_xy(1,4,formatted_lon);       // Ej: 076°35.9' W
    } else {
        // Si no se pudo obtener una señal GPS válida, muestra un mensaje de error
        LCD_String_xy(0,0,"GPS: Sin senal");
        LCD_String_xy(1,0,"Reintentando");
    }
}

// Función para mostrar los datos del RTC DS1307
void Display_RTC() {
    unsigned char h,m,s,day,mon,year;
    for(uint8_t cnt=0; cnt<5; cnt++) {
        // Obtiene la fecha y hora actual del RTC
        RTC_GetDateTime(&h,&m,&s,&day,&mon,&year);
        Clear_Line(0);  // Limpia la línea 0
        // Muestra la fecha en formato: DD/MM/YY
        sprintf(lcd_buffer, "%02u/%02u/20%02u", day,mon,year);
        LCD_String_xy(0,0,lcd_buffer);
        Clear_Line(1);  // Limpia la línea 1
        // Muestra la hora en formato: HH:MM:SS
        sprintf(lcd_buffer, "%02u:%02u:%02u", h,m,s);
        LCD_String_xy(1,0,lcd_buffer);
        __delay_ms(1000);  // Espera 1 segundo antes de actualizar
    }
}

// Función principal
void main() {
    OSCCON = 0x72;        // Configura el oscilador interno a 8MHz
    ADCON1 = 0x0F;        // Configura todos los pines como digitales
    CMCON  = 0x07;        // Desactiva los comparadores internos
    LCD_Init();           // Inicializa la pantalla LCD
    I2C_Master_Init(100000); // Inicializa el bus I2C a 100kHz
    RTC_Init();           // Inicializa el RTC DS1307
    GPS_Init();           // Inicializa el módulo GPS

    // Muestra un mensaje inicial de arranque en el LCD
    LCD_Clear();
    LCD_String_xy(0,0,"Estacion Met");
    LCD_String_xy(1,0,"Iniciando...");
    __delay_ms(2000);  // Pausa de 2 segundos

    // Loop principal
    while(1) {
        // Dependiendo del estado actual, muestra DHT11, GPS o RTC
        switch(current_display) {
            case SHOW_DHT11: Display_DHT11(); break;  // Muestra los datos del DHT11
            case SHOW_GPS:   Display_GPS();   break;  // Muestra los datos del GPS
            case SHOW_RTC:   Display_RTC();   break;  // Muestra los datos del RTC
        }
        
        // Cambia el estado a la siguiente opción para el próximo ciclo
        current_display = (current_display + 1) % NUM_DISPLAYS;
        __delay_ms(5000);  // Espera 5 segundos antes de cambiar la pantalla
    }
}


