#include "DHT11.h"
#include <stdint.h>

uint8_t DHT11_Read() {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        while (!DHT11_PIN);  // Esperar flanco de subida
        __delay_us(35);
        data <<= 1;
        if (DHT11_PIN) data |= 1;
        while (DHT11_PIN);   // Esperar que el pin baje
    }
    return data;
}

uint8_t DHT11_GetTemperature() {
    DHT11_TRIS = 0;         // Configurar como salida
    DHT11_PIN = 0;          
    __delay_ms(18);
    DHT11_PIN = 1;
    __delay_us(30);
    DHT11_TRIS = 1;         // Configurar como entrada

    if (DHT11_PIN == 0) {
        while (!DHT11_PIN); // Esperar 80µs low
        while (DHT11_PIN);  // Esperar 80µs high

        uint8_t checksum = (
            DHT11_Read() +  // Humedad entera
            DHT11_Read() +  // Humedad decimal
            DHT11_Read() +  // Temp. entera
            DHT11_Read()    // Temp. decimal
        );
        
        if (checksum == DHT11_Read()) {
            return DHT11_Read(); // Retorna temp. entera
        }
    }
    return 255; // Error
}