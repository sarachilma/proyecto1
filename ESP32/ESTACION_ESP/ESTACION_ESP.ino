#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <RTClib.h>

// -------- CONFIGURACIÓN WiFi --------
const char* ssid = "iPhone";
const char* password = "8865316@";

// Configuración DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Configuración GPS
#define RXD2 16
#define TXD2 17
TinyGPSPlus gps;
HardwareSerial ss(1);

// Configuración RTC
RTC_DS1307 rtc;

// Servidor Web
WebServer server(80);

// Variables globales
bool systemOn = true;
float temp = 0, hum = 0;
float tempMax = -1000, tempMin = 1000;
float humMax = -1000, humMin = 1000;
double latitude = 0, longitude = 0, altitude = 0;
int satellites = 0;
String dateTime = "";

// Función para convertir grados decimales a grados, minutos, segundos y dirección
String formatGPScoord(double coord, bool isLat) {
  char direction;
  if (isLat) {
    direction = coord >= 0 ? 'N' : 'S';
  } else {
    direction = coord >= 0 ? 'E' : 'W';
  }
  
  coord = fabs(coord);
  int degrees = (int)coord;
  double minutesWithSeconds = (coord - degrees) * 60;
  int minutes = (int)minutesWithSeconds;
  double seconds = (minutesWithSeconds - minutes) * 60;
  
  char buffer[30];
  snprintf(buffer, sizeof(buffer), "%d°%d'%.2f\" %c", degrees, minutes, seconds, direction);
  return String(buffer);
}

