/* 
 * File:   LCD.h
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:12 PM
 */

#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <xc.h>
#include "Config.h"
#include <pic18f4550.h>
#include <stdint.h>

/*********************Definition of Ports********************************/
#define RS LATD0
#define EN LATD1
#define ldata LATD
#define LCD_Port TRISD
   
#define CMD_CLEAR_LCD 0x01

void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Char(uint8_t dat);
void LCD_String(const char *msg);
void LCD_String_xy(uint8_t row, uint8_t pos, const char *msg);
void LCD_Clear(void);

#ifdef __cplusplus
}
#endif

#endif
