/**************************************************************
 *
 * This sketch connects to a website and downloads a page.
 * It can be used to perform HTTP/RESTful API calls.
 *
 * For this example, you need to install ArduinoHttpClient library:
 *   https://github.com/arduino-libraries/ArduinoHttpClient
 *   or from http://librarymanager/all#ArduinoHttpClient
 *
 * TinyGSM Getting Started guide:
 *   https://tiny.cc/tinygsm-readme
 *
 * For more HTTP API examples, see ArduinoHttpClient library
 *
 * NOTE: This example may NOT work with the XBee because the
 * HttpClient library does not empty to serial buffer fast enough
 * and the buffer overflow causes the HttpClient library to stall.
 * Boards with faster processors may work, 8MHz boards will not.
 **************************************************************/

// Select modem:
#define TINY_GSM_MODEM_SIM900

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
//#define SerialAT Serial1

// or Software Serial on Uno, Nano
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(7, 8); // RX, TX

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
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200

// Add a reception delay - may be needed for a fast processor at a slow baud rate
// #define TINY_GSM_YIELD() { delay(2); }

// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true

// set GSM PIN, if any
#define GSM_PIN ""

// Your GPRS credentials, if any
const char apn[]  = "zap.vivo.com.br";
const char gprsUser[] = "vivo";
const char gprsPass[] = "vivo";

// Server details
const char server[] = "things.ubidots.com";
String id_variable_1 = "600c9c291d84721d35d83171";
String resource = "/api/v1.6/variables/" + id_variable_1 + "/values";
const char token[] = "BBFF-KGOwoOzmHto5vDktpBP1ch9luEByik";
const int  port = 80;

#include <TinyGsmClient.h>
//#include <ArduinoHttpClient.h>

#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);
//HttpClient http(client, server, port);

void setup() {
  // Set console baud rate
  SerialMon.begin(9600);
  delay(10);

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

  SerialMon.print(F("Performing HTTP GET request... "));
  String contentType = "application/json";
  int value = 1.0;
  String postData = "{\"value\":"+ String(value) + "}";
  
  // int err = http.get(resource);
//  int err = http.post(resource, contentType, postData);
 
//  if (err != 0) {
//    SerialMon.println(F("failed to connect"));
//    delay(10000);
//    return;
//  }

//  int status = http.responseStatusCode();
  SerialMon.print(F("Response status code: "));
//  SerialMon.println(status);
//  if (!status) {
//    delay(10000);
//    return;
//  }

  SerialMon.println(F("Response Headers:"));
//  while (http.headerAvailable()) {
//    String headerName = http.readHeaderName();
//    String headerValue = http.readHeaderValue();
//    SerialMon.println("    " + headerName + " : " + headerValue);
//  }

//  int length = http.contentLength();
//  if (length >= 0) {
//    SerialMon.print(F("Content length is: "));
//    SerialMon.println(length);
//  }
//  if (http.isResponseChunked()) {
//    SerialMon.println(F("The response is chunked"));
//  }

//  String body = http.responseBody();
//  SerialMon.println(F("Response:"));
//  SerialMon.println(body);
//
//  SerialMon.print(F("Body length is: "));
//  SerialMon.println(body.length());
//
//  // Shutdown
//
//  http.stop();
  SerialMon.println(F("Server disconnected"));

  modem.gprsDisconnect();
  SerialMon.println(F("GPRS disconnected"));

  // Do nothing forevermore
  while (true) {
    delay(1000);
  }
}