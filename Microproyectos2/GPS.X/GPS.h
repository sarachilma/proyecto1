/* 
 * File:   gps_uart.h
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:13 PM
 */

#ifndef GPS_H
#define GPS_H

#include <xc.h>
#include <stdint.h>

// Prototipos de funciones
void GPS_Init(void); // Inicializa el módulo GPS
uint8_t GPS_ReadSentence(char *buffer, uint16_t max_len, uint16_t timeout_ms); // Lee una frase NMEA
uint8_t GPS_ParseGPRMC(const char *msg, char *lat, char *ns, char *lon, char *ew); // Parsea datos GPRMC

#endif