This repository compiles codes, libraries and content for automation in reading hydrometeorological data.

## Actual code

- [Testing HTTP POST To Ubidots with TinyGSM](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/tinygsm_to_ubidots.ino)

## Libraries used

- [TinyGSM](https://github.com/vshymanskyy/TinyGSM)
- [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

## Others libraries/options

- [Seeed-Studio/GPRS_SIM900](https://github.com/Seeed-Studio/GPRS_SIM900)

## Current hardware

[DOIT ESP32 DEVKIT V1](https://en.wikipedia.org/wiki/ESP32)

## Other hardware options

- [Arduino Uno](http://arduino.cc/) - Unable to handle TinyGSM + ArduinoHttpClient libraries in memory
- [ESP8266](https://en.wikipedia.org/wiki/ESP8266)/[ESP32](https://en.wikipedia.org/wiki/ESP32)
- [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/)

## SaaS options

[Thingspeak](https://thingspeak.com/), [Ubidots](https://ubidots.com/), [Adafruit IO](https://io.adafruit.com/), [Thinger.io](https://thinger.io/), [Thingsboard](https://thingsboard.io/)...

## Dashboard Prototype

[Dashboard Prototype](https://dirceup.github.io/remote_hydrometeorological_monitoring_system/dashboard/)