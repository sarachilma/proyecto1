/*!
\date   2021-09-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\
\par 
Copyright (c) unicauca 2021. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.

\note
Last modified: 2025-05-06 Cristian Valencia <chpayan@unicauca.edu.co>
******************************************************************************
*/

#include "USART_Header_File.h"

/*****************************USART por hardware*******************************/
void USART_Init(long baud_rate)
{
    float temp;
    TRISC6 = 0;  // TX como salida
    TRISC7 = 1;  // RX como entrada
    temp = Baud_value;
    SPBRG = (int)temp;
    TXSTA = 0x20;  // Habilita transmisión
    RCSTA = 0x90;  // Habilita recepción y el puerto serial
}

void USART_TxChar(char out)
{
    while (TXIF == 0);  // Espera a que TXREG esté listo
    TXREG = out;
}

char USART_RxChar()
{
    while (RCIF == 0);  // Espera recepción
    if (RCSTAbits.OERR) {
        CREN = 0;
        NOP();
        CREN = 1;
    }
    return RCREG;
}

void USART_SendString(const char *out)
{
    while (*out != '\0') {
        USART_TxChar(*out++);
    }
}

/*****************************USART por software*******************************/
void SoftUSART_Init()
{
    SOFT_TX_TRIS = 0;  // TX como salida
    SOFT_RX_TRIS = 1;  // RX como entrada
    SOFT_TX_PIN = 1;   // Línea en reposo
}

void SoftUSART_TxChar(char data)
{
    char i;
    SOFT_TX_PIN = 0;  // Bit de inicio
    __delay_us(SOFT_BIT_DELAY_US);

    for (i = 0; i < 8; i++) {
        SOFT_TX_PIN = (data >> i) & 1;
        __delay_us(SOFT_BIT_DELAY_US);
    }

    SOFT_TX_PIN = 1;  // Bit de parada
    __delay_us(SOFT_BIT_DELAY_US);
}

char SoftUSART_RxChar()
{
    char i, data = 0;

    while (SOFT_RX_PIN);  // Esperar bit de inicio (línea baja)

    __delay_us(SOFT_BIT_DELAY_US + SOFT_BIT_DELAY_US / 2);  // Centrar lectura

    for (i = 0; i < 8; i++) {
        if (SOFT_RX_PIN)
            data |= (1 << i);
        __delay_us(SOFT_BIT_DELAY_US);
    }

    // Bit de parada
    __delay_us(SOFT_BIT_DELAY_US);

    return data;
}

void SoftUSART_SendString(const char *str)
{
    while (*str != '\0') {
        SoftUSART_TxChar(*str++);
    }
}

