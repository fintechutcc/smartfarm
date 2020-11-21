#include <Wire.h>
#include <VL53L0X.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <time.h>

#define MQTT_SERVER   "smartfarm.utcc-fintech.com"
#define MQTT_PORT     1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_NAME     ""
#define WIFI_STA_NAME "TA_2.4G"
#define WIFI_STA_PASS "Wearefamily."

#define SQL1 "insert into water_level values (null,"
#define SQL2 ","
#define SQL3 ",null)"

#define SDA_PIN 4
#define SCL_PIN 5
#define SID 99

VL53L0X sensor;

WiFiClient client;
PubSubClient mqtt(client);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}

void setup() 
{
   Serial.begin(115200);
   Serial.println("Starting...");
   WiFi.mode(WIFI_STA); 
   WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);       
      Serial.print(".");
   }
   
   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
   
   mqtt.setServer(MQTT_SERVER, MQTT_PORT);
   mqtt.setCallback(callback);
   
   Wire.begin();
   sensor.init();
   sensor.setTimeout(500);
   sensor.setMeasurementTimingBudget(20000);

   srand(time(0));
}

void loop()
{
  //float level = sensor.readRangeSingleMillimeters();
  float level = randomLevel(80, 40);
  if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print("\n Publish message: ");
    char sql[256];
    snprintf(sql, sizeof sql, "%s%d%s%f%s", SQL1, SID, SQL2, level, SQL3);
    if (mqtt.publish(sql, "Suphanburi") == true) { 
      Serial.print("Success sending: ");
      Serial.println(sql);
    } else {
      Serial.println("Fail sending");
    }
  }

  //
  delay(300000); 
}

int randomLevel(int max, int min) {
  return (rand() % (max - min + 1)) + min; 
}
