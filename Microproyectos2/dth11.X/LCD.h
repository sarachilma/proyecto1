/* 
 * File:   LCD.h
 * Author: Esteban
 *
 * Created on 3 de abril de 2025, 03:25 PM
 */

#ifndef LCD_H
#define LCD_H

#include <xc.h>
#include <stdint.h>

#define RS LATD0
#define EN LATD1
#define ldata LATD
#define LCD_Port TRISD
   
#define CMD_CLEAR_LCD 0x01

void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Char(unsigned char dat);
void LCD_String(const char *msg);
void LCD_String_xy(char row, char pos, const char *msg);  // Cambiado a char para compatibilidad
void LCD_Clear(void);

#endif