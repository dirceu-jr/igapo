#include "utilities.h"

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Increase RX buffer to capture the entire response
// Chips without internal buffering (A6/A7, ESP8266, M590)
// need enough space in the buffer for the entire response
// else data will be lost (and the http library will fail).
// #define TINY_GSM_RX_BUFFER 1024

// See all AT commands, if wanted
// #define DUMP_AT_COMMANDS

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon
// #define LOGGING  // <- Logging is for the HTTP library

#include "esp_wifi.h"
#include "esp_bt.h"

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>
#include <Ezo_i2c.h>
// #include <Ezo_i2c_util.h>

// Your GPRS credentials, if any
const char apn[] = "iot.datatem.com.br";
const char gprsUser[] = "datatem";
const char gprsPass[] = "datatem";

// Server details
const char server[] = "api.thingspeak.com";
const int port = 443;

const char* writeAPIKey = "FG0D9R78LUMJ2O7G";

Ezo_board PH = Ezo_board(99, "PH");
Ezo_board ORP = Ezo_board(98, "ORP");
Ezo_board RTD = Ezo_board(102, "RTD");

// enable pins for each circuit
const int EN_PH = 2;
const int EN_ORP = 32;
const int EN_RTD = 33;

// how long we wait to receive a response, in milliseconds
const unsigned long reading_delay = 1000;

struct SensorData {
  float ph;
  float orp;
  float temperature;
};

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm        modem(debugger);
#else
TinyGsm        modem(SerialAT);
#endif

TinyGsmClientSecure client(modem);
HttpClient          http(client, server, port);

// #define LED_PIN     12

void modemPowerOn() {
  pinMode(BOARD_PWRKEY_PIN, OUTPUT);
  digitalWrite(BOARD_PWRKEY_PIN, HIGH);
  delay(100);
  digitalWrite(BOARD_PWRKEY_PIN, LOW);
  delay(MODEM_POWERON_PULSE_WIDTH_MS);
  digitalWrite(BOARD_PWRKEY_PIN, HIGH);
}

// enable sensors circuits only at reading time
// Power consumption
// 0.19A with circuits enabled (LOW, LOW, HIGH)
// 0.07A with circuits disabled (HIGH, HIGH, LOW)
void enableCircuits() {
  digitalWrite(EN_PH, LOW);
  digitalWrite(EN_ORP, LOW);
  digitalWrite(EN_RTD, HIGH);

  SerialMon.println("Circuits ON");

  // wait 2 secs, till circuits power on
  delay(2000);
}

void disableCircuits() {
  digitalWrite(EN_PH, HIGH);
  digitalWrite(EN_ORP, HIGH);
  digitalWrite(EN_RTD, LOW);

  SerialMon.println("Circuits OFF");
}

void holdCircuitsGpio() {
  SerialMon.println("Holding GPIO states for deep sleep");
  gpio_hold_en((gpio_num_t)EN_PH);
  gpio_hold_en((gpio_num_t)EN_ORP);
  gpio_hold_en((gpio_num_t)EN_RTD);
  gpio_deep_sleep_hold_en();
}

void releaseCircuitsGpio() {
  SerialMon.println("Releasing GPIO states from deep sleep");
  gpio_hold_dis((gpio_num_t)EN_PH);
  gpio_hold_dis((gpio_num_t)EN_ORP);
  gpio_hold_dis((gpio_num_t)EN_RTD);
  gpio_deep_sleep_hold_dis();
}

bool connectAndSendData(SensorData readings) {
  SerialMon.print("Signal quality: ");
  SerialMon.println(modem.getSignalQuality());

  SerialMon.print("Waiting for network");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    return false;
  }
  SerialMon.println(" success");

  if (modem.isNetworkConnected()) {
    SerialMon.println("Network connected");
  }

  // GPRS connection parameters are usually set after network registration
  if (modem.isGprsConnected()) {
    SerialMon.println("GPRS already connected");
  } else {
    SerialMon.print(F("Connecting to "));
    SerialMon.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      SerialMon.println(" fail");
      return false;
    }
    SerialMon.println(" success");
  }

  http.setTimeout(30000);
  http.connectionKeepAlive(); // this may be needed for HTTPS

  // Construct the resource URL
  String resource = String("/update?api_key=") + writeAPIKey + "&field1=" + String(readings.ph) + "&field2=" + String(readings.orp) + "&field3=" + String(readings.temperature);

  SerialMon.print(F("Performing HTTPS GET request"));
  int err = http.get(resource);
  if (err != 0) {
    SerialMon.print(F("failed to connect, error: "));
    SerialMon.println(err);
    return false;
  }

  int status = http.responseStatusCode();
  SerialMon.print(F("Response status code: "));
  SerialMon.println(status);
  if (status <= 0) {
    return false;
  }

  String body = http.responseBody();
  SerialMon.println(F("Response:"));
  SerialMon.println(body);

  return true;
}

