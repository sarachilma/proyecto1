#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
  
  if (!rtc.begin()) {
    Serial.println("Error: No se encuentra el RTC DS1307");
    while (1);
  }

  // Opción 1: Configurar hora automáticamente (descomentar solo para la primera configuración)
  // Serial.println("Configurando hora inicial...");
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Hora actual del PC
  
  // Opción 2: Configurar hora manualmente (descomentar y ajustar)
  // rtc.adjust(DateTime(2025, 5, 20, 12, 0, 0)); // Año, Mes, Día, Hora, Minuto, Segundo

  Serial.println("RTC DS1307 listo");
}

void printTwoDigits(int number) {
  if (number < 10) Serial.print('0');
  Serial.print(number);
}

void loop() {
  DateTime now = rtc.now();
  
  // Fecha: DD/MM/AAAA
  printTwoDigits(now.day());
  Serial.print('/');
  printTwoDigits(now.month());
  Serial.print('/');
  Serial.print(now.year());
  Serial.print(' ');
  
  // Hora: HH:MM:SS
  printTwoDigits(now.hour());
  Serial.print(':');
  printTwoDigits(now.minute());
  Serial.print(':');
  printTwoDigits(now.second());
  
  Serial.println();
  delay(1000);
}