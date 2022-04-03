This repository compiles codes, libraries and content for automation in reading hydrometeorological data.

## Current Hardware

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (Legacy, with ESP8266)
- [LILYGO® TTGO T-BAT Battery Holder](https://pt.aliexpress.com/item/4001156737871.html)

## Software

- [Thingspeak](https://thingspeak.com/channels/1643222/) (Cloud and on-premise)

## Dashboard Prototype

- [Dashboard Prototype](https://dirceu-jr.github.io/remote_hydrometeorological_monitoring_system/dashboard/)

## Other Options

### Embedded Software

- [HTTP POST To Ubidots via GPRS with TinyGSM](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/gprs_to_ubidots.ino)
- [How To](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/howto.md)

### Other Hardware Options

- [DOIT ESP32 DEVKIT V1](https://en.wikipedia.org/wiki/ESP32)
- [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/)
- SIMCom GSM900 based Arduino Shield

### Libraries That Could Be Used

- [TinyGSM](https://github.com/vshymanskyy/TinyGSM)
- [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

### Pinout

- [DOIT ESP32 DEVKIT V1](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/ESP32-DOIT-DEVKIT-V1-Board-Pinout-30-GPIOs-Copy.png)
- [SIMCom GSM900](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/Wiring-SIM900-GSM-GPRS-Shield-with-Arduino-UNO.png)

[Arduino Uno](http://arduino.cc/) was unable to handle TinyGSM + ArduinoHttpClient libraries in memory

### Other Software Options

- [Ubidots](https://ubidots.com/) (Cloud only, free for Educational or Personal purposes, cloud functions not included in free plan);
- [Thingspeak](https://thingspeak.com/) (Cloud and on-premise)
- [Adafruit IO](https://io.adafruit.com/) (Cloud only)
- [Thinger.io](https://thinger.io/) (Cloud and on-premise)
- [Thingsboard](https://thingsboard.io/) (Cloud and on-premise)
- ...
