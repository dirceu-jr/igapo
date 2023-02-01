//This code is for the Atlas Scientific wifi pool kit that uses the Adafruit feather huzzah esp8266 as its computer.

#include <iot_cmd.h>
#include <ESP8266WiFi.h>                                         //include esp8266 wifi library 
#include "ThingSpeak.h"                                          //include thingspeak library
#include <Ezo_i2c_util.h>                                        //brings in common print statements
#include <Ezo_i2c.h>                                             //include the EZO I2C library from https://github.com/Atlas-Scientific/Ezo_I2c_lib
#include <Wire.h>                                                //include arduinos i2c library

WiFiClient client;                                               //declare that this device connects to a Wi-Fi network, create a connection to a specified internet IP address

//----------------Fill in your Wi-Fi / ThingSpeak Credentials-------
const String ssid = "DIRCEU 2.4GHz";                             //The name of the Wi-Fi network you are connecting to
const String pass = "PASSWORD";                                 //Your WiFi network password
const long myChannelNumber = 1956479;                            //Your Thingspeak channel number
const char * myWriteAPIKey = "FG0D9R78LUMJ2O7G";                 //Your ThingSpeak Write API Key"
//------------------------------------------------------------------

Ezo_board PH = Ezo_board(99, "PH");           //create a PH circuit object, who's address is 99 and name is "PH"
Ezo_board ORP = Ezo_board(98, "ORP");         //create an ORP circuit object who's address is 98 and name is "ORP"
Ezo_board RTD = Ezo_board(102, "RTD");        //create an RTD circuit object who's address is 102 and name is "RTD"

Ezo_board device_list[] = { //an array of boards used for sending commands to all or specific boards
  PH,
  ORP,
  RTD
};

Ezo_board* default_board = &device_list[0]; //used to store the board were talking to

//gets the length of the array automatically so we dont have to change the number every time we add new boards
const uint8_t device_list_len = sizeof(device_list) / sizeof(device_list[0]);

//enable pins for each circuit
const int EN_PH = 14;
const int EN_ORP = 12;
const int EN_RTD = 15;
// const int EN_AUX = 13;

const unsigned long reading_delay = 1000;                 //how long we wait to receive a response, in milliseconds

float k_val = 0;                                          //holds the k value for determining what to print in the help menu

bool polling = true;                                      //variable to determine whether or not were polling the circuits
bool send_to_thingspeak = true;                           //variable to determine whether or not were sending data to thingspeak

const long SLEEPTIME = 30e6; //30 sec - may be used in deep sleep

//----------

bool wifi_isconnected() {                                 //function to check if wifi is connected
  return (WiFi.status() == WL_CONNECTED);
}

void disconnect_wifi() {
  // TODO:
  // - may not need to disconnect/begin
  // - verify docs for .disconnect
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);
}

void reconnect_wifi() {                                   //function to reconnect wifi if its not connected
  WiFi.forceSleepWake();
  delay(1);

  WiFi.mode(WIFI_STA);                                    //set ESP8266 mode as a station to be connected to wifi network

  WiFi.begin(ssid, pass);
  Serial.println("connecting to wifi");

  const int max_tries = 30;
  int attempts = 0;

  while (!wifi_isconnected() && attempts < max_tries) {   //wait till connect - max 30 secs
    attempts++;
    delay(1000);
  }
}

void thingspeak_send() {
  if (send_to_thingspeak == true) {                                                    //if we're datalogging
    if (wifi_isconnected()) {
      int return_code = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      if (return_code == 200) {                                                          //code for successful transmission
        Serial.println("sent to thingspeak");
      } else {
        Serial.println("couldnt send to thingspeak");
      }
    }
  }
}

//Power consumption
//0.19A with circuits enabled (LOW, LOW, HIGH)
//0.07A with circuits disabled (HIGH, HIGH, LOW)

//enable sensors circuits only at reading time
void enable_circuits() {
  digitalWrite(EN_PH, LOW);                                                       //set enable pins to enable the circuits
  digitalWrite(EN_ORP, LOW);
  digitalWrite(EN_RTD, HIGH);

  Serial.println("circuits ON");

  //Wait 2 secs, till circuits power on
  delay(2000);
}

void disable_circuits() {
  digitalWrite(EN_PH, HIGH);                                                       //set enable pins to disabled the circuits
  digitalWrite(EN_ORP, HIGH);
  digitalWrite(EN_RTD, LOW);

  Serial.println("circuits OFF");
}

void setup() {
  // Obs:
  // - Starting from version 3 of this core, persistence is disabled by default and WiFi does not start automatically at boot
  // - So maybe three lines bellow is not necessary and maybe even harmfull
  WiFi.persistent(false);                 //does not store in flash memory
  WiFi.mode(WIFI_OFF);                    //start with WIFI off;
  WiFi.forceSleepBegin();
  
  delay(1);

  // TODO:
  // - test initialization, may change this to works better with low battery level;
  pinMode(EN_PH, OUTPUT);                                                         //set enable pins as outputs
  pinMode(EN_ORP, OUTPUT);
  pinMode(EN_RTD, OUTPUT);

  //Start disabled
  disable_circuits();

  Wire.begin();                           //start the I2C
  Serial.begin(9600);                     //start the serial communication to the computer

  ThingSpeak.begin(client);               //enable ThingSpeak connection
}

