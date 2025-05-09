/* 
 * File:   Config.h
 * Author: usuario
 *
 * Created on 23 de abril de 2025, 02:12 PM
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <xc.h>

// Configuración del PIC18F4550
#pragma config PLLDIV = 1       // No prescaler para el PLL (4MHz input)
#pragma config CPUDIV = OSC1_PLL2// CPU clock divide por 2 (8MHz/2 = 4MHz)
#pragma config USBDIV = 1       // USB clock desde oscilador primario

#pragma config FOSC = INTOSC_EC // Oscilador interno, CLKO en RA6
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor desactivado
#pragma config IESO = OFF       // Oscillator Switchover desactivado

#pragma config PWRT = OFF       // Power-up Timer desactivado
#pragma config BOR = ON         // Brown-out Reset activado
#pragma config BORV = 3         // Voltage level 2.05V
#pragma config VREGEN = OFF     // USB Voltage Regulator desactivado

#pragma config WDT = OFF        // Watchdog Timer desactivado
#pragma config WDTPS = 32768    // Postscaler value (no usado con WDT off)

#pragma config CCP2MX = ON      // CCP2 multiplexado con RC1
#pragma config PBADEN = OFF     // PORTB<4:0> como pines digitales
#pragma config LPT1OSC = OFF    // Timer1 en modo high power
#pragma config MCLRE = OFF      // MCLR desactivado, RE3 como entrada

#pragma config STVREN = ON      // Stack Overflow Reset activado
#pragma config LVP = OFF        // Low Voltage Programming desactivado
#pragma config ICPRT = OFF      // Debug port desactivado
#pragma config XINST = OFF      // Extended Instruction Set desactivado

// Configuraciones de protección
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
#pragma config CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
#pragma config WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
#pragma config EBTRB = OFF

// Configuración para UART y GPS
#define _XTAL_FREQ 8000000      // Frecuencia del oscilador interno
#define BAUDRATE 9600           // Mismo baudrate que el NEO-6M por defecto

#endif
