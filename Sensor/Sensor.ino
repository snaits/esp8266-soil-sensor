#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif
#include <ESP8266HTTPClient.h> 
#include "configuration.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  int avalue = analogRead(A0);
  Serial.println(avalue);
  HTTPClient http;
  String apiUrl = "https://io.adafruit.com/api/v2/";
  http.begin(apiUrl + IO_USERNAME + "/feeds/" + IO_FEED_KEY + "/data",  "77 00 54 2d da e7 d8 03 27 31 23 99 eb 27 db cb a5 4c 57 18");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-AIO-Key", IO_KEY);
  String startValue = "{\"value\":";
  int httpCode = http.POST(startValue + avalue + "}");
  http.writeToStream(&Serial);
  http.end();
  String responseStatus = "Response status: ";
  Serial.println(responseStatus + httpCode);
  Serial.println("closing connection");
  ESP.deepSleep(ESP.deepSleepMax());
}
