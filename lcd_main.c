/*!
\file   lcd_main.c
\date   2021-09-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  keypad 4x4 and LCD 16X2 4BITS.
\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2021. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.

\note
Last modified: 2025-03-26 Cristian Valencia <chpayan@unicauca.edu.co>
******************************************************************************
*/

#include <xc.h>
#include <pic18f4550.h>
#include "Config.h"
#include "LCD.h"



unsigned char password[5] ={'2','0','2','1',0};

unsigned char pass_user[5];
unsigned char idx = 0;

void main() 
{
    char key;
    OSCCON = 0x72;

    RBPU=0;                             /* activate pull-up resistor */
    LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
    LCD_String_xy(0,0,"WELCOME");
    LCD_Command(0xC0);                  /* display pressed key on 2nd line of LCD */
    while(1)
    {
        LCD_String_xy(0,0,"MICROCONTROLADORES");
		__delay_ms(2000);
		LCD_Clear();
		__delay_ms(1000);        
    }
    
}