// HTML con gráficos perfectamente alineados
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Estación Meteorológica ESP32</title>
  <style>
    :root {
      --color-primary: #3498db;
      --color-danger: #e74c3c;
      --color-success: #2ecc71;
      --color-warning: #f39c12;
    }
    html { 
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      text-align: center; 
      background-color: #f8f9fa;
    }
    h2 { 
      color: #2c3e50; 
      margin: 20px 0 30px;
      font-size: 1.8rem;
    }
    .dashboard {
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
      gap: 25px;
      max-width: 1200px;
      margin: 0 auto;
      padding: 0 20px;
    }
    .card {
      background: white;
      border-radius: 12px;
      padding: 20px;
      box-shadow: 0 6px 12px rgba(0,0,0,0.08);
      width: 320px;
      box-sizing: border-box;
    }
    .thermo-wrapper {
      display: flex;
      justify-content: center;
      margin: 15px 0;
      gap: 10px;
    }
    .thermo-container {
      width: 65px;
      height: 260px; /* Altura del termómetro */
      background: linear-gradient(to top, #0000ff, #00ffff, #00ff00, #ffff00, #ff0000);
      border-radius: 35px;
      border: 3px solid #ddd;
      position: relative;
      overflow: hidden;
    }
    .thermo-mask {
      position: absolute;
      bottom: 0;
      width: 100%;
      background: rgba(50, 50, 50, 0.4);
      transition: height 0.8s ease-out;
    }
    .thermo-scale {
      display: flex;
      flex-direction: column;
      justify-content: space-between;
      height: 260px;
      font-size: 0.85rem;
      color: #555;
      padding-left: 5px;
    }
    .gps-map {
      width: 220px;
      height: 220px;
      margin: 15px auto;
      background: #ebf5fb;
      border: 2px solid #aed6f1;
      border-radius: 8px;
      position: relative;
      overflow: hidden;
    }
    .gps-marker {
      width: 12px;
      height: 12px;
      background: var(--color-danger);
      border-radius: 50%;
      position: absolute;
      transform: translate(-50%, -50%);
      border: 2px solid white;
      box-shadow: 0 0 0 2px var(--color-danger);
    }
    .clock-container {
      width: 180px;
      height: 180px;
      margin: 15px auto;
      position: relative;
    }
    .clock-face {
      width: 100%;
      height: 100%;
      border: 8px solid #2c3e50;
      border-radius: 50%;
      position: relative;
      background: white;
    }
    .clock-hand {
      position: absolute;
      left: 50%;
      bottom: 50%;
      transform-origin: 50% 100%;
      transform: translateX(-50%);
    }
    .hour-hand {
      width: 5px;
      height: 50px;
      background: #2c3e50;
      z-index: 1;
    }
    .minute-hand {
      width: 3px;
      height: 70px;
      background: #2c3e50;
      z-index: 2;
    }
    .second-hand {
      width: 2px;
      height: 80px;
      background: #e74c3c;
      z-index: 3;
    }
    .clock-center {
      width: 12px;
      height: 12px;
      background: #2c3e50;
      border-radius: 50%;
      position: absolute;
      top: 50%;
      left: 50%;
      transform: translate(-50%, -50%);
      z-index: 4;
    }
    .card-title {
      font-size: 1.3rem;
      font-weight: 600;
      color: #2c3e50;
      margin-bottom: 10px;
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 8px;
    }
    .card-value {
      font-size: 1.8rem;
      font-weight: 700;
      color: #2c3e50;
      margin: 5px 0;
    }
    .card-unit {
      font-size: 1.2rem;
      color: #7f8c8d;
      margin-left: 3px;
    }
    .minmax {
      font-size: 0.95rem;
      color: #555;
      margin-top: 8px;
    }
    .power-btn {
      display: block;
      width: 200px;
      margin: 0 auto 25px;
      padding: 12px 0;
      font-size: 1.1rem;
      font-weight: 600;
      border: none;
      border-radius: 8px;
      cursor: pointer;
      transition: all 0.3s;
      background-color: var(--btn-color);
      color: #000;
      box-shadow: 0 4px 8px rgba(0,0,0,0.1);
    }
    .power-btn:hover {
      transform: translateY(-2px);
      box-shadow: 0 6px 12px rgba(0,0,0,0.15);
    }
    .power-btn:active {
      transform: translateY(0);
    }
  </style>
</head>
<body>
  <button class="power-btn" id="powerButton" onclick="toggleSystem()">%BTN_TEXT%</button>
  <h2>Estación Meteorológica ESP32</h2>
  
  <div class="dashboard">
    <!-- Tarjeta Temperatura -->
    <div class="card">
      <div class="card-title">🌡 Temperatura</div>
      <div class="thermo-wrapper">
        <div class="thermo-container">
          <div class="thermo-mask" id="temp-mask" style="height:100%"></div>
        </div>
        <div class="thermo-scale">
          <div>50°C</div>
          <div>40°C</div>
          <div>30°C</div>
          <div>20°C</div>
          <div>10°C</div>
          <div>0°C</div>
        </div>
      </div>
      <div class="card-value"><span id="temp">--</span><span class="card-unit">°C</span></div>
      <div class="minmax">Máx: <span id="temp-max">--</span>°C | Mín: <span id="temp-min">--</span>°C</div>
    </div>

    <!-- Tarjeta Humedad -->
    <div class="card">
      <div class="card-title">💧 Humedad Relativa</div>
      <div class="thermo-wrapper">
        <div class="thermo-container">
          <div class="thermo-mask" id="hum-mask" style="height:100%"></div>
        </div>
        <div class="thermo-scale">
          <div>100%</div>
          <div>80%</div>
          <div>60%</div>
          <div>40%</div>
          <div>20%</div>
          <div>0%</div>
        </div>
      </div>
      <div class="card-value"><span id="hum">--</span><span class="card-unit">%</span></div>
      <div class="minmax">Máx: <span id="hum-max">--</span>% | Mín: <span id="hum-min">--</span>%</div>
    </div>

    <!-- Tarjeta GPS -->
    <div class="card">
      <div class="card-title">📍 Posición GPS</div>
      <div class="gps-map">
        <div class="gps-marker" id="gps-marker"></div>
      </div>
      <div style="margin-top: 15px;">
        <div>Latitud: <span id="lat">--°--'--"--</span></div>
        <div>Longitud: <span id="lon">--°--'--"--</span></div>
        <div>Altitud: <span id="alt">---</span> m</div>
        <div>Satélites: <span id="sats">--</span></div>
      </div>
    </div>

    <!-- Tarjeta RTC -->
    <div class="card">
      <div class="card-title">⏰ Reloj y Fecha</div>
      <div class="clock-container">
        <div class="clock-face">
          <div class="clock-hand hour-hand" id="hour-hand"></div>
          <div class="clock-hand minute-hand" id="minute-hand"></div>
          <div class="clock-hand second-hand" id="second-hand"></div>
          <div class="clock-center"></div>
        </div>
      </div>
      <div class="card-value"><span id="rtc-time">--:--:--</span></div>
      <div>Fecha: <span id="rtc-date">--/--/----</span></div>
    </div>
  </div>

<script>
// Variables de estado
let systemOn = %SYSTEM_STATUS%;

// Funciones (usando sintaxis moderna const + arrow)
const updateClock = (hours, minutes, seconds) => {
  const hourHand = document.getElementById('hour-hand');
  const minuteHand = document.getElementById('minute-hand');
  const secondHand = document.getElementById('second-hand');
  
  hourHand.style.transform = `translateX(-50%) rotate(${(hours % 12) * 30 + minutes * 0.5}deg)`;
  minuteHand.style.transform = `translateX(-50%) rotate(${minutes * 6}deg)`;
  secondHand.style.transform = `translateX(-50%) rotate(${seconds * 6}deg)`;
};

const toggleSystem = () => {
  fetch('/control?action=' + (systemOn ? 'off' : 'on'))
    .then(() => location.reload());
};

const decimalToDMS = (coord, isLat) => {
  let direction = isLat ? (coord >= 0 ? 'N' : 'S') : (coord >= 0 ? 'E' : 'W');
  coord = Math.abs(coord);
  const degrees = Math.floor(coord);
  const minutes = Math.floor((coord - degrees) * 60);
  const seconds = (((coord - degrees) * 60 - minutes) * 60).toFixed(2);
  return `${degrees}°${minutes}'${seconds}" ${direction}`;
};

const updateData = () => {
  if (!systemOn) return;
  
  fetch('/data')
    .then(response => response.json())
    .then(data => {
      // Actualizar termómetros
      document.getElementById('temp').textContent = data.temp.toFixed(1);
      document.getElementById('temp-max').textContent = data.tempMax.toFixed(1);
      document.getElementById('temp-min').textContent = data.tempMin.toFixed(1);
      document.getElementById('hum').textContent = data.hum.toFixed(1);
      document.getElementById('hum-max').textContent = data.humMax.toFixed(1);
      document.getElementById('hum-min').textContent = data.humMin.toFixed(1);
      
      // Ajustar máscaras
      document.getElementById('temp-mask').style.height = `${100 - (data.temp * 2)}%`;
      document.getElementById('hum-mask').style.height = `${100 - (data.hum * 0.01 * 100)}%`;

      // Actualizar GPS (formato DMS)
      document.getElementById('lat').textContent = decimalToDMS(data.lat, true);
      document.getElementById('lon').textContent = decimalToDMS(data.lon, false);
      document.getElementById('alt').textContent = data.alt.toFixed(0);
      document.getElementById('sats').textContent = data.sats;
      
      // Posicionar marcador
      const marker = document.getElementById('gps-marker');
      const latPos = 50 - ((data.lat - %INITIAL_LAT%) * 1000);
      const lonPos = 50 + ((data.lon - %INITIAL_LON%) * 1000);
      marker.style.top = `${Math.min(Math.max(latPos, 5), 95)}%`;
      marker.style.left = `${Math.min(Math.max(lonPos, 5), 95)}%`;

      // Actualizar RTC
      const [date, time] = data.datetime.split(' ');
      const [hours, minutes, seconds] = time.split(':');
      document.getElementById('rtc-time').textContent = time;
      document.getElementById('rtc-date').textContent = date;
      updateClock(parseInt(hours), parseInt(minutes), parseInt(seconds));
    });
};

// Iniciar actualización
setInterval(updateData, 1000);
window.onload = updateData;
</script>
</body>
</html>
)rawliteral";

