<img width="1015" height="789" alt="Screenshot 2026-09-12 014726" src="https://github.com/user-attachments/assets/3d85fae5-9ca0-45b1-8292-5053f3a1fe4a" />
<img width="2000" height="1333" alt="อบรม" src="https://github.com/user-attachments/assets/82d51442-8a24-4a75-ac05-e100fc256595" />
# ESP32 Smart Environmental and Energy Monitoring System

ระบบตรวจวัดสภาพแวดล้อมและพลังงานด้วย ESP32  
สำหรับการเรียนรู้และอบรมด้าน Internet of Things (IoT) และ Google Apps Script

---

## 📌 About This Project

โปรเจกต์นี้เป็นตัวอย่างระบบ IoT สำหรับตรวจวัดข้อมูลจากเซนเซอร์หลายชนิด
โดยใช้ ESP32 เป็นอุปกรณ์หลักในการอ่านค่าและประมวลผลข้อมูล

ข้อมูลจากเซนเซอร์จะถูกส่งผ่าน Wi-Fi ไปยัง Google Apps Script
และบันทึกลงใน Google Sheets เพื่อใช้สำหรับจัดเก็บและวิเคราะห์ข้อมูล

โปรเจกต์นี้จัดทำขึ้นเพื่อใช้เป็นสื่อประกอบการอบรม/Workshop
เกี่ยวกับ IoT, ESP32 และ Google Apps Script

---

## 🎯 Learning Objectives

ผู้เรียนจะได้เรียนรู้เกี่ยวกับ

- พื้นฐาน Internet of Things (IoT)
- การใช้งาน ESP32
- การเชื่อมต่อ Sensor กับ ESP32
- การอ่านค่าจาก Sensor
- การเชื่อมต่อ ESP32 เข้ากับ Wi-Fi
- การส่งข้อมูลด้วย HTTP POST
- การสร้าง API ด้วย Google Apps Script
- การรับข้อมูล JSON จาก ESP32
- การบันทึกข้อมูลลง Google Sheets
- การนำข้อมูล IoT ไปต่อยอดเป็นระบบ Monitoring

---

## 🧩 System Overview

ระบบทำงานตามลำดับดังนี้

Sensor
↓
ESP32
↓
Wi-Fi
↓
Google Apps Script
↓
Google Sheets

ESP32 ทำหน้าที่อ่านข้อมูลจาก Sensor และส่งข้อมูลในรูปแบบ JSON
ผ่าน HTTP POST ไปยัง Google Apps Script

Google Apps Script ทำหน้าที่รับข้อมูลและบันทึกลง Google Sheets

---

## 🔧 Hardware

- ESP32 Dev Module
- BH1750 Light Sensor
- DS18B20 Temperature Sensor
- INA219 Voltage/Current Sensor
- Breadboard
- Jumper Wire
- Power Supply

---

## 📡 Sensors

### BH1750

ใช้สำหรับวัดความเข้มแสง

หน่วย:
`Lux (lx)`

### DS18B20

ใช้สำหรับวัดอุณหภูมิ

หน่วย:
`°C`

### INA219

ใช้สำหรับวัด

- Voltage (V)
- Current (mA)
- Power (mW)

---

## 💻 Software

- Arduino IDE
- ESP32 Board Package
- Google Apps Script
- Google Sheets

### Arduino Libraries

```text
Wire
BH1750
OneWire
DallasTemperature
Adafruit INA219
WiFi
HTTPClient
