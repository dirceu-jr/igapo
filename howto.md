### 1 - Set SimCOM GSM900 Shield to "Software Serial" (through jumpers):
<img src='https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/serial.png' />

### 2 - On the side of the GSM shield you have to use the ports indicated in the image below. On the Arduino or ESP side, you can use other ports. In my case I use ESP32 22 and 23:

<img src='https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/pinout/Wiring-SIM900-GSM-GPRS-Shield-with-Arduino-UNO.png' />

### 3 - You have to install some libraries in the Arduino IDE.

Go to Arduino > Preferences and where it says "Additional URLs for Card Managers" add: "https://dl.espressif.com/dl/package_esp32_index.json" (without quotes).

Go to Tools > Manage Libraries. Search for and install "TinyGSM", "ArduinoHttpClient" and "EspSoftwareSerial".

### 4 - In line 33 of the code you may have to change to the ports you are going to use on your ESP:

https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/tinygsm_to_ubidots.ino#L33

### 5 - In line 69 you have to put the Ubidots token:
https://github.com/dirceup/remote_hydrometeorological_monitoring_system/blob/master/arduino/tinygsm_to_ubidots.ino#L69

### 6 - That's it! In line 159 of the code I am trying to send the temperature value of the LM35. You can change to something fixed or try to use a sensor.