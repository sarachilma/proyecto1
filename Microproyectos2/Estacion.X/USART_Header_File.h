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

#ifndef USART_HEADER_FILE_H
#define	USART_HEADER_FILE_H
#include <pic18f4550.h>
#include <xc.h>

// --------- Configuración general ----------
#define _XTAL_FREQ 8000000UL
#define F_CPU _XTAL_FREQ/64
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)

// --------- USART por hardware -------------
void USART_Init(long baud_rate);
void USART_TxChar(char out);
void USART_SendString(const char *out);
char USART_RxChar();

// --------- USART por software -------------
#define SOFT_TX_PIN LATBbits.LATB0
#define SOFT_TX_TRIS TRISBbits.TRISB0
#define SOFT_RX_PIN PORTBbits.RB1
#define SOFT_RX_TRIS TRISBbits.TRISB1

#define SOFT_BAUD_RATE 9600
#define SOFT_BIT_DELAY_US (1000000 / SOFT_BAUD_RATE)

void SoftUSART_Init();
void SoftUSART_TxChar(char data);
char SoftUSART_RxChar();
void SoftUSART_SendString(const char *str);

#endif	/* USART_HEADER_FILE_H */
