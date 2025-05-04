/* 
 * File:   RTC.h
 * Author: danis
 *
 * Created on 21 de abril de 2025, 09:14 AM
 */

#ifndef RTC_H
#define RTC_H

#include <xc.h>
#include <stdint.h>
#include "Config.h"

#define DS1307_ADDR 0x68


void RTC_Init(void);
void RTC_SetTime(uint8_t hour, uint8_t min, uint8_t sec);
void RTC_SetDate(uint8_t date, uint8_t month, uint8_t year);  
void RTC_GetTime(uint8_t *hour, uint8_t *min, uint8_t *sec);
void RTC_GetDate(uint8_t *date, uint8_t *month, uint8_t *year);  

#endif