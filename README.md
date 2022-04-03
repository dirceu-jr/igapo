This repository compiles codes, libraries and content for ambient water quality monitoring.

## Current Hardware

- [Atlas Scientific Wi-Fi Pool Kit](https://atlas-scientific.com/kits/wi-fi-pool-kit/) (Legacy, with ESP8266)

<a target="_blank" href="https://atlas-scientific.com/kits/wi-fi-pool-kit/"><img width="260" src="https://github.com/dirceu-jr/ambient-water-quality/blob/master/readme_files/wi-fi-pk01.jpeg"></a>

- [LILYGO® TTGO T-BAT Battery Holder](https://pt.aliexpress.com/item/4001156737871.html)

<a target="_blank" href="https://pt.aliexpress.com/item/4001156737871.html"><img width="260" src="https://github.com/dirceu-jr/ambient-water-quality/blob/master/readme_files/lilygo-ttgo-t-bat.webp"></a>

## Software

- [Firmware](https://github.com/dirceu-jr/ambient-water-quality/blob/master/firmware/legacy_pool_kit.ino)
- [Dashboard Prototype](https://dirceu-jr.github.io/ambient-water-quality/dashboard/)
- [Thingspeak Channel](https://thingspeak.com/channels/1643222/) (Cloud and on-premise)

## Other Options

### Embedded Software

- [HTTP POST To Ubidots via GPRS with TinyGSM](https://github.com/dirceu-jr/ambient-water-quality/blob/master/firmware/gprs_to_ubidots.ino)
- [How To](https://github.com/dirceu-jr/ambient-water-quality/blob/master/howto.md)

### Other Hardware Options

- [DOIT ESP32 DEVKIT V1](https://en.wikipedia.org/wiki/ESP32)
- [Raspberry Pi Pico](https://www.raspberrypi.org/products/raspberry-pi-pico/)
- SIMCom GSM900 based Arduino Shield

### Libraries That Could Be Used

- [TinyGSM](https://github.com/vshymanskyy/TinyGSM)
- [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)

### Pinout

- [DOIT ESP32 DEVKIT V1](https://github.com/dirceu-jr/ambient-water-quality/blob/master/pinout/ESP32-DOIT-DEVKIT-V1-Board-Pinout-30-GPIOs-Copy.png)
- [SIMCom GSM900](https://github.com/dirceu-jr/ambient-water-quality/blob/master/pinout/Wiring-SIM900-GSM-GPRS-Shield-with-Arduino-UNO.png)

[Arduino Uno](http://arduino.cc/) was unable to handle TinyGSM + ArduinoHttpClient libraries in memory

### Other Software Options

- [Ubidots](https://ubidots.com/) (Cloud only, free for Educational or Personal purposes, cloud functions not included in free plan);
- [Thingspeak](https://thingspeak.com/) (Cloud and on-premise)
- [Adafruit IO](https://io.adafruit.com/) (Cloud only)
- [Thinger.io](https://thinger.io/) (Cloud and on-premise)
- [Thingsboard](https://thingsboard.io/) (Cloud and on-premise)
- ...
