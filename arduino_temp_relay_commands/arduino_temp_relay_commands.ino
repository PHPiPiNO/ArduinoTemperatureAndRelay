// Based on the example testing sketch for various 
// DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 12     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11

#define RELAY 9 // Digital pin connected to the relay

DHT dht(DHTPIN, DHTTYPE);

float celsiusTemp = 0.0;
float celsiusTempIndex = 0.0;
float farenheitTemp = 0.0;
float farenheitTempIndex = 0.0;
float humidity = 0.0;

int relayStatus = LOW;

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH); //Turn off relay
  
  Serial.begin(9600);
  Serial.println("System ready!");

  dht.begin();
}

void loop() {
  // Wait one second
  delay(1000);
  
  if (Serial.available()) {
    byte command = Serial.read();
    switch (command) {
      case 'r': // Read temperature
        readHeatValues();
        Serial.print("H_");
        Serial.print(humidity);
        Serial.print("-CT_");
        Serial.print(celsiusTemp);
        Serial.print("-CTI_");
        Serial.print(celsiusTempIndex);
        Serial.print("-FT_");
        Serial.print(farenheitTemp);
        Serial.print("-FTI_");
        Serial.println(farenheitTempIndex);
        break;
      case 'o':
        digitalWrite(RELAY, LOW); //Turn on relay
        relayStatus = LOW;
        Serial.println("On");
        break;
      case 's':
        digitalWrite(RELAY, HIGH); //Turn off relay
        relayStatus = HIGH;
        Serial.println("Stop");
        break;
      case 'i':
        if(relayStatus == HIGH) {
          Serial.println("Relay is on");
        } else {
          Serial.println("Relay is off");
        }
        break;

    }
    // Empty serial buffer
    while (Serial.available()) {
       byte a = Serial.read();
     }
  }
}

void readHeatValues() {
  humidity = dht.readHumidity();
  
  celsiusTemp = dht.readTemperature();
  celsiusTempIndex = dht.computeHeatIndex(celsiusTemp, humidity, false);
  
  farenheitTemp = dht.readTemperature(true);
  farenheitTempIndex = dht.computeHeatIndex(farenheitTemp, humidity, true);

  if (isnan(humidity) || isnan(celsiusTemp) || isnan(farenheitTemp)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  return;
}

