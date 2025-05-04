#include "LCD.h"

void LCD_Init(void) {
    LCD_Port = 0;
    __delay_ms(15);
    LCD_Command(0x02);
    LCD_Command(0x28);
    LCD_Command(CMD_CLEAR_LCD);
    LCD_Command(0x0C);
    LCD_Command(0x06);
}

void LCD_Command(uint8_t cmd) {
    ldata = (ldata & 0x0F) | (cmd & 0xF0);
    RS = 0;
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(1);
    
    ldata = (ldata & 0x0F) | ((cmd << 4) & 0xF0);
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(3);
}

void LCD_Char(uint8_t dat) {
    ldata = (ldata & 0x0F) | (dat & 0xF0);
    RS = 1;
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(1);
    
    ldata = (ldata & 0x0F) | ((dat << 4) & 0xF0);
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(3);
}

void LCD_String(const char *msg) {
    while(*msg != 0) {
        LCD_Char(*msg);
        msg++;
    }
}

void LCD_String_xy(uint8_t row, uint8_t pos, const char *msg) {
    uint8_t location;
    pos = (pos > 15) ? 15 : pos; // Limitar a 16 caracteres
    
    if(row == 0) {
        location = 0x80 + pos;
    } else {
        location = 0xC0 + pos;
    }
    
    LCD_Command(location);
    LCD_String(msg);
}

void LCD_Clear(void) {
    LCD_Command(CMD_CLEAR_LCD);
}