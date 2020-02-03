#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif
#include <ESP8266HTTPClient.h> 
#include "configuration.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const int chipId = system_get_chip_id();
bool feedExists = false;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Chip id ");
  Serial.println(chipId);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop() {
  createFeed(chipId); 
  
  int avalue = analogRead(A0);
  Serial.println(avalue);
  
  HTTPClient http;
  String apiUrl = "https://io.adafruit.com/api/v2/";
  http.begin(apiUrl + IO_USERNAME + "/feeds/" + chipId + "/data",  IO_FINGERPRINT);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-AIO-Key", IO_KEY);
  String startValue = "{\"value\":";
  int httpCode = http.POST(startValue + avalue + "}");
  http.writeToStream(&Serial);
  http.end();
  
  Serial.print("Response status: ");
  Serial.println(httpCode);
  
  //the RTC speed varies with temperature - so to be sure make room for errors
  ESP.deepSleep(0.9 * ESP.deepSleepMax());
  delay(100);
}

void createFeed(int chipId){
  if(ESP.rtcUserMemoryRead(0, (uint32_t*) &feedExists, sizeof(feedExists))) {
    Serial.println("Read: ");
    Serial.println(feedExists);
    if((bool)feedExists == true){
      Serial.println("Feed exists, returning");
      return;
    }
  }
  HTTPClient http;
  String apiUrl = "https://io.adafruit.com/api/v2/";
  http.begin(apiUrl + IO_USERNAME + "/feeds/",  IO_FINGERPRINT);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-AIO-Key", IO_KEY);
  String startValue = "{ \"feed\": {\"name\":";
  int httpCode = http.POST(startValue + chipId + "} }");
  http.writeToStream(&Serial);
  http.end();
  Serial.print("Response status: ");
  Serial.println(httpCode);
  feedExists = true;
  if(ESP.rtcUserMemoryWrite(0, (uint32_t*) &feedExists, sizeof(feedExists)))
  {
    Serial.println("Feed exists, saved for later");
  }
  else{
    Serial.println("Could not store feed exists.");
  }
}
