#include <xc.h>
#include "config.h"

#include "RTC.h"

void main(void) {
    unsigned char hour, minute, second;
    char display[17];

    LCD_Init();
    LCD_Clear();
    rtc_init();
    
    // Configurar hora inicial: 18:02:00
    rtc_set_time(18, 2, 0);

    while (1) {
        rtc_get_time(&hour, &minute, &second);

        LCD_Set_Cursor(1, 1);
        sprintf(display, "Hora: %02u:%02u:%02u", hour, minute, second);
        LCD_Write_String(display);

        __delay_ms(1000);
    }
}
