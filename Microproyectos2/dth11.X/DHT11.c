#include "DHT11.h"
#include <stdint.h>

uint8_t DHT11_Read() {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        while (!DHT11_PIN); // Esperar flanco de subida
        __delay_us(50);     // Aumentado a 50µs para mayor estabilidad
        data <<= 1;
        if (DHT11_PIN) data |= 1;
        while (DHT11_PIN);  // Esperar a que el pin baje
    }
    return data;
}

uint8_t DHT11_GetTemperature() {
    DHT11_TRIS = 0;         // Configurar RA0 como salida
    DHT11_PIN = 0;          
    __delay_ms(20);         // Aumentado a 20ms para garantizar inicio
    DHT11_PIN = 1;
    __delay_us(40);         // Aumentado a 40µs
    DHT11_TRIS = 1;         // Configurar RA0 como entrada

    if (DHT11_PIN == 0) {
        uint16_t timeout = 1000;
        while (!DHT11_PIN && timeout--) __delay_us(1); // Timeout para evitar bloqueos
        timeout = 1000;
        while (DHT11_PIN && timeout--) __delay_us(1);

        uint8_t data[5];
        for (uint8_t i = 0; i < 5; i++) {
            data[i] = DHT11_Read();
        }

        if (data[0] + data[1] + data[2] + data[3] == data[4]) {
            return data[2];  // Retorna temperatura entera
        }
    }
    return 255; // Error
}