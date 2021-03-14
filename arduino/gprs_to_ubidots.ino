/**************************************************************
 Read Sonar, Humidity, Temperature, send to Ubidots API via GPRS
 **************************************************************/

#define TINY_GSM_MODEM_SIM900

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

#include <SoftwareSerial.h>

// NewPing is for Sonar
#include <NewPing.h>

// DHT for Humidity and Temperature
#include "DHT.h"

// Real Time Clock (no SIM900 tem RTC?)
//#include <RTClib.h>

#define TRIGGER_PIN  18
#define ECHO_PIN     19
#define MAX_DISTANCE 200

// DHT 22  (AM2302), AM2321
#define DHTTYPE DHT22
// Digital pin connected to the DHT sensor
#define DHTPIN 21

// Configure modem:
#define SIM900RX 22
#define SIM900TX 23

// Initialize Sonar
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize Modem on Software Serial on Uno, Nano
SoftwareSerial SerialAT(SIM900RX, SIM900TX); // RX, TX

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Increase RX buffer to capture the entire response
// Chips without internal buffering (A6/A7, ESP8266, M590)
// need enough space in the buffer for the entire response
// else data will be lost (and the http library will fail).
#if !defined(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 650
#endif

// See all AT commands, if wanted
//#define DUMP_AT_COMMANDS

// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon
// #define LOGGING  // <- Logging is for the HTTP library

// Range to attempt to autobaud
//#define GSM_AUTOBAUD_MIN 9600
//#define GSM_AUTOBAUD_MAX 115200

// Add a reception delay - may be needed for a fast processor at a slow baud rate
// #define TINY_GSM_YIELD() { delay(2); }

// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true

// set GSM PIN, if any
#define GSM_PIN ""

// Your GPRS credentials, if any
const char apn[]  = "smart.m2m.vivo.com.br";
const char gprsUser[] = "vivo";
const char gprsPass[] = "vivo";

// Server details
const char server[] = "things.ubidots.com";
const int port = 80;

// esp32-dpj token
String token = "BBFF-N5GFm5topPFrHni6ZmV5MbFCjHd4HO";

#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);
HttpClient http(client, server, port);

String resourceEndpoint(String variable) {
  return "/api/v1.6/variables/" + variable + "/values?token=" + token;
}

String distance_resource = resourceEndpoint("604e887a1d84724ed8571234");
String humidity_resource = resourceEndpoint("600c9c291d84721d35d83171");
String temperature_resource = resourceEndpoint("600c85571d84726aeed92746");

void setup() {
  // Set console baud rate
  SerialMon.begin(9600);
  delay(10);

  dht.begin();

  // !!!!!!!!!!!
  // Set your reset, enable, power pins here
  // !!!!!!!!!!!

  SerialMon.println("Wait...");
  
  // Set GSM module baud rate
  SerialAT.begin(9600);
  delay(6000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN if needed
  if ( GSM_PIN && modem.getSimStatus() != 3 ) {
    modem.simUnlock(GSM_PIN);
  }
}

void loop() {

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isNetworkConnected()) {
    SerialMon.println("Network connected");
  }

  // GPRS connection parameters are usually set after network registration
  SerialMon.print(F("Connecting to "));
  SerialMon.print(apn);
  if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isGprsConnected()) {
    SerialMon.println("GPRS connected");
  }

  // send distance
  sendToUbidots(distance_resource, "distance", sonar.ping_cm());

  // send humitity
  sendToUbidots(humidity_resource, "humidity", dht.readHumidity());

  // send temperature
  sendToUbidots(temperature_resource, "temperature", dht.readTemperature());

  modem.gprsDisconnect();
  SerialMon.println(F("GPRS disconnected"));

  // Do nothing forevermore
  //  while (true) {
  //    delay(1000);
  //  }
  delay(60000);
}

// Use ArduinoHttpClient to send HTTP POST to Ubidots API
void sendToUbidots(String resource, String type, float value) {

  if (isnan(value)) {
    SerialMon.println(F("Failed to read from: "));
    SerialMon.println(type);
    return;
  }
  
  SerialMon.print(F("Performing HTTP POST request... "));
  
  String contentType = "application/json";
  String postData = "{\"value\":" + String(value) + "}";
  
  // int err = http.get(resource);
  int err = http.post(resource, contentType, postData);

  //  http.sendHeader("X-Auth-Token", token);
 
  if (err != 0) {
    SerialMon.println(F("failed to connect"));
    delay(10000);
    return;
  }

  int status = http.responseStatusCode();
  SerialMon.print(F("Response status code: "));
  SerialMon.println(status);
  if (!status) {
    delay(10000);
    return;
  }

  SerialMon.println(F("Response Headers:"));
  while (http.headerAvailable()) {
    String headerName = http.readHeaderName();
    String headerValue = http.readHeaderValue();
    SerialMon.println("    " + headerName + " : " + headerValue);
  }

  int length = http.contentLength();
  if (length >= 0) {
    SerialMon.print(F("Content length is: "));
    SerialMon.println(length);
  }
  if (http.isResponseChunked()) {
    SerialMon.println(F("The response is chunked"));
  }

  String body = http.responseBody();
  SerialMon.println(F("Response:"));
  SerialMon.println(body);

  SerialMon.print(F("Body length is: "));
  SerialMon.println(body.length());

  // Shutdown
  http.stop();
  SerialMon.println(F("Server disconnected"));
}