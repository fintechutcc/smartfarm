#include "ClosedCube_HDC1080.h"
#include "Magellan_SIM7020E.h"

Magellan_SIM7020E magel;          
ClosedCube_HDC1080 hdc1080;

// เซ็นเซอร์แสงต่อที่ขา 34
const int lightSensorPin=34; 
String payload;

// ขาต่อเพื่อขับรีเลย์ควบคุมปั๊มที่ขา 33
// LED บนบอร์ดอยู่ที่ขา 2
const int pumpPin = 33;
const int ledPin = 2;
String pumpState;
String sw;

void setup() 
{
  Serial.begin(115200);

  Serial.println("ClosedCube HDC1080");

  // เริ่มต้นใช้งานเซ็นเซอร์อุณหภูมิ ความชื้น และแสงสว่าง
  hdc1080.begin(0x40);
  Serial.print("Manufacturer ID=0x");
  Serial.println(hdc1080.readManufacturerId(), HEX); 
  Serial.print("Device ID=0x");
  Serial.println(hdc1080.readDeviceId(), HEX);

  // เริ่มต้นใช้งาน Magellan IoT Platform
  Serial.println("Initialize Magellan IoT API.");
  magel.begin();
  Serial.println("Initialization done!");

  // กำหนดขาที่ใช้ควบคุมรีเลย์เปิด-ปิดปั๊ม
  pinMode(pumpPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() 
{
  // อ่านสถานะของสวิตช์ควบคุมปั๊มจาก Magellan IoT Platform
  pumpState = magel.getControl("pump");
  Serial.println("Pump State:" + pumpState);
  if(pumpState.indexOf("40300") == -1) {
    sw = pumpState;
  }

  // ถ้าสวิตช์มีสถานะเป็น 1 เปิด LED และเปิดปั๊ม
  // มิฉะนั้น ปิด LED และปิดปั๊ม
  if(sw == "1") {
    digitalWrite(ledPin, 1);
    digitalWrite(pumpPin, 1);
  } else {
    digitalWrite(ledPin, 0);
    digitalWrite(pumpPin, 0);
  }

  // อ่านค่าอุณหภูมิ แปลงเป็นข้อความ
  String temperature = String(hdc1080.readTemperature());

  // อ่านค่าความชื้น แปลงเป็นข้อความ
  String humidity = String(hdc1080.readHumidity());

  // อ่านค่าแสงสว่าง แปลงเป็นข้อความ
  String light = String(analogRead(lightSensorPin));

  // อ่านค่าระยะทาง แปลงเป็นข้อความ
  String distance = String(100); // <--- เปลี่ยนโค้ดบรรทัดนี้ให้อ่านค่าจากเซ็นเซอร์

  /* นำอุณหภูมิ (temperature), ความชื้น (humidity), แสงสว่าง (light) และระยะทาง (distance)
   * มาเรียงเป็นสตริง payload ให้อยู่ในรูปแบบ JSON เช่น
   * {"temperature":34.63, "humidity":42.5, "light":85, "distance":25}
   */
  payload = "{\"temperature\":" + temperature
          + ",\"humidity\":" + humidity
          + ",\"light\":" + light
          + ",\"distance\":" + distance
          + "}";  
  
  // ส่งสตริง payload ไปบันทึกยัง Magellan IoT Platform
  magel.report(payload);

  // แสดงสตริง payload บน Serial
  Serial.println(payload);
  
  // หยุดการทำงาน 5 วินาที ก่อนไปเริ่มบรรทัดแรกของฟังก์ชัน loop
  delay(5000);                                                                                
}