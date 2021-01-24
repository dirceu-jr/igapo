This repository compiles codes, libraries and content for automation in reading hydrometeorological data.

Connect GSM Shield with Arduino as in bellow image:

<img src="https://dirceup.github.io/remote_hydrometeorological_monitoring_system/Wiring-SIM900-GSM-GPRS-Shield-with-Arduino-UNO.png" />

Set Shield to Software Serial:

<img src="https://dirceup.github.io/remote_hydrometeorological_monitoring_system/serial.png" />

## Actual code

- [Testing HTTP To Ubidots with TinyGSM](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/tinygsm_to_ubidots.ino)
- [Testing SMS without library](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/testing_sms.ino)
- [Testing SMS with GSM/GRPS library](https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/GSM_GPRSLibrary_SMS.ino)

## Arduino libraries options

- [TinyGSM](https://github.com/vshymanskyy/TinyGSM)
- [GSM/GPRS & GPS Shield Library for modules using SIM900](https://github.com/MarcoMartines/GSM-GPRS-GPS-Shield)
- [Seeed-Studio/GPRS_SIM900](https://github.com/Seeed-Studio/GPRS_SIM900)
- [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

## Base hardware options

- [Arduino Uno](http://arduino.cc/)
- [ESP8266](https://en.wikipedia.org/wiki/ESP8266)/[ESP32](https://en.wikipedia.org/wiki/ESP32)
- [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/)

## SaaS options

[Thingspeak](https://thingspeak.com/), [Ubidots](https://ubidots.com/), [Adafruit IO](https://io.adafruit.com/), [Thinger.io](https://thinger.io/), [Thingsboard](https://thingsboard.io/)...

## Dashboard Prototype

[Dashboard Prototype](https://dirceup.github.io/remote_hydrometeorological_monitoring_system/dashboard/)
