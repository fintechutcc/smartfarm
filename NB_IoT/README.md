# ตัวอย่างโค้ดสำหรับ AIS NB IoT และ Magellan IoT Platform

ตำแหน่งขา (Pins) ต่างๆ ของ NB IoT:

![Preferences00](images/24_IoT.png)

## ขั้นตอนที่ 1 ติดตั้ง ESP32
- คลิกที่เมนู File > Preferences

![Preferences01](images/01_ESP32.jpeg)

- ที่แท็บ Settings ในช่อง Additional Boards Manager URLs ตรวจสอบว่ามีค่าเป็น https://dl.espressif.com/dl/package_esp32_index.json

![Preferences02](images/02_ESP32.jpeg)

- คลิกที่เมนู Tools > Board: ... > Boards Manager ดังรูปด้านล่าง

![Preferences03](images/03_ESP32.jpeg)

- พิมพ์ esp32 ลงในกล่องข้อความดังรูปต่อไปนี้

![Preferences04](images/04_ESP32.jpeg)

- เมื่อติดตั้งเสร็จ เปลี่ยนบอร์ดเป็น ESP32 Dev Model ดังรูปต่อไปนี้

![Preferences05](images/05_ESP32.jpeg)

## ขั้นตอนที่ 2 ติดตั้งไลบรารี Magellan_SIM7020E

- ดาวน์โหลด Magellan_SIM7020E จากลิงค์ต่อไปนี้ https://github.com/AIS-DeviceInnovation/Magellan_SIM7020E แล้วบันทึกไว้ในโฟลเดอร์ Downloads

- ใน Arduino IDE คลิกที่เมนู Sketch > Include Library > Add .ZIP Library ... ดังรูปต่อไปนี้

![Magellan01](images/06_Magellan.jpeg)

- โปรแกรมถามหาไฟล์ Magellan_SIM7020E.zip ให้เลือกดังรูป แล้วคลิก Open

![Magellan02](images/07_Magellan.jpeg)

- คลิกที่เมนู Sketch > Include Library > Manage Libraries ...

![Magellan03](images/08_Magellan.jpeg)

- พิมพ์ข้อความ Magellan_SIM7020 แล้วคลิก Install ดังรูปต่อไปนี้

![Magellan04](images/09_Magellan.jpeg)

## ขั้นตอนที่ 3 ติดตั้งไลบรารี HDC1080

- คลิกที่เมนู Sketch > Include Library > Manage Libraries ...

![Magellan03](images/08_Magellan.jpeg)

- พิมพ์ข้อความ ClosedCube HDC1080 แล้วคลิก Install ดังรูปต่อไปนี้

![HDC01](images/10_HDC.jpeg)

## ขั้นตอนที่ 4 ทดลองโปรแกรม nb_iot.ino 

- ดาวน์โหลดโค้ดต่อไปนี้ เปิดด้วย Arduino IDE แล้วคลิกอัพโหลดขึ้นยังบอร์ด NB IoT พร้อมเปิด Serial Monitor ผลลัพธ์ที่ได้เป็นดังนี้

![SerialMonitor](images/11_Serial_Monitor.png)

## ขั้นตอนที่ 5 ลงทะเบียน Magellan IoT Plantform

- เปิดเว็บ https://magellan.ais.co.th/users/signin แล้วคลิกที่ CONTINUE WITH FACEBOOK ดังรูปต่อไปนี้

![IoT01](images/12_IoT.png)

- ในรูปต่อไปนี้ คลิกที่ "ดำเนินการต่อในชื่อ ..." 

![IoT02](images/13_IoT.png)

- ที่รูปด้านล่าง คลิกที่  Trial Magellan Free 30 Days

![IoT03](images/14_IoT.png)

- ติ๊กถูกที่ I agree terms and conditions แล้วคลิก Accept

![IoT04](images/15_IoT.png)

- คลิกที่ + Register Thing

![IoT05](images/16_IoT.png)

- ป้อนข้อมูลต่อไปนี้
1. Thing Name เช่น NB_ แล้วตามด้วยชื่อ
2. ป้อนค่า ICCID และ IMEI โดยใช้ค่าที่ได้จาก Serial Monitor ในขั้นตอนที่ 4
3. เปลี่ยน Refresh Time จาก None เป็น Refresh ป้อนตัวเลขเป็น 5 แล้วคลิก Register Thing เพื่อลงทะเบียนอุปกรณ์ NB IoT

![IoT06](images/17_IoT.png)

- ผลลัพธ์ของการลงทะเบียนเป็นดังนี้

![IoT07](images/18_IoT.png)

## ขั้นตอนที่ 6 การสร้าง Dashboard

- คลิกที่ Dashboards > + Create Dashboard แล้วตั้งชื่อ Dashboard Name เช่น ห้องของฉัน ดังรูป

![IoT08](images/19_IoT.png)

- คลิกที่ Create Widget แล้วเลือก Temperature จากนั้นคลิก Next

![IoT09](images/20_IoT.png)

- ตั้งชื่อของ Widget ในช่อง Name เป็น "อุณหภูมิ" ส่วน Thing Name ให้เลือกชื่ออุปกรณ์ที่ลงทะเบียนไว้ เช่น NB_Suparerk และเลือกชนิดของเซ็นเซอร์ ในกรณีนี้เลือก temperature แล้วคลิก Next

![IoT10](images/20_IoT.png)

- คลิก Create Widget

![IoT11](images/22_IoT.png)

- โปรดทดลองสร้าง Widget อื่นๆ เพิ่มเติม เช่น ดังรูปต่อไปนี้

![IoT12](images/23_IoT.png)
