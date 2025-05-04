#include "RTC.h"

// Configuración de pines I2C (RB0=SDA, RB1=SCL)
#define SDA_PIN TRISB0
#define SCL_PIN TRISB1

void I2C_Init() {
    TRISB0 = 1;     // SDA como entrada
    TRISB1 = 1;     // SCL como entrada
    SSPCON1 = 0x28; // Usar SSPCON1 en lugar de SSPCON
    SSPADD = 19;    // 100kHz con Fosc=8MHz
    SSPSTAT = 0x80;
}

void I2C_Start() {
    SEN = 1;
    while(SEN);
}

void I2C_Stop() {
    PEN = 1;
    while(PEN);
}

void I2C_Write(uint8_t data) {
    SSPBUF = data;
    while(BF);
    while(SSPCON2 & 0x1F);
}

uint8_t I2C_Read(uint8_t ack) {
    RCEN = 1;
    while(!BF);
    uint8_t data = SSPBUF;
    ACKDT = (ack) ? 0 : 1;
    ACKEN = 1;
    while(ACKEN);
    return data;
}

uint8_t decToBcd(uint8_t val) { 
    return (uint8_t)(((val / 10) << 4) | (val % 10)); // Conversión explícita
}

uint8_t bcdToDec(uint8_t val) { 
    return (uint8_t)(((val >> 4) * 10) + (val & 0x0F)); // Conversión explícita
}

void RTC_Init() {
    I2C_Init();
    // Iniciar reloj (bit CH=0)
    I2C_Start();
    I2C_Write(DS1307_ADDR << 1);
    I2C_Write(0x00);
    I2C_Write(0x00); // CH=0
    I2C_Stop();
}


void RTC_SetTime(uint8_t hour, uint8_t min, uint8_t sec) {
    I2C_Start();
    I2C_Write(DS1307_ADDR << 1);
    I2C_Write(0x00);  // Registro de segundos
    I2C_Write(decToBcd(sec));
    I2C_Write(decToBcd(min));
    I2C_Write(decToBcd(hour) & 0x3F);  // Modo 24h (bit 6=0)
    I2C_Stop();
}


void RTC_SetDate(uint8_t date, uint8_t month, uint8_t year) {
    I2C_Start();
    I2C_Write(DS1307_ADDR << 1);
    I2C_Write(0x04);  
    I2C_Write(decToBcd(date));
    I2C_Write(decToBcd(month));
    I2C_Write(decToBcd(year));
    I2C_Stop();
}

void RTC_GetTime(uint8_t *hour, uint8_t *min, uint8_t *sec) {
    I2C_Start();
    I2C_Write(DS1307_ADDR << 1);
    I2C_Write(0x00);  // Puntero a segundos
    I2C_Start();
    I2C_Write((DS1307_ADDR << 1) | 1);  // Dirección + lectura
    
    *sec = bcdToDec(I2C_Read(1) & 0x7F);  // Ignorar bit CH
    *min = bcdToDec(I2C_Read(1));
    *hour = bcdToDec(I2C_Read(0) & 0x3F);  // Modo 24h
    
    I2C_Stop();
}


void RTC_GetDate(uint8_t *date, uint8_t *month, uint8_t *year) {
    I2C_Start();
    I2C_Write(DS1307_ADDR << 1);
    I2C_Write(0x04); 
    I2C_Start();
    I2C_Write((DS1307_ADDR << 1) | 1);  // Dirección + lectura
    
    *date = bcdToDec(I2C_Read(1));
    *month = bcdToDec(I2C_Read(1));
    *year = bcdToDec(I2C_Read(0));
    
    I2C_Stop();
}