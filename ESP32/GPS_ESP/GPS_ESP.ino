#include <TinyGPS++.h>

#define RXD2 16  // GPIO16 como RX
#define TXD2 17  // GPIO17 como TX

TinyGPSPlus gps;
HardwareSerial ss(1);  // UART1 del ESP32

void setup() {
  Serial.begin(115200);
  ss.begin(9600, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println("\nDatos GPS Formateados");
  Serial.println("---------------------");
}

void loop() {
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      displayFormattedData();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("Error: No se detecta señal GPS");
    while(true);
  }
}

void displayFormattedData() {
  if (gps.location.isValid()) {
    // Mostrar Latitud en formato ° ' "
    Serial.print("Lat: ");
    printDMS(gps.location.lat(), gps.location.lat() >= 0 ? 'N' : 'S');
    
    // Mostrar Longitud en formato ° ' "
    Serial.print(" Lon: ");
    printDMS(gps.location.lng(), gps.location.lng() >= 0 ? 'E' : 'W');
    
    // Mostrar Altura
    Serial.print(" Alt: ");
    if (gps.altitude.isValid()) {
      Serial.print(gps.altitude.meters(), 1);
      Serial.println(" m");
    } else {
      Serial.println("---");
    }
  } else {
    Serial.println("Esperando señal satelital...");
  }
  delay(1000);
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
