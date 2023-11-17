#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Qqqqqqq";
const char* password = "parolatelefon";

String serverName = "http://192.168.190.3:3001/api/sendData";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  // Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
  // Serial.println("");
  // Serial.print("Connected to WiFi network with IP Address: ");
  // Serial.println(WiFi.localIP());
 
  // Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

bool stringComplete=false;
String inputString="";

void loop() {

  
  if(Serial.available()) {
    inputString = Serial.readStringUntil('\n');
    stringComplete=true;
  }

  // Send an HTTP POST request depending on timerDelay and if we read anything
  if (stringComplete && (millis() - lastTime) > timerDelay) {
    Serial.println(inputString);
    int temperature=0;
    int humidity=0;
    int emission=0;

    sscanf(inputString.c_str(), "%d %d %d", &temperature, &humidity,&emission);
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName 
            +String("?temperature=")+String(temperature)
            +String("&humidity=")+String(humidity)
            +String("&emission=")+String(emission);
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
  
      int httpResponseCode = http.GET();

      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
      stringComplete=false;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

