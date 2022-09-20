//For security purposes set the netwirk address and password
#include "arduino_secrets.h"
//including DHT library
#include "DHT.h"

//set the pin for dht sensor
#define DHTPIN 9

#define DHTTYPE DHT11

//intialising the object of dht class and taking input through constructor
DHT dht(DHTPIN, DHTTYPE);

#include "thingProperties.h"

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  dht.begin();
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(13, OUTPUT); //setting the pin 13 as output
}

void loop() {
  ArduinoCloud.update();
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  onLedChange();
}

/*
  Since Led is READ_WRITE variable, onLedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLedChange()  {
  digitalWrite(13, led);  //digital writing pin13 according to the variable led
}
