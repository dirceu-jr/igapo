//Authors:Nayana Machado and Marina Ferrarez
//Email: {nayanamachado.02@gmail.com;maferrarezr@gmail.com}
//Date: 29/07/2020
//Revision: LESS DATA + CALIBRAÇÃO UMIDADE E VÁCUO _ delay 60000 1 min#
//Project: {Data logger com sensor de umidade do solo (SOIL) e transdutor de pressão com tensiômetro (DPX5100DP)}

#include <RTClib.h> // RTClib - Version: Latest 
//#include <SDConfig.h> // SDConfig - Version: Latest 
#include <SD.h>
#include <Adafruit_Sensor.h>


//Pino CS do cartao SD
int Pino_CS = 10;

int sensor_pin = A0;  //pino umidade
int output_value ;  //saida umidade


const float SensorOffset = 36.0; // sensor pressão

RTC_DS1307 rtc;
File file;

void setup()
{
  Serial.begin(9600); //speed parameter
  Serial.println("Data logger com sensor de umidade e transdutor de pressão");
  Serial.println();

  //Inicia o cartao SD
  Serial.println("Iniciando cartao SD...");
  if (!SD.begin(Pino_CS))
  {
    Serial.println("Falha na inicializacao do SD!");
    return;
  }
  Serial.println("Cartao SD iniciado. OK");
  Serial.println();

  //Verifica as condicoes do RTC
  if (! rtc.begin())
  {
    Serial.println("RTC nao encontrado!");
    while (1);
  }
  if (! rtc.isrunning())
  {
    Serial.println("RTC nao operante!");
    //A linha abaixo ajusta o RTC com a data e hora do momento da compilacao
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //A linha abaixo permite ajustar manualmente a data e hora do RTC
    //Formato: DateTime(ano, mes, dia, hora, minuto, segundo)
    //rtc.adjust(DateTime(2020, 6, 19, 14, 32, 0));
  }

//  Serial.begin(9600); // umidade
  Serial.println("Iniciando leitura dos sensores de umidade e transdutor de pressão ..."); //umidade e vacuo
  delay(2000); //umidade
}




void loop(void)
{

  delay(2000); 

//  ____________ UMIDADE
 // a função analogRead() mapeia tensões entre 0 e a tensão operacional
  // (5V ou 3.3V) para valores inteiros entre 0 e 1023.
  output_value= analogRead(sensor_pin);

    
  //output_value = map(output_value,580,385,0,100);    
  //Serial.print(" Moisture : ");
  //Serial.print(output_value);
  //Serial.println("");
  delay(1000);

//  _______________PRESSÃO
  // read the input on analog pin 0:
  float sensorValue = (analogRead(A1)-SensorOffset)/10.0; //Do maths for calibration
  // print out the value you read:

  
  delay(1000);      // delay in between reads for stability

  //Le as informacoes do RTC
  DateTime now = rtc.now();
  //Serial monitor informacoes de hora
  Serial.print(now.day() < 10 ? "0" : "");
  Serial.print(now.day(), DEC);
  Serial.print('-');
  Serial.print(now.month() < 10 ? "0" : "");
  Serial.print(now.month(), DEC);
  Serial.print('-');
  Serial.print(now.year() < 10 ? "0" : "");
  Serial.print(now.year(), DEC);
  Serial.print(";");
  Serial.print(now.hour() < 10 ? "0" : "");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute() < 10 ? "0" : "");
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second() < 10 ? "0" : "");
  Serial.print(now.second(), DEC);
  Serial.print(';');
  Serial.print("Umidade:");
  Serial.print(output_value);
  Serial.print("V,Vacuo:");  
  Serial.print(sensorValue,8);
  Serial.println("KPa");

  //Gravacao do cartao
  //Abre arquivo no SD para gravacao
  file = SD.open("solo.csv", FILE_WRITE);
  //Grava os dados no cartao SD
  file.print(now.day() < 10 ? "0" : "");
  file.print(now.day(), DEC);
  file.print('-');
  file.print(now.month() < 10 ? "0" : "");
  file.print(now.month(), DEC);
  file.print('-');
  file.print(now.year() < 10 ? "0" : "");
  file.print(now.year(), DEC);
  file.print(";");
  file.print(now.hour() < 10 ? "0" : "");
  file.print(now.hour(), DEC);
  file.print(':');
  file.print(now.minute() < 10 ? "0" : "");
  file.print(now.minute(), DEC);
  file.print(':');
  file.print(now.second() < 10 ? "0" : "");
  file.print(now.second(), DEC);
  file.print(";");
  file.print("Umidade:");
  file.print(output_value);
  file.print("V,Vacuo:");  
  file.print(sensorValue,8);
  file.println("KPa");
  
  //Fecha arquivo
  file.close();
  //Delay ate a proxima leitura
  //delay(598000); // delay 10 min
  //delay(3598000); // delay de uma hora 
  delay(58000); //delay de um minuto
  //delay(1000); //tempo de delay para ver o programa rodar
  
}
