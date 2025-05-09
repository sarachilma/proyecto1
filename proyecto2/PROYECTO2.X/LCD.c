#include "LCD.h"

void LCD_Init() {
    LCD_Port = 0;                   // PORT como salida
    __delay_ms(15);                 // Espera inicial
    LCD_Command(0x02);              // Modo 4 bits
    LCD_Command(0x28);              // 2 líneas, matriz 5x8
    LCD_Command(CMD_CLEAR_LCD);     // Limpiar display
    LCD_Command(0x0C);              // Display ON, cursor OFF
    LCD_Command(0x06);              // Incremento de cursor
}

void LCD_Command(unsigned char cmd) {
    ldata = (unsigned char)((ldata & 0x0F) | (0xF0 & cmd)); // Conversión explícita
    RS = 0;
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(1);
    
    ldata = (unsigned char)((ldata & 0x0F) | ((cmd & 0x0F) << 4)); // Conversión explícita
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(3);
}

void LCD_Char(unsigned char dat) {
    ldata = (unsigned char)((ldata & 0x0F) | (0xF0 & dat)); // Conversión explícita
    RS = 1;
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(1);
    
    ldata = (unsigned char)((ldata & 0x0F) | ((dat & 0x0F) << 4)); // Conversión explícita
    EN = 1;
    NOP();
    EN = 0;
    __delay_ms(3);
}

void LCD_String(const char *msg) {
    while(*msg != '\0') {
        LCD_Char(*msg);
        msg++;
    }
}

void LCD_String_xy(char row, char pos, const char *msg) {
    char location = (row == 0) ? (0x80 | (pos & 0x0F)) : (0xC0 | (pos & 0x0F));
    LCD_Command(location);
    LCD_String(msg);
}

void LCD_Clear() {
    LCD_Command(CMD_CLEAR_LCD);
    __delay_ms(2);
}

void LCD_ClearLine(char row) {
    unsigned char i; // Cambiado de uint8_t a unsigned char
    char location = (row == 0) ? 0x80 : 0xC0;
    LCD_Command(location);
    for(i = 0; i < 16; i++) {
        LCD_Char(' ');
    }
}
