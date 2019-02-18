#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal.h>

#include "functions.h"

#define D6 12
#define D7 13
const int sensor = D6, rele = D7;

double tempC = 0;
OneWire oneWire(sensor);
DallasTemperature sensors(&oneWire);
HTTPClient http;
Functions functions;
int update;

const char* SSID = "Andressa";
const char* PASS = "12312322";
const String LEVEDURA = "\"LEVEDURA\":";
const String LOWTEMP = "\"LOWTEMP\":";
const String HIGHTEMP = "\"HIGHTEMP\":";

void setup()
{
  Serial.begin(115200);
  pinMode(rele, OUTPUT);
  sensors.begin();
  WiFi.begin(SSID, PASS);
  while(!functions.verifySTATUS())
    delay(500);
  functions.uploadSTATUS();
  delay(2000);
}

void loop(){
  update = functions.updateRELE(functions.downloadWEB());
  //Serial.println(update);
  
  if(update == 1)
   digitalWrite(rele, HIGH);
  else if(update==0)
   digitalWrite(rele, LOW);
   
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  functions.uploadSENSOR(tempC);
  delay(1500);
  functions.uploadRELE(digitalRead(rele));
  functions.uploadSTATUS();
}
