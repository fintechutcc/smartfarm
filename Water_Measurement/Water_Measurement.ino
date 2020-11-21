#include <Wire.h>
#include <VL53L0X.h>
#include <ESP8266WiFi.h>

#define SDA_PIN 4
#define SCL_PIN 5

const char* ssid     = "UTCC_CPE_LAB";
const char* password = "iyd9kmujl6f";

VL53L0X sensor;
WiFiServer server(80);

void setup() 
{
   Serial.begin(115200);
   Serial.println("Starting...");
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);       
      Serial.print(".");
   }
   
   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  server.begin();
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.setMeasurementTimingBudget(20000);
}

void loop()
{
  float  Level =sensor.readRangeSingleMillimeters();
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && blank_line) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head></head><body><h1>ระดับน้ำ</h1><h3>");
          client.println(Level);
          client.println("</h3><h3>");
          client.println("</body></html>");
          break;
        }
      }
    }
  }
}
