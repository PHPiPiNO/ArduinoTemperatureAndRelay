// Based on the example testing sketch for various 
// DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 12     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("System ready!");

  dht.begin();
}

void loop() {
  // Wait one second
  delay(1000);
  
  float celsiusTemp = 0.0;
  float farenheitTemp = 0.0;
  float humidity = 0.0;
  
  if (Serial.available()) {
    byte command = Serial.read();
    switch (command) {
      case 'r': // Read temperature
        readHeatIndex(celsiusTemp, farenheitTemp, humidity);
        Serial.print("H_");
        Serial.print(humidity);
        Serial.print("-CT_");
        Serial.print(celsiusTemp);
        Serial.print("-FT_");
        Serial.println(farenheitTemp);
    }
    while (Serial.available()) {
       byte a = Serial.read();
     }
  }
}

void readHeatIndex(float &ct, float &ft, float &hu) {
  hu = dht.readHumidity();
  ct = dht.readTemperature();
  ft = dht.readTemperature(true);

  if (isnan(hu) || isnan(ct) || isnan(ft)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  ct = dht.computeHeatIndex(ct, hu, false);
  ft = dht.computeHeatIndex(ft, hu, true);

  return;
}

