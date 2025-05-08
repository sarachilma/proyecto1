#ifndef DHT11_H
#define DHT11_H

#include <xc.h>
#include <stdint.h>

#define DHT11_TRIS TRISBbits.TRISB2
#define DHT11_PIN  PORTBbits.RB2

uint8_t DHT11_Read(uint8_t *humidity, uint8_t *temperature);
uint8_t DHT11_ReadByte(void);

#endif