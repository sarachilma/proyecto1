#include <Arduino.h>

// Definición de los pines de los LEDs
#define LED1 12    // LED integrado en la placa
#define LED2 14    // Puedes cambiar estos números por los pines que uses
#define LED3 13

void setup() {
  // Inicializar comunicación serial
  Serial.begin(115200);
  
  // Configurar pines como salidas
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  
  Serial.println("Iniciando secuencia de LEDs...");
}

void loop() {
  // Secuencia 1: LED1 ON, otros OFF
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  Serial.println("LED1 ON, LED2 OFF, LED3 OFF");
  delay(500);
  
  // Secuencia 2: LED2 ON, otros OFF
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  Serial.println("LED1 OFF, LED2 ON, LED3 OFF");
  delay(500);
  
  // Secuencia 3: LED3 ON, otros OFF
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  Serial.println("LED1 OFF, LED2 OFF, LED3 ON");
  delay(500);
  
  // Todos los LEDs ON
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  Serial.println("Todos los LEDs ON");
  delay(500);
  
  // Todos los LEDs OFF
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  Serial.println("Todos los LEDs OFF");
  delay(500);
}