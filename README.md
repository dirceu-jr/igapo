This repository compiles codes, libraries and content for automation in reading hydrometeorological data.

## Actual code

- [Testing HTTP POST To Ubidotsv via GPRS with TinyGSM](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/gprs_to_ubidots.ino)
- [How To](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/howto.md)

## Libraries used

- [TinyGSM](https://github.com/vshymanskyy/TinyGSM)
- [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

## Current hardware

- [DOIT ESP32 DEVKIT V1](https://en.wikipedia.org/wiki/ESP32)
- SIMCom GSM900 based Arduino Shield

## Pinout

- [DOIT ESP32 DEVKIT V1](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/ESP32-DOIT-DEVKIT-V1-Board-Pinout-30-GPIOs-Copy.png)
- [SIMCom GSM900](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/Wiring-SIM900-GSM-GPRS-Shield-with-Arduino-UNO.png)

## Others libraries/options

- [Seeed-Studio/GPRS_SIM900](https://github.com/Seeed-Studio/GPRS_SIM900)

## Other hardware options

- [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/)
- [ESP8266](https://en.wikipedia.org/wiki/ESP8266)
- [Arduino Uno](http://arduino.cc/) - Unable to handle TinyGSM + ArduinoHttpClient libraries in memory

## SaaS options

- [Ubidots](https://ubidots.com/)
- [Thingspeak](https://thingspeak.com/)
- [Adafruit IO](https://io.adafruit.com/)
- [Thinger.io](https://thinger.io/)
- [Thingsboard](https://thingsboard.io/)
- ...

## Dashboard Prototype

- [Dashboard Prototype](https://dirceup.github.io/remote_hydrometeorological_monitoring_system/dashboard/)
