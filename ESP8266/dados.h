#ifndef DADOS_H
#define DADOS_H

#include "Arduino.h" 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


class Dados{
private:
    String LOCATION, UPLOAD, DOWNLOAD, STATUS, RELE, SENSOR, SSID, PASS;
    bool CONEXAO; 
    HTTPClient http;
public:
    Dados();
    String JSON_SENSOR(double tempC);
    String JSON_RELE(bool estado);
    String JSON_STATUS();
    void uploadSENSOR();
    void uploadRELE();
    void uploadSTATUS();
    int updateRELE(String comando);
    String downloadWEB();
    bool verifySTATUS();
};

#endif // DADOS_H
