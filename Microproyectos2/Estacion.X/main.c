/**
 * PROGRAMA PRINCIPAL PARA ESTACIÓN METEOROLÓGICA
 * Integra tres módulos: DHT11 (temperatura/humedad), GPS y RTC (reloj)
 * Muestra los datos de cada módulo rotando cada 5 segundos en pantalla LCD
 */

#include <xc.h>         // Librería básica del compilador XC8
#include <stdio.h>      // Para funciones de formato como sprintf
#include <string.h>     // Para manejo de cadenas (strstr)
#include "Config.h"     // Configuración de bits del PIC
#include "LCD.h"        // Control de la pantalla LCD
#include "DHT11.h"      // Sensor de temperatura/humedad
#include "GPS.h"        // Módulo GPS
#include "ds1307.h"     // Reloj de tiempo real (RTC)
#include "i2c.h"        // Comunicación I2C para el RTC

// Definición de estados para rotar entre displays
typedef enum {
    SHOW_DHT11,     // Mostrar datos del sensor DHT11
    SHOW_GPS,       // Mostrar datos del GPS
    SHOW_RTC,       // Mostrar hora/fecha del RTC
    NUM_DISPLAYS    // Total de estados disponibles
} DisplayState;

DisplayState current_display = SHOW_DHT11; // Estado inicial
char lcd_buffer[17]; // Buffer para almacenar texto a mostrar en LCD (16 caracteres + null)

/**
 * Función para limpiar una línea específica del LCD
 * @param line: Número de línea a limpiar (0 o 1)
 */
void Clear_Line(uint8_t line) {
    LCD_String_xy(line, 0, "                "); // Rellena con 16 espacios
}

/**
 * Muestra datos del sensor DHT11 (temperatura y humedad)
 */
void Display_DHT11() {
    uint8_t hum, temp; // Variables para humedad y temperatura
    
    // Limpiar ambas líneas del LCD
    Clear_Line(0);
    Clear_Line(1);
    
    // Leer sensor DHT11
    if(DHT11_Read(&hum, &temp)) {
        // Si lectura exitosa, mostrar humedad (línea 0)
        sprintf(lcd_buffer, "H: %d%%", hum);
        LCD_String_xy(0, 0, lcd_buffer);
        
        // Mostrar temperatura (línea 1) con símbolo de grados
        sprintf(lcd_buffer, "T: %d\xDF""C", temp);
        LCD_String_xy(1, 0, lcd_buffer);
    } else {
        // Si hay error, mostrar mensaje
        LCD_String_xy(0, 0, "DHT11: Error");
        LCD_String_xy(1, 0, "Reintentando...");
    }
}

/**
 * Muestra datos del GPS (latitud y longitud)
 */
void Display_GPS() {
    char buffer[100], lat[10], ns[2], lon[11], ew[2];
    
    // Limpiar pantalla
    Clear_Line(0);
    Clear_Line(1);
    
    // Leer frase NMEA del GPS y parsear datos
    if(GPS_ReadSentence(buffer, sizeof(buffer), 500) && 
       strstr(buffer, "$GPRMC") &&  // Buscar frase GPRMC
       GPS_ParseGPRMC(buffer, lat, ns, lon, ew)) {
        
        // Mostrar latitud (línea 0)
        sprintf(lcd_buffer, "Lat:%s%s", lat, ns);
        LCD_String_xy(0, 0, lcd_buffer);
        
        // Mostrar longitud (línea 1)
        sprintf(lcd_buffer, "Lon:%s%s", lon, ew);
        LCD_String_xy(1, 0, lcd_buffer);
    } else {
        // Si no hay datos válidos
        LCD_String_xy(0, 0, "GPS: Sin senal");
        LCD_String_xy(1, 0, "Buscando...");
    }
}

/**
 * Muestra hora y fecha del RTC (actualizado cada segundo)
 */
void Display_RTC() {
    unsigned char h, m, s, day, mon, year;
    int8_t refresh_count = 0; // Contador para 5 segundos
    
    while (refresh_count < 5) {
        // Leer hora y fecha actual del RTC
        RTC_GetDateTime(&h, &m, &s, &day, &mon, &year);
        
        // Mostrar fecha (formato DD/MM/YYYY)
        Clear_Line(0);
        sprintf(lcd_buffer, "Fecha:%02d/%02d/20%02d", day, mon, year);
        LCD_String_xy(0, 0, lcd_buffer);
        
        // Mostrar hora (formato HH:MM:SS)
        Clear_Line(1);
        sprintf(lcd_buffer, "Hora: %02d:%02d:%02d", h, m, s);
        LCD_String_xy(1, 0, lcd_buffer);
        
        __delay_ms(1000); // Esperar 1 segundo
        refresh_count++;   // Incrementar contador
    }
}

/**
 * Función principal
 */
void main() {
    // --- CONFIGURACIÓN INICIAL ---
    OSCCON = 0x72;    // Configurar oscilador interno a 8MHz
    ADCON1 = 0x0F;     // Desactivar convertidor analógico-digital
    CMCON = 0x07;      // Desactivar comparadores analógicos
    
    // --- INICIALIZACIÓN DE PERIFÉRICOS ---
    LCD_Init();         // Pantalla LCD
    I2C_Master_Init(100000); // I2C a 100kHz (para RTC)
    RTC_Init();         // Reloj de tiempo real
    GPS_Init();         // Módulo GPS

    // --- MENSAJE INICIAL ---
    LCD_Clear();
    LCD_String_xy(0, 0, "Estacion Met"); // Mensaje línea 0
    LCD_String_xy(1, 0, "Iniciando..."); // Mensaje línea 1
    __delay_ms(2000);   // Mostrar por 2 segundos

    // --- BUCLE PRINCIPAL ---
    while(1) {
        // Rotar entre los diferentes displays
        switch(current_display) {
            case SHOW_DHT11:
                Display_DHT11(); // Mostrar datos DHT11
                break;
            case SHOW_GPS:
                Display_GPS();   // Mostrar datos GPS
                break;
            case SHOW_RTC:
                Display_RTC();   // Mostrar hora/fecha
                break;
            default:
                current_display = SHOW_DHT11; // Por seguridad
        }
        
        // Cambiar al siguiente display (rotación cíclica)
        current_display = (current_display + 1) % NUM_DISPLAYS;
        __delay_ms(5000); // Esperar 5 segundos antes de cambiar
    }
}