void loop() {
  String cmd;                            //variable to hold commands we send to the kit

  if (receive_command(cmd)) {            //if we sent the kit a command it gets put into the cmd variable
    polling = false;                     //we stop polling
    send_to_thingspeak = false;          //and sending data to thingspeak
    if (!process_coms(cmd)) {            //then we evaluate the cmd for kit specific commands
      process_command(cmd, device_list, device_list_len, default_board);    //then if its not kit specific, pass the cmd to the IOT command processing function
    }
  }
  
  if (polling) {                 //if polling is turned on, run the sequencer
    enable_circuits();

    //!? Will it work with delay()!?
    //looks that YES!

    send_read_cmd_to_RTD();
    delay(reading_delay);

    receive_RTD_and_send_temperature_to_PH();
    delay(300);

    send_read_cms_to_PH_and_ORP();
    delay(reading_delay);

    receive_PH_and_ORP();
    
    disable_circuits();

    if (send_to_thingspeak) {
      reconnect_wifi();
      thingspeak_send();
      disconnect_wifi();
    }
  }

  // sleep for 360 seconds (6 minutes)
  ESP.deepSleep(360e6, WAKE_RF_DISABLED);
}

void send_read_cmd_to_RTD() {
  //send a read command. we use this command instead of RTD.send_cmd("R");
  //to let the library know to parse the reading
  RTD.send_read_cmd();
}

void receive_RTD_and_send_temperature_to_PH() {
  receive_and_print_reading(RTD);             //get the reading from the RTD circuit

  if ((RTD.get_error() == Ezo_board::SUCCESS) && (RTD.get_last_received_reading() > -1000.0)) { //if the temperature reading has been received and it is valid
    PH.send_cmd_with_num("T,", RTD.get_last_received_reading());
    ThingSpeak.setField(3, String(RTD.get_last_received_reading(), 2));                 //assign temperature readings to the third column of thingspeak channel
  } else {                                                                                      //if the temperature reading is invalid
    PH.send_cmd_with_num("T,", 25.0);                                                           //send default temp = 25 deg C to PH sensor
    ThingSpeak.setField(3, String(25.0, 2));                 //assign temperature readings to the third column of thingspeak channel
  }

  Serial.print(" ");
}

void send_read_cms_to_PH_and_ORP() {
  //send a read command. we use this command instead of PH.send_cmd("R");
  //to let the library know to parse the reading
  PH.send_read_cmd();
  ORP.send_read_cmd();
}

void receive_PH_and_ORP() {
  receive_and_print_reading(PH);             //get the reading from the PH circuit
  if (PH.get_error() == Ezo_board::SUCCESS) {                                          //if the PH reading was successful (back in step 1)
    ThingSpeak.setField(1, String(PH.get_last_received_reading(), 2));                 //assign PH readings to the first column of thingspeak channel
  }
  
  Serial.print(" ");
  
  receive_and_print_reading(ORP);             //get the reading from the ORP circuit
  if (ORP.get_error() == Ezo_board::SUCCESS) {                                          //if the ORP reading was successful (back in step 1)
    ThingSpeak.setField(2, String(ORP.get_last_received_reading(), 0));                 //assign ORP readings to the second column of thingspeak channel
  }
  
  Serial.println();
}

bool process_coms(const String &string_buffer) {      //function to process commands that manipulate global variables and are specifc to certain kits
  if (string_buffer == "HELP") {
    print_help();
    return true;
  }
  return false;                         //return false if the command is not in the list, so we can scan the other list or pass it to the circuit
}

void print_help() {
  Serial.println(F("Atlas Scientific I2C pool kit                                              "));
  Serial.println(F("Commands:                                                                  "));
  Serial.println(F("                                                                           "));
  Serial.println(F("ph:cal,mid,7     calibrate to pH 7                                         "));
  Serial.println(F("ph:cal,low,4     calibrate to pH 4                                         "));
  Serial.println(F("ph:cal,high,10   calibrate to pH 10                                        "));
  Serial.println(F("ph:cal,clear     clear calibration                                         "));
  Serial.println(F("                                                                           "));
  Serial.println(F("orp:cal,225          calibrate orp probe to 225mV                          "));
  Serial.println(F("orp:cal,clear        clear calibration                                     "));
  Serial.println(F("                                                                           "));
  Serial.println(F("rtd:cal,t            calibrate the temp probe to any temp value            "));
  Serial.println(F("                     t= the temperature you have chosen                    "));
  Serial.println(F("rtd:cal,clear        clear calibration                                     "));
}
