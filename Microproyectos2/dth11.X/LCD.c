#include "LCD.h"
#include "Config.h"

void LCD_Init()
{
    LCD_Port = 0;
    __delay_ms(15);
    LCD_Command(0x02);
    LCD_Command(0x28);
    LCD_Command(CMD_CLEAR_LCD);
    LCD_Command(0x0c);
    LCD_Command(0x06);
}

void LCD_Command(unsigned char cmd)
{
    ldata = (ldata & 0x0f) | (0xF0 & cmd);
    RS = 0;
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(1);
    ldata = (ldata & 0x0f) | ((cmd << 4) & 0xF0);
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(3);
}

void LCD_Char(unsigned char dat)
{
    ldata = (ldata & 0x0f) | (0xF0 & dat);
    RS = 1;
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(1);
    ldata = (ldata & 0x0f) | ((dat << 4) & 0xF0);
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(3);
}

void LCD_String(const char *msg)
{
    while((*msg) != 0) {        
        LCD_Char(*msg);
        msg++;    
    }
}

void LCD_String_xy(char row, char pos, const char *msg) {
    char location = 0;
    if (row == 0) {
        location = 0x80 | (pos & 0x0F); // Primera fila
    } else {
        location = 0xC0 | (pos & 0x0F); // Segunda fila
    }
    LCD_Command(location); // Posicionar cursor
    LCD_String(msg);       // Escribir mensaje
}

void LCD_Clear()
{
    LCD_Command(CMD_CLEAR_LCD);
    __delay_ms(2);
}