#include <Wire.h>
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_INA219.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ตั้งค่า Wi-Fi ของคุณ
const char* ssid = "";
const char* password = "";

// วาง URL ที่ได้จากการ Deploy Google Apps Script ตรงนี้
const char* scriptURL = "";

const int oneWireBus = 4;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
BH1750 lightMeter;
Adafruit_INA219 ina219;

unsigned long lastTime = 0;
unsigned long timerDelay = 10000; // ส่งข้อมูลทุกๆ 10 วินาที

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Wire.begin(21, 22);
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  sensors.begin();
  ina219.begin();
  ina219.setCalibration_16V_400mA(); 

  // เชื่อมต่อ Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  // ส่งข้อมูลทุกๆ 10 วินาที
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      // อ่านค่าจากเซนเซอร์ทั้งหมด
      float lux = lightMeter.readLightLevel();
      sensors.requestTemperatures();
      float temp = sensors.getTempCByIndex(0);
      float voltage = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000.0);
      float current = ina219.getCurrent_mA();
      float power = voltage * current;   // เปลี่ยนจาก ina219.getPower_mW()

      Serial.println("---------------");
      Serial.print("Temp: ");
      Serial.println(temp);

      Serial.print("Lux: ");
      Serial.println(lux);

      Serial.print("Voltage: ");
      Serial.println(voltage);

      Serial.print("Current: ");
      Serial.println(current);

      Serial.print("Power: ");
      Serial.println(power);

      // สร้างข้อมูลแบบ JSON
      String jsonPayload = "{";
      jsonPayload += "\"lux\":" + String(lux < 0 ? 0 : lux) + ",";
      jsonPayload += "\"temp\":" + String(temp == DEVICE_DISCONNECTED_C ? 0 : temp) + ",";
      jsonPayload += "\"voltage\":" + String(voltage) + ",";
      jsonPayload += "\"current\":" + String(current) + ",";
      jsonPayload += "\"power\":" + String(power);
      jsonPayload += "}";

      // ส่ง HTTP POST ไปยัง Google Apps Script
      HTTPClient http;
      http.begin(scriptURL);
      http.addHeader("Content-Type", "application/json");

      int httpResponseCode = http.POST(jsonPayload);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
