/* 
 * File:   DHT11.h
 * Author: Esteban
 *
 * Created on 3 de abril de 2025, 03:21 PM
 */

#ifndef DHT11_H
#define DHT11_H

#include <xc.h>
#include <stdint.h>
#include "Config.h"

#define DHT11_PIN  PORTAbits.RA0
#define DHT11_TRIS TRISAbits.TRISA0 

// Cambiamos la función para devolver humedad y temperatura por referencia
uint8_t DHT11_Read(uint8_t *humidity, uint8_t *temperature);

#endif