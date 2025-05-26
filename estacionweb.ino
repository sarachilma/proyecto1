/********************** SECCIÓN DE BIBLIOTECAS **********************/
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <RTClib.h>

/********************** CONFIGURACIÓN WIFI **********************/
const char* ssid = "CISCO";
const char* password = "REDRED30";

/********************** CONFIGURACIÓN SENSOR DHT11 **********************/
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/********************** CONFIGURACIÓN GPS **********************/
#define RXD2 16
#define TXD2 17
TinyGPSPlus gps;
HardwareSerial ss(1);

/********************** CONFIGURACIÓN RTC **********************/
RTC_DS1307 rtc;

/********************** SERVIDOR WEB **********************/
WebServer server(80);

/********************** VARIABLES GLOBALES **********************/
bool systemOn = true;
float temp = 0, hum = 0;
float tempMax = -1000, tempMin = 1000;
float humMax = -1000, humMin = 1000;
double latitude = 0, longitude = 0, altitude = 0;
int satellites = 0;
String dateTime = "";

/********************** FUNCIÓN PARA FORMATO GPS **********************/
String formatGPScoord(double coord, bool isLat) {
  char direction = isLat ? (coord >= 0 ? 'N' : 'S') : (coord >= 0 ? 'E' : 'W');
  coord = fabs(coord);
  int degrees = (int)coord;
  double minutesWithSeconds = (coord - degrees) * 60;
  int minutes = (int)minutesWithSeconds;
  double seconds = (minutesWithSeconds - minutes) * 60;
  char buffer[30];
  snprintf(buffer, sizeof(buffer), "%d°%d'%.2f\" %c", degrees, minutes, seconds, direction);
  return String(buffer);
}

/********************** FUNCIÓN PARA OBTENER DATOS HTML **********************/
String processor(const String& var) {
  if (var == "BTN_TEXT") return systemOn ? "Apagar Sistema" : "Encender Sistema";
  if (var == "TEMP") return String(temp, 1);
  if (var == "HUM") return String(hum, 1);
  if (var == "TEMP_MAX") return String(tempMax, 1);
  if (var == "TEMP_MIN") return String(tempMin, 1);
  if (var == "HUM_MAX") return String(humMax, 1);
  if (var == "HUM_MIN") return String(humMin, 1);
  if (var == "LAT") return formatGPScoord(latitude, true);
  if (var == "LON") return formatGPScoord(longitude, false);
  if (var == "ALT") return String(altitude, 1);
  if (var == "SAT") return String(satellites);
  if (var == "DATETIME") return dateTime;
  if (var == "GPS_STATUS") return satellites >= 4 ? "gps-status gps-status-active" : "gps-status gps-status-inactive";
  int tempLevel = constrain(map(temp, 0, 50, 100, 0), 0, 100);
  return String(tempLevel);
}

/********************** FUNCIÓN DE CONTROL REMOTO **********************/
void toggleSystem() {
  systemOn = !systemOn;
  server.sendHeader("Location", "/");
  server.send(303);
}

/********************** SETUP **********************/
void setup() {
  Serial.begin(115200);
  ss.begin(9600, SERIAL_8N1, RXD2, TXD2);
  dht.begin();
  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning()) rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado: " + WiFi.localIP().toString());

  server.on("/", []() {
    String html = index_html;
    html.replace("%BTN_TEXT%", processor("BTN_TEXT"));
    html.replace("%TEMP%", processor("TEMP"));
    html.replace("%HUM%", processor("HUM"));
    html.replace("%TEMP_MAX%", processor("TEMP_MAX"));
    html.replace("%TEMP_MIN%", processor("TEMP_MIN"));
    html.replace("%HUM_MAX%", processor("HUM_MAX"));
    html.replace("%HUM_MIN%", processor("HUM_MIN"));
    html.replace("%LAT%", processor("LAT"));
    html.replace("%LON%", processor("LON"));
    html.replace("%ALT%", processor("ALT"));
    html.replace("%SAT%", processor("SAT"));
    html.replace("%DATETIME%", processor("DATETIME"));
    html.replace("%GPS_STATUS%", processor("GPS_STATUS"));
    server.send(200, "text/html", html);
  });

  server.on("/toggle", toggleSystem);
  server.begin();
}

/********************** LOOP PRINCIPAL **********************/
void loop() {
  server.handleClient();

  if (!systemOn) return;

  temp = dht.readTemperature();
  hum = dht.readHumidity();

  if (!isnan(temp)) {
    tempMax = max(tempMax, temp);
    tempMin = min(tempMin, temp);
  }

  if (!isnan(hum)) {
    humMax = max(humMax, hum);
    humMin = min(humMin, hum);
  }

  while (ss.available()) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      latitude = gps.location.lat();
      longitude = gps.location.lng();
      altitude = gps.altitude.meters();
      satellites = gps.satellites.value();
    }
  }

  DateTime now = rtc.now();
  char buf[20];
  snprintf(buf, sizeof(buf), "%02d/%02d/%04d %02d:%02d:%02d",
           now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
  dateTime = String(buf);

  delay(2000);
}

/********************** HTML ESTÁTICO **********************/
const char index_html[] PROGMEM = R"rawliteral(
<!-- (tu código HTML completo que enviaste va aquí, reemplazando variables con %NOMBRE%) -->
)rawliteral";
