
// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPLWzMJtgDD"
#define BLYNK_DEVICE_NAME "HomeWheather"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include "DHT.h"
#include "BlynkEdgent.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void sendSensor(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();  
    
    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    Blynk.virtualWrite(V0, "Sensor(s) are not Connected!");
    return;
  }else{
      Blynk.virtualWrite(V1, h);
      Blynk.virtualWrite(V2, t);

      Serial.print("Temp: ");
      Serial.println(t);

      Serial.print("Humidity: ");
      Serial.println(h);
      Blynk.virtualWrite(V0, "Everything seems okay!");
  }
}
void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  dht.begin();
}

void loop() {
  BlynkEdgent.run();
  sendSensor();
  delay(1000);
}
