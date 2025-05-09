#include "GPS.h"
#include "Config.h"
#include <string.h>

// Inicializaci�n del m�dulo GPS
void GPS_Init(void) {
    TRISC7 = 1;     // Configura RC7 como entrada (RX del GPS)
    
    // Configuraci�n del UART para 9600 baudios a 8MHz
    BAUDCON = 0x08; // BRG16 = 1 (modo 16 bits)
    TXSTA = 0x24;   // BRGH = 1, TXEN = 0 (solo recepci�n)
    RCSTA = 0x90;   // SPEN = 1, CREN = 1 (habilita UART y recepci�n continua)
    SPBRG = 207;    // Valor para 9600 baudios con BRG16=1 y BRGH=1
    
    // Limpieza inicial del buffer de recepci�n
    while(PIR1bits.RCIF) {
        volatile char dummy = RCREG; // Lee y descarta cualquier dato existente
        (void)dummy;
    }
    PIR1bits.RCIF = 0; // Limpia flag de interrupci�n
}

// Lee una frase NMEA desde el GPS
uint8_t GPS_ReadSentence(char *buffer, uint16_t max_len, uint16_t timeout_ms) {
    uint16_t i = 0; // �ndice para el buffer
    char c;         // Car�cter actual
    uint8_t started = 0; // Bandera de inicio de frase

    // Reinicia la recepci�n UART
    RCSTAbits.CREN = 0;
    NOP(); // Peque�a pausa
    RCSTAbits.CREN = 1;
    
    // Limpia el buffer de recepci�n
    while(PIR1bits.RCIF) {
        volatile char dummy = RCREG;
        (void)dummy;
    }

    // Espera la llegada de datos con timeout
    for(uint16_t t = 0; t < timeout_ms; t++) {
        if(PIR1bits.RCIF) { // Si hay dato disponible
            c = RCREG; // Lee el car�cter
            
            // Maneja error de sobreflujo
            if(RCSTAbits.OERR) {
                RCSTAbits.CREN = 0;
                RCSTAbits.CREN = 1;
                continue;
            }
            
            // Detecta inicio de frase NMEA
            if(!started && c == '$') {
                started = 1;
                buffer[i++] = c;
            } 
            // Almacena la frase hasta encontrar salto de l�nea
            else if(started) {
                if(c == '\n' || i >= max_len-1) { // Fin de frase
                    buffer[i] = '\0';
                    return 1; // �xito
                }
                if(c != '\r') buffer[i++] = c; // Ignora retorno de carro
            }
        }
        __delay_us(100); // Ajuste para 9600 baudios
    }
    return 0; // Timeout
}

// Parsea una frase GPRMC para extraer posici�n
uint8_t GPS_ParseGPRMC(const char *msg, char *lat, char *ns, char *lon, char *ew) {
    char buf[100];       // Buffer local para trabajo
    char *token;         // Token actual
    uint8_t field = 0;   // N�mero de campo actual
    uint8_t data_valid = 0; // Bandera de datos v�lidos

    // Verifica que sea una frase GPRMC
    if(strstr(msg, "$GPRMC") == NULL) return 0;

    // Copia segura del mensaje
    strncpy(buf, msg, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';

    // Procesamiento por campos separados por comas
    token = strtok(buf, ",");
    while(token && field <= 6) { // Solo campos relevantes (0-6)
        switch(field) {
            case 2: // Campo 2: Estado (A=V�lido, V=Inv�lido)
                data_valid = (token[0] == 'A');
                break;
            case 3: // Campo 3: Latitud (DDMM.MMMM)
                if(lat && data_valid) { 
                    strncpy(lat, token, 7); // Copia 7 caracteres (DDMM.MM)
                    lat[7] = '\0'; // Asegura terminaci�n
                }
                break;
            case 4: // Campo 4: Indicador N/S
                if(ns && data_valid) {
                    ns[0] = token[0]; // 'N' o 'S'
                    ns[1] = '\0';
                }
                break;
            case 5: // Campo 5: Longitud (DDDMM.MMMM)
                if(lon && data_valid) {
                    strncpy(lon, token, 8); // Copia 8 caracteres (DDDMM.MM)
                    lon[8] = '\0';
                }
                break;
            case 6: // Campo 6: Indicador E/W
                if(ew && data_valid) {
                    ew[0] = token[0]; // 'E' o 'W'
                    ew[1] = '\0';
                }
                break;
        }
        token = strtok(NULL, ","); // Siguiente campo
        field++;
    }
    return (data_valid && field >= 6); // Retorna 1 si datos son v�lidos
}
