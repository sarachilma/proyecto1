/* 
 * File:   LCD.h
 * Author: danis
 *
 * Created on 21 de abril de 2025, 09:13 AM
 */

#ifndef LCD_H
#define LCD_H

#include <xc.h>
#include <stdint.h> // Añadir para uint8_t
#include "Config.h"

// Definición de pines
#define RS LATD0
#define EN LATD1
#define ldata LATD
#define LCD_Port TRISD

#define CMD_CLEAR_LCD 0x01

// Prototipos de funciones
void LCD_Init(void);
void LCD_Command(unsigned char);
void LCD_Char(unsigned char);
void LCD_String(const char *);
void LCD_String_xy(char, char, const char *);
void LCD_Clear(void);
void LCD_ClearLine(char); // Nueva función

#endif