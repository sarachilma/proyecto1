#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "Config.h"
#include "LCD.h"
#include "DHT11.h"
#include "GPS.h"
#include "ds1307.h"
#include "i2c.h"


// Estados del sistema
#define SYSTEM_OFF 0
#define SYSTEM_ON 1

// Variables globales volátiles (accedidas desde interrupciones)
volatile unsigned char system_state = SYSTEM_ON;
volatile unsigned char system_needs_reset = 0;
char lcd_buffer[17];

// Prototipos de funciones
void Initialize_System(void);
void Setup_Interrupts(void);
void Enter_Low_Power_Mode(void);
void Display_DHT11(void);
void Display_GPS(void);
void Display_RTC(void);
void Clear_Line(unsigned char line);

// ==================== CONFIGURACIÓN INICIAL ====================
void Initialize_System() {
    // 1. Configuración básica del PIC
    OSCCON = 0x72;      // Oscilador interno a 8MHz
    ADCON1 = 0x0F;       // Todos los pines como digitales
    CMCON = 0x07;        // Comparadores analógicos desactivados
    TRISB = 0b00001000;  // RB3 como entrada (RX BT), RB2 como salida (TX BT)

    // 2. Inicialización de periféricos
    LCD_Init();
    I2C_Master_Init(100000); // I2C a 100kHz
    RTC_Init();
    GPS_Init();
    
    // 3. Mensaje inicial
    LCD_Clear();
    LCD_String_xy(0,0,"Estacion Meteo");
    LCD_String_xy(1,0,"BT: Esperando...");
    __delay_ms(2000);
}

// ==================== INTERRUPCIONES ====================
void Setup_Interrupts() {
    // 1. Configurar interrupción por flanco de bajada en RB3 (INT0)
    INTCONbits.INT0IE = 1;    // Habilitar INT0
    INTCONbits.INT0IF = 0;    // Limpiar flag
    INTCON2bits.INTEDG0 = 0;  // Detectar flanco de bajada
    
    // 2. Configurar prioridades (para PIC18)
    RCONbits.IPEN = 1;        // Habilitar prioridades
    INTCONbits.GIEH = 1;      // Habilitar interrupciones globales
    INTCONbits.GIEL = 1;      // Habilitar interrupciones de baja prioridad
}

void __interrupt(high_priority) HighPriorityISR() {
    if (INTCONbits.INT0IF) {  // Si la interrupción fue por RB3
        system_state = !system_state;
        system_needs_reset = 1;
        INTCONbits.INT0IF = 0; // Limpiar flag
    }
}

// ==================== MODO BAJO CONSUMO ====================
void Enter_Low_Power_Mode() {
    LCD_Clear();
    LCD_String_xy(0,0,"Sistema OFF");
    LCD_String_xy(1,0,"En espera...");
    
    // Desactivar periféricos para ahorrar energía (opcional)
    // (Implementar según tus necesidades)
}

// ==================== FUNCIONES DE VISUALIZACIÓN ====================
void Clear_Line(unsigned char line) {
    LCD_Command(line == 0 ? 0x80 : 0xC0);
    for(unsigned char i=0; i<16; i++) LCD_Char(' ');
}

void Display_DHT11() {
    unsigned char hum = 0, temp = 0;
    Clear_Line(0);
    Clear_Line(1);
    
    if(DHT11_Read(&hum, &temp)) {
        sprintf(lcd_buffer, "H: %d%%", hum);
        LCD_String_xy(0, 0, lcd_buffer);
        sprintf(lcd_buffer, "T: %d\xDF""C", temp);
        LCD_String_xy(1, 0, lcd_buffer);
    } else {
        LCD_String_xy(0, 0, "DHT11: Error");
        LCD_String_xy(1, 0, "Reintentando...");
    }
}

void Display_GPS() {
    char buffer[100] = {0};
    char lat[10] = {0}, ns[2] = {0}, lon[11] = {0}, ew[2] = {0};
    
    Clear_Line(0);
    Clear_Line(1);
    
    if(GPS_ReadSentence(buffer, sizeof(buffer), 500)) {
        if(strstr(buffer, "$GPRMC") && GPS_ParseGPRMC(buffer, lat, ns, lon, ew)) {
            sprintf(lcd_buffer, "Lat:%s%s", lat, ns);
            LCD_String_xy(0, 0, lcd_buffer);
            sprintf(lcd_buffer, "Lon:%s%s", lon, ew);
            LCD_String_xy(1, 0, lcd_buffer);
        } else {
            LCD_String_xy(0, 0, "GPS: Sin datos");
            LCD_String_xy(1, 0, "Buscando...");
        }
    } else {
        LCD_String_xy(0, 0, "GPS: Error");
        LCD_String_xy(1, 0, "Reintentando...");
    }
}

void Display_RTC() {
    unsigned char h = 0, m = 0, s = 0, day = 0, mon = 0, year = 0;
    int refresh_count = 0;
    
    while (refresh_count < 5 && system_state == SYSTEM_ON) {
        RTC_GetDateTime(&h, &m, &s, &day, &mon, &year);
        
        Clear_Line(0);
        sprintf(lcd_buffer, "Fecha:%02d/%02d/20%02d", day, mon, year);
        LCD_String_xy(0, 0, lcd_buffer);
        
        Clear_Line(1);
        sprintf(lcd_buffer, "Hora: %02d:%02d:%02d", h, m, s);
        LCD_String_xy(1, 0, lcd_buffer);
        
        __delay_ms(1000);
        refresh_count++;
        
        if (system_needs_reset) break; // Salir si hay cambio de estado
    }
}

// ==================== PROGRAMA PRINCIPAL ====================
void main() {
    Initialize_System();
    Setup_Interrupts();
    
    while(1) {
        if (system_state == SYSTEM_ON) {
            if (system_needs_reset) {
                Initialize_System(); // Reinicialización completa
                system_needs_reset = 0;
            }
            
            // Ciclo normal de operación
            Display_DHT11();
            __delay_ms(5000);
            if (system_state == SYSTEM_OFF) continue;
            
            Display_GPS();
            __delay_ms(5000);
            if (system_state == SYSTEM_OFF) continue;
            
            Display_RTC();
        } else {
            Enter_Low_Power_Mode();
            while (system_state == SYSTEM_OFF) {
                __delay_ms(100); // Espera activa de bajo consumo
            }
        }
    }
}