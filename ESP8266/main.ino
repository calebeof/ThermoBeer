#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal.h>

#include "Dados.h"

#define D6 12
#define D7 13
const int sensor = D6, rele = D7;

double tempC = 0
OneWire oneWire(sensor);
DallasTemperature sensors(&oneWire);
HTTPClient http;
Dados dados;

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
  while(!dados.verifySTATUS())
    delay(500);
  uploadSTATUS();
  lcd.begin(20,4);
  delay(2000);
}

void loop(){
  if(Serial.available()>0)
    data2 = Serial.read();
  dados.updateRELE(dados.downloadWEB());
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  dados.uploadSENSOR();
  delay(1500);
  dados.uploadRELE();
  dados.uploadSTATUS();
}
