#include "DHT11.h"
#include <stdint.h>

uint8_t DHT11_ReadByte() {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        while (!DHT11_PIN); // Esperar flanco de subida
        __delay_us(50);     // Esperar 50µs para determinar el bit
        data <<= 1;
        if (DHT11_PIN) data |= 1;
        while (DHT11_PIN);  // Esperar a que el pin baje
    }
    return data;
}

uint8_t DHT11_Read(uint8_t *humidity, uint8_t *temperature) {
    DHT11_TRIS = 0;         // Configurar como salida
    DHT11_PIN = 0;          // Iniciar comunicación
    __delay_ms(18);
    DHT11_PIN = 1;
    __delay_us(30);
    DHT11_TRIS = 1;         // Configurar como entrada

    if (DHT11_PIN == 0) {
        while (!DHT11_PIN); // Esperar respuesta (80µs low)
        while (DHT11_PIN);  // Esperar 80µs high

        // Leer los 5 bytes de datos
        uint8_t data[5];
        for (uint8_t i = 0; i < 5; i++) {
            data[i] = DHT11_ReadByte();
        }

        // Verificar checksum
        if ((data[0] + data[1] + data[2] + data[3]) == data[4]) {
            *humidity = data[0];    // Humedad entera
            *temperature = data[2]; // Temperatura entera
            return 1; // Éxito
        }
    }
    return 0; // Error
}