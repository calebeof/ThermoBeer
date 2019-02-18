#include "dados.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


Dados::Dados(){
    LOCATION = "http://thermobeer.herokuapp.com/";
    _UPLOAD = "upload";
    _DOWNLOAD = "download";
    _RELE = "\"RELE\":";
    _STATUS =  "\"STATUS\":";
    _SENSOR = "\"SENSOR\":";
    _CONEXAO = 0;
}

String Dados::JSON_SENSOR(double tempC){
  return "{" + _SENSOR + String(tempC) + "}";
}

String Dados::JSON_RELE(bool estado){
  return "{" + _RELE + estado + "}";
}

String Dados::JSON_STATUS(){
  return "{" + _STATUS + _CONEXAO + "}";
}

void Dados::uploadSENSOR(double tempC){
  _http.begin(LOCATION+_UPLOAD);
  _http.addHeader("Content-Type", "application/json");
  Serial.print(JSON_SENSOR(tempC));
  _http.POST(JSON_SENSOR(tempC));
  _http.end();
} 

void Dados::uploadRELE(bool estado){
  _http.begin(LOCATION+_UPLOAD);
  _http.addHeader("Content-Type", "application/json");
  _http.POST(JSON_RELE(estado));
  _http.end();
}

void Dados::uploadSTATUS(){
  _http.begin(LOCATION+_UPLOAD);
  _http.addHeader("Content-Type", "application/json");
  _http.POST(JSON_STATUS());
  Serial.println(JSON_STATUS());
  _http.end();
}

String Dados::downloadWEB(){
  _http.begin(LOCATION+_DOWNLOAD);
  _http.GET();
  String payload = _http.getString();
  _http.end();
  return payload;
}

bool Dados::verifySTATUS(){
  if(WiFi.status() != WL_CONNECTED)
    return _CONEXAO = false;
  return _CONEXAO = true;  
}

int Dados::updateRELE(String comando){
    if(comando.startsWith("{") and comando.endsWith("}")){
        if(comando.indexOf(_RELE + " 1")>0)
            return 1;
        else if (comando.indexOf(_RELE + " 0")>0)
            return 0;
    }
    return -1;
}
