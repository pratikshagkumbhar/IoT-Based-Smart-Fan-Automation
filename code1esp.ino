#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// ---- Tumche values ----
const char* WIFI_NAME = "Galaxy";
const char* WIFI_PASS = "Pratikshaa";
const char* URL = "https://smart-fan-ced42-default-rtdb.asia-southeast1.firebasedatabase.app/devices/fan1.json";

// ---- Pins ----
#define IN1 18
#define IN2 19
#define ENA 21

int failCount = 0;

void setupPWM() {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(ENA, 1000, 8);
#else
  ledcSetup(0, 1000, 8);
  ledcAttachPin(ENA, 0);
#endif
}

void writeSpeed(int v) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(ENA, v);
#else
  ledcWrite(0, v);
#endif
}

void motor(int power, int speed) {
  if (power == 1) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    writeSpeed(constrain(speed, 0, 255));
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    writeSpeed(0);
  }
}

int getVal(const String& s, const char* key) {
  int i = s.indexOf(String("\"") + key + "\":");
  if (i < 0) return -1;
  return s.substring(i + strlen(key) + 3).toInt();
}

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  setupPWM();
  motor(0, 0);

  WiFi.begin(WIFI_NAME, WIFI_PASS);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
    http.setTimeout(4000);
    if (http.begin(client, URL)) {
      int code = http.GET();
      if (code == 200) {
        String body = http.getString();
        int power = getVal(body, "power");
        int speed = getVal(body, "speed");
        if (power >= 0 && speed >= 0) {
          motor(power, speed);
          Serial.printf("power=%d speed=%d\n", power, speed);
          failCount = 0;
        }
      } else {
        failCount++;
        Serial.printf("HTTP error %d\n", code);
      }
      http.end();
    }
  } else {
    failCount++;
    WiFi.reconnect();
  }

  if (failCount >= 10) {
    motor(0, 0);
  }
  delay(1000);
}