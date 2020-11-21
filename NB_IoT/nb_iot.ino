#include "ClosedCube_HDC1080.h"
#include "Magellan_SIM7020E.h"

Magellan_SIM7020E magel;          
ClosedCube_HDC1080 hdc1080;

// เซ็นเซอร์แสงต่อที่ขา 24
const int lightSensorPin=34; 
String payload;

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
}

void loop() 
{
  // อ่านค่าอุณหภูมิ แปลงเป็นข้อความ
  String temperature=String(hdc1080.readTemperature());

  // อ่านค่าความชื้น แปลงเป็นข้อความ
  String humidity=String(hdc1080.readHumidity());

  // อ่านค่าแสงสว่าง แปลงเป็นข้อความ
  String Light=String(analogRead(lightSensorPin));

  /* นำอุณหภูมิ (temperature), ความชื้น (humidity), และแสงสว่าง (Light)
   * มาเรียงเป็นสตริง payload ให้อยู่ในรูปแบบ JSON เช่น
   * {"temperature":34.63, "humidity":42.5, "light":85}
   */
  payload="{\"temperature\":"+temperature+",\"humidity\":"+humidity+",\"light\":"+Light+"}";  
  
  // ส่งสตริง payload ไปบันทึกยัง Magellan IoT Platform
  magel.report(payload);

  // แสดงสตริง payload บน Serial
  Serial.println(payload);
  
  // หยุดการทำงาน 5 วินาที ก่อนไปเริ่มบรรทัดแรกของฟังก์ชัน loop
  delay(5000);                                                                                
}