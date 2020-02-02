# Read me
Source code for an ESP8266 soil moisture sensor, with an adafruit.io backend.
After each reading, the sensor goes to deep sleep for the maximum allowed time (about 3 hours). That way it can run off batteries for a longer time.

## Configuration.h
You need to add a header file for the WiFi and Adafruit.IO settings, like this:

```
#define WIFI_SSID "Your Wifi";
#define WIFI_PASSWORD "Your Wifi pass";

#define IO_USERNAME  "adafruit io username"
#define IO_KEY       "adafruit io key"
#define IO_FINGERPRINT "certificate fingerprint"
```

That's it, and install the latest ESP8266 board to the Arduino manager!

## Some helpful links
The adafruit io api docs:
https://io.adafruit.com/api/docs

The Arduino wiki: https://github.com/arduino/Arduino/wiki/_pages

