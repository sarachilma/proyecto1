#include "lcd.h" // Incluye el archivo de cabecera de la LCD
#define _XTAL_FREQ 8000000 // Frecuencia de 8 MHz

// Función para generar un pulso en el pin EN
void Lcd_Pulse_EN(void) {
    EN = 1;
    __delay_us(10);
    EN = 0;
    __delay_us(10);
}

// Función para enviar un nibble (4 bits) a la LCD
void Lcd_Send_Nibble(unsigned char data) {
    D4 = (data >> 0) & 1;
    D5 = (data >> 1) & 1;
    D6 = (data >> 2) & 1;
    D7 = (data >> 3) & 1;
    Lcd_Pulse_EN();
}

// Función para enviar un comando a la LCD
void Lcd_Cmd(unsigned char cmd) {
    RS = 0; // Modo comando
    Lcd_Send_Nibble(cmd >> 4); // Enviar nibble alto
    Lcd_Send_Nibble(cmd & 0x0F); // Enviar nibble bajo
    __delay_ms(2); // Retardo para comandos que requieren más tiempo
}

// Función para escribir un carácter en la LCD
void Lcd_Write_Char(char data) {
    RS = 1; // Modo dato
    Lcd_Send_Nibble(data >> 4); // Enviar nibble alto
    Lcd_Send_Nibble(data & 0x0F); // Enviar nibble bajo
    __delay_us(40); // Retardo para escritura de caracteres
}

// Función para escribir una cadena en la LCD
void Lcd_Write_String(const char *str) {
    while (*str) {
        Lcd_Write_Char(*str++);
    }
}

// Función para posicionar el cursor en una fila y columna específica
void Lcd_Set_Cursor(unsigned char row, unsigned char col) {
    unsigned char address;
    if (row == 0)
        address = 0x80 + col; // Primera fila
    else
        address = 0xC0 + col; // Segunda fila
    Lcd_Cmd(address);
}

// Función para limpiar la pantalla
void Lcd_Clear(void) {
    Lcd_Cmd(0x01); // Comando para limpiar la pantalla
    __delay_ms(2); // Retardo para que el comando se complete
}

// Función para inicializar la LCD
void Lcd_Init(void) {
    // Configurar pines como salidas
    TRISAbits.TRISA0 = 0; // RS
    TRISAbits.TRISA1 = 0; // RW
    TRISAbits.TRISA2 = 0; // EN
    TRISBbits.TRISB0 = 0; // D4
    TRISBbits.TRISB1 = 0; // D5
    TRISBbits.TRISB2 = 0; // D6
    TRISBbits.TRISB3 = 0; // D7

    RW = 0; // Modo escritura

    // Inicialización del LCD en modo 4 bits
    __delay_ms(20); // Esperar para que el LCD se estabilice
    Lcd_Send_Nibble(0x03); // Inicialización
    __delay_ms(5);
    Lcd_Send_Nibble(0x03);
    __delay_us(100);
    Lcd_Send_Nibble(0x03);
    Lcd_Send_Nibble(0x02); // Modo 4 bits

    Lcd_Cmd(0x28); // Configurar LCD en 4 bits, 2 líneas, 5x7 puntos
    Lcd_Cmd(0x0C); // Encender LCD, cursor apagado
    Lcd_Cmd(0x06); // Incrementar cursor, no desplazar
    Lcd_Clear();   // Limpiar pantalla
}