void disconnectAndPowerModemOff() {
  // Disconnect
  http.stop();
  SerialMon.println(F("Server disconnected"));

  modem.gprsDisconnect();
  SerialMon.println(F("GPRS disconnected"));

  // Power down the modem using AT command
  SerialMon.println(F("Powering down modem"));
  modem.poweroff();
}

float receive_RTD_and_send_temperature_to_PH() {
  // get the reading from the RTD circuit
  // receive_and_print_reading(RTD);
  RTD.receive_read_cmd();

  // if the temperature reading has been received and it is valid
  if ((RTD.get_error() == Ezo_board::SUCCESS) && (RTD.get_last_received_reading() > -1000.0)) {
    PH.send_cmd_with_num("T,", RTD.get_last_received_reading());
    return RTD.get_last_received_reading();
  } else {
    // if the temperature reading is invalid
    // send default temp = 25 deg C to PH sensor
    PH.send_cmd_with_num("T,", 25.0);
    return 25.0;
  }
}

float receive_PH() {
  // get the reading from the PH circuit
  // receive_and_print_reading(PH);
  PH.receive_read_cmd();

  if (PH.get_error() == Ezo_board::SUCCESS) {
    return PH.get_last_received_reading();
  }
}

float receive_ORP() {
  // get the reading from the ORP circuit
  // receive_and_print_reading(ORP);
  ORP.receive_read_cmd();

  if (ORP.get_error() == Ezo_board::SUCCESS) {
    return ORP.get_last_received_reading();
  }
}

SensorData getSensorReadings() {
  SensorData data;

  enableCircuits();

  // step1
  RTD.send_read_cmd();
  delay(reading_delay);

  // step2
  data.temperature = receive_RTD_and_send_temperature_to_PH();
  delay(300);

  // step3
  // send a read command. we use this command instead of PH.send_cmd("R");
  // to let the library know to parse the reading
  PH.send_read_cmd();
  ORP.send_read_cmd();
  delay(reading_delay);

  // step4
  data.ph = receive_PH();
  data.orp = receive_ORP();

  disableCircuits();

  return data;
}

void setup() {
  // Disable Wi-Fi and Bluetooth
  esp_wifi_stop();
  esp_bt_controller_disable();

  // release GPIOs from deep sleep hold, in case they were held
  releaseCircuitsGpio();

  // set enable pins as outputs
  pinMode(EN_PH, OUTPUT);
  pinMode(EN_ORP, OUTPUT);
  pinMode(EN_RTD, OUTPUT);

  disableCircuits();

  // Set LED OFF
  // pinMode(LED_PIN, OUTPUT);
  // digitalWrite(LED_PIN, HIGH);

  // start the I2C
  Wire.begin();

  // Set console baud rate
  SerialMon.begin(115200);
  delay(1000);

  SerialMon.println("Hello A7670SA!");

  /* Set Power control pin output
  * * @note      Known issues, ESP32 (V1.2) version of T-A7670, T-A7608,
  *            when using battery power supply mode, BOARD_POWERON_PIN (IO12) must be set to high level after esp32 starts, otherwise a reset will occur.
  * */
  pinMode(BOARD_POWERON_PIN, OUTPUT);
  digitalWrite(BOARD_POWERON_PIN, HIGH);

  // Set modem reset
  pinMode(MODEM_RESET_PIN, OUTPUT);
  digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);

  // Pull down DTR to ensure the modem is not in sleep state
  pinMode(MODEM_DTR_PIN, OUTPUT);
  digitalWrite(MODEM_DTR_PIN, LOW);

  // Turn on modem
  SerialMon.println(F("Powering modem on..."));
  modemPowerOn();
  delay(3000);

  // Set GSM module baud rate
  SerialAT.begin(MODEM_BAUDRATE, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);
  delay(6000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  // SerialMon.println("Restarting modem...");
  // modem.restart();
  SerialMon.println("Initializing modem...");
  modem.init();

  // Disable GPS
  modem.disableGPS();

  delay(200);

  // print modem info
  String name = modem.getModemName();
  SerialMon.println("Modem Name: " + name);

  String modemInfo = modem.getModemInfo();
  SerialMon.println("Modem Info: " + modemInfo);

  // Check SIM status
  SerialMon.print("SIM Status: ");
  SerialMon.println(modem.getSimStatus());

  String res;
  // 2 Automatic
  // 13 GSM only
  // 38 LTE only
  // 51 GSM and LTE only
  res = modem.setNetworkMode(2);
  SerialMon.print("setNetworkMode: ");
  SerialMon.println(res);
}

void loop() {
  SensorData readings = getSensorReadings();

  bool success = connectAndSendData(readings);

  disconnectAndPowerModemOff();
  holdCircuitsGpio();

  if (success) {
    SerialMon.println("Entering deep sleep for success...");
    // sleep for 10 minutes
    ESP.deepSleep(600e6);
  } else {
    SerialMon.println("Entering deep sleep for error...");
    // sleep for 1 minute
    ESP.deepSleep(60e6);
  }
}
