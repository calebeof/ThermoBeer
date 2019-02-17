#include "dados.h"

Dados::Dados(){
    LOCATION = "http://thermobeer.herokuapp.com/";
    UPLOAD = "upload";
    DOWNLOAD = "download";
    RELE = "\"RELE\":";
    STATUS =  "\"STATUS\":";
}

String Dados::JSON_SENSOR(double tempC){
  return "{" + SENSOR + String(tempC) + "}";
}

String Dados::JSON_RELE(bool estado){
  return "{" + RELE + estado + "}";
}

String Dados::JSON_STATUS(){
  return "{" + STATUS + CONEXAO + "}";
}

void Dados::uploadSENSOR(){
  http.begin(LOCATION+UPLOAD);
  http.addHeader("Content-Type", "application/json");
  http.POST(JSON_SENSOR());
  Serial.print(JSON_SENSOR());
  http.end();
} 

void uploadRELE(){
  http.begin(LOCATION+UPLOAD);
  http.addHeader("Content-Type", "application/json");
  http.POST(JSON_RELE());
  http.end();
}

void Dados::uploadSTATUS(){
  http.begin(LOCATION+UPLOAD);
  http.addHeader("Content-Type", "application/json");
  http.POST(JSON_STATUS());
  http.end();
}

String Dados::downloadWEB(){
  http.begin(LOCATION+DOWNLOAD);
  http.GET();
  String payload = http.getString();
  http.end();
  return payload;
}

bool Dados::verifySTATUS(){
  if(WiFi.status() != WL_CONNECTED)
    return CONEXAO = false;
  return CONEXAO = true;  
}

int Dados::updateRELE(String comando){
    if(comando.startsWith("{") and comando.endsWith("}")){
        if(comando.indexOf(RELE + " 1")>0)
            return 1;
        else if (comando.indexOf(RELE + " 0")>0)
            return 0;
    }
    return -1;
}
