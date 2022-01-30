This repository compiles codes, libraries and content for automation in reading hydrometeorological data.

## Embedded Software

- [HTTP POST To Ubidots via GPRS with TinyGSM](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/gprs_to_ubidots.ino)
- [How To](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/howto.md)

## Libraries Used

- [TinyGSM](https://github.com/vshymanskyy/TinyGSM)
- [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

## Current Hardware

- [DOIT ESP32 DEVKIT V1](https://en.wikipedia.org/wiki/ESP32)
- SIMCom GSM900 based Arduino Shield
- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/)

## Pinout

- [DOIT ESP32 DEVKIT V1](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/ESP32-DOIT-DEVKIT-V1-Board-Pinout-30-GPIOs-Copy.png)
- [SIMCom GSM900](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/Wiring-SIM900-GSM-GPRS-Shield-with-Arduino-UNO.png)

## Other Hardware Options

- [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/)
- [ESP8266](https://en.wikipedia.org/wiki/ESP8266)

[Arduino Uno](http://arduino.cc/) was unable to handle TinyGSM + ArduinoHttpClient libraries in memory

## Software Options

- [Ubidots](https://ubidots.com/) (Cloud only, free for Educational or Personal purposes, cloud functions not included in free plan);
- [Thingspeak](https://thingspeak.com/) (Cloud and on-premise)
- [Adafruit IO](https://io.adafruit.com/) (Cloud only)
- [Thinger.io](https://thinger.io/) (Cloud and on-premise)
- [Thingsboard](https://thingsboard.io/) (Cloud and on-premise)
- ...

## Dashboard Prototype

- [Dashboard Prototype](https://dirceup.github.io/remote_hydrometeorological_monitoring_system/dashboard/)
