/* 
 * File:   lcd.h
 * Author: Esteban
 *
 * Created on 17 de marzo de 2025, 07:57 PM
 */

#ifndef LCD_H
#define LCD_H

#include <xc.h> // Incluye la librería del compilador XC8

// Definiciones de pines para la LCD
#define RS PORTAbits.RA0 // Pin RS
#define RW PORTAbits.RA1 // Pin RW
#define EN PORTAbits.RA2 // Pin EN
#define D4 PORTBbits.RB0 // Pin D4
#define D5 PORTBbits.RB1 // Pin D5
#define D6 PORTBbits.RB2 // Pin D6
#define D7 PORTBbits.RB3 // Pin D7

// Prototipos de funciones
void Lcd_Init(void); // Inicializa la LCD
void Lcd_Cmd(unsigned char cmd); // Envía un comando a la LCD
void Lcd_Write_Char(char data); // Escribe un carácter en la LCD
void Lcd_Write_String(const char *str); // Escribe una cadena en la LCD
void Lcd_Set_Cursor(unsigned char row, unsigned char col); // Posiciona el cursor
void Lcd_Clear(void); // Limpia la pantalla

#endif

