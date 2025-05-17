#include <DHT.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <RTClib.h>

// Configuración del DHT11
#define DHTPIN 4       // Pin GPIO4 para el DHT11
#define DHTTYPE DHT11  // Tipo de sensor
DHT dht(DHTPIN, DHTTYPE);

// Configuración del GPS
#define RXD2 16  // GPIO16 como RX
#define TXD2 17  // GPIO17 como TX
TinyGPSPlus gps;
HardwareSerial ss(1);  // UART1 del ESP32

// Configuración del RTC
RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Inicializar DHT11
  Serial.println("Inicializando sensores...");
  dht.begin();
  
  // Inicializar GPS
  ss.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  // Inicializar RTC
  if (!rtc.begin()) {
    Serial.println("Error: No se encuentra el RTC DS1307");
    while (1);
  }
  
  Serial.println("\nSistema de monitoreo integrado listo");
  Serial.println("----------------------------------");
  delay(2000); // Tiempo para estabilización
}

void loop() {
  // Leer y mostrar datos del RTC
  displayRTCData();
  
  // Leer y mostrar datos del DHT11
  displayDHTData();
  
  // Leer y mostrar datos del GPS
  displayGPSData();
  
  Serial.println("----------------------------------");
  delay(2000); // Esperar 2 segundos entre lecturas
}

void displayDHTData() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Error al leer el sensor DHT11!");
  } else {
    Serial.print("Clima: Humedad=");
    Serial.print(hum);
    Serial.print("% | Temp=");
    Serial.print(temp);
    Serial.println("°C");
  }
}

void displayGPSData() {
  bool newData = false;
  
  // Leer datos del GPS durante 1 segundo
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (ss.available()) {
      if (gps.encode(ss.read())) {
        newData = true;
      }
    }
  }
  
  if (newData) {
    if (gps.location.isValid()) {
      Serial.print("GPS: Lat=");
      printDMS(gps.location.lat(), gps.location.lat() >= 0 ? 'N' : 'S');
      Serial.print(" | Lon=");
      printDMS(gps.location.lng(), gps.location.lng() >= 0 ? 'E' : 'W');
      
      if (gps.altitude.isValid()) {
        Serial.print(" | Alt=");
        Serial.print(gps.altitude.meters(), 1);
        Serial.print("m");
      }
      
      if (gps.satellites.isValid()) {
        Serial.print(" | Sats=");
        Serial.print(gps.satellites.value());
      }
      
      Serial.println();
    } else {
      Serial.println("GPS: Esperando señal satelital...");
    }
  } else if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("GPS: Error - No se detecta señal");
  }
}

void displayRTCData() {
  DateTime now = rtc.now();
  
  Serial.print("Fecha/Hora: ");
  printTwoDigits(now.day());
  Serial.print('/');
  printTwoDigits(now.month());
  Serial.print('/');
  Serial.print(now.year());
  Serial.print(' ');
  printTwoDigits(now.hour());
  Serial.print(':');
  printTwoDigits(now.minute());
  Serial.print(':');
  printTwoDigits(now.second());
  Serial.println();
}

// Función para convertir y mostrar en formato grados, minutos, segundos
void printDMS(double decimalDegrees, char hemisphere) {
  decimalDegrees = abs(decimalDegrees);
  int degrees = int(decimalDegrees);
  double minutesDecimal = (decimalDegrees - degrees) * 60;
  int minutes = int(minutesDecimal);
  double seconds = (minutesDecimal - minutes) * 60;
  
  Serial.print(degrees);
  Serial.print("°");
  Serial.print(minutes);
  Serial.print("'");
  Serial.print(seconds, 1);
  Serial.print("\"");
  Serial.print(hemisphere);
}

void printTwoDigits(int number) {
  if (number < 10) Serial.print('0');
  Serial.print(number);
}