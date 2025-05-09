#ifndef RTC_H
#define RTC_H

#include <xc.h>

void rtc_init(void);
void rtc_set_time(unsigned char hour, unsigned char min, unsigned char sec);
void rtc_get_time(unsigned char* hour, unsigned char* min, unsigned char* sec);

#endif

