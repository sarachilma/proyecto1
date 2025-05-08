#include "DHT11.h"

uint8_t DHT11_ReadByte() {
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++) {
        while (!DHT11_PIN); 
        __delay_us(50);     
        data <<= 1;
        if (DHT11_PIN) data |= 1;
        while (DHT11_PIN);  
    }
    return data;
}

uint8_t DHT11_Read(uint8_t *humidity, uint8_t *temperature) {
    DHT11_TRIS = 0;
    DHT11_PIN = 0;
    __delay_ms(18);
    DHT11_PIN = 1;
    __delay_us(30);
    DHT11_TRIS = 1;

    if (DHT11_PIN == 0) {
        while (!DHT11_PIN);
        while (DHT11_PIN);

        uint8_t data[5];
        for (uint8_t i = 0; i < 5; i++) {
            data[i] = DHT11_ReadByte();
        }

        if ((data[0] + data[1] + data[2] + data[3]) == data[4]) {
            *humidity = data[0];
            *temperature = data[2];
            return 1;
        }
    }
    return 0;
}