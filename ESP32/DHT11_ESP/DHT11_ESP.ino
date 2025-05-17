#include <DHT.h>

// Configuración del DHT11
#define DHTPIN 4       // Pin GPIO4 para el DHT11
#define DHTTYPE DHT11  // Tipo de sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("Inicializando sensor DHT11...");
  
  // Inicializar DHT11
  dht.begin();
  
  delay(2000); // Tiempo para estabilización
}

void loop() {
  // Leer humedad y temperatura
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  
  // Verificar si la lectura fue exitosa
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Error al leer el sensor DHT11!");
  } else {
    // Mostrar valores en el monitor serial
    Serial.print("Humedad: ");
    Serial.print(hum);
    Serial.print("%\t");
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println("°C");
  }
  
  delay(2000); // Esperar 2 segundos entre lecturas
}
