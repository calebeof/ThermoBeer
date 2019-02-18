#ifndef DADOS_H
#define DADOS_H

#include "Arduino.h" 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


class Dados{
private:
    String LOCATION, _UPLOAD, _DOWNLOAD, _STATUS, _RELE, _SENSOR;
    bool _CONEXAO; 
    HTTPClient _http;
public:
    Dados();
    String JSON_SENSOR(double tempC);
    String JSON_RELE(bool estado);
    String JSON_STATUS();
    void uploadSENSOR(double tempC);
    void uploadRELE(bool estado);
    void uploadSTATUS();
    int updateRELE(String comando);
    String downloadWEB();
    bool verifySTATUS();
};

#endif // DADOS_H
