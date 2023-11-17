#include <SoftwareSerial.h>
#include <DHT11.h>

// Create an instance of the DHT11 class.
// - For Arduino: Connect the sensor to Digital I/O Pin 2.
// - For ESP32: Connect the sensor to pin GPIO2 or P2.
// - For ESP8266: Connect the sensor to GPIO2 or D4.
DHT11 dht11(2);
SoftwareSerial espSerial(5, 6);

void setup()
{
  espSerial.begin(115200);
}
void loop()
{
  int temperature = dht11.readTemperature();
  int humidity = dht11.readHumidity();
  String str =String(humidity)+String(" ")+String(temperature);
  espSerial.println(str);
  delay(1000);
}