String getHTML() {
  String html = index_html;
  html.replace("%BTN_TEXT%", systemOn ? "🔴 APAGAR SISTEMA" : "🟢 ENCENDER SISTEMA");
  html.replace("%SYSTEM_STATUS%", systemOn ? "true" : "false");
  html.replace("%INITIAL_LAT%", String(latitude, 6));
  html.replace("%INITIAL_LON%", String(longitude, 6));
  return html;
}

void readSensors() {
  if (!systemOn) return;

  // Leer DHT11
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  if (!isnan(temp) && !isnan(hum)) {
    if (temp > tempMax) tempMax = temp;
    if (temp < tempMin) tempMin = temp;
    if (hum > humMax) humMax = hum;
    if (hum < humMin) humMin = hum;
  }

  // Leer GPS
  bool newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (ss.available()) {
      if (gps.encode(ss.read())) {
        if (gps.location.isValid()) {
          latitude = gps.location.lat();
          longitude = gps.location.lng();
          altitude = gps.altitude.meters();
          satellites = gps.satellites.value();
          newData = true;
        }
      }
    }
  }

  // Leer RTC
  DateTime now = rtc.now();
  dateTime = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " +
             String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Inicializar sensores
  dht.begin();
  ss.begin(9600, SERIAL_8N1, RXD2, TXD2);
  if (!rtc.begin()) Serial.println("Error: RTC no encontrado");

  // Conectar WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado. IP: " + WiFi.localIP().toString());

  // Configurar rutas
  server.on("/", HTTP_GET, []() { server.send(200, "text/html", getHTML()); });
  server.on("/data", HTTP_GET, []() {
    readSensors();
    String json = "{";
    json += "\"temp\":" + String(temp, 1) + ",";
    json += "\"tempMax\":" + String(tempMax, 1) + ",";
    json += "\"tempMin\":" + String(tempMin, 1) + ",";
    json += "\"hum\":" + String(hum, 1) + ",";
    json += "\"humMax\":" + String(humMax, 1) + ",";
    json += "\"humMin\":" + String(humMin, 1) + ",";
    json += "\"lat\":" + String(latitude, 6) + ",";
    json += "\"lon\":" + String(longitude, 6) + ",";
    json += "\"alt\":" + String(altitude, 1) + ",";
    json += "\"sats\":" + String(satellites) + ",";
    json += "\"datetime\":\"" + dateTime + "\"";
    json += "}";
    server.send(200, "application/json", json);
  });
  server.on("/control", HTTP_GET, []() {
    systemOn = (server.arg("action") == "on");
    server.send(200, "text/plain", "OK");
  });
  server.begin();
}

void loop() {
  server.handleClient();
  delay(100);
}