#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Arduino.h" 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


class Functions{
private:
    String _LOCATION, _UPLOAD, _DOWNLOAD, _STATUS, _RELE, _SENSOR;
    bool _CONEXAO; 
    HTTPClient _http;
public:
    Functions();
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

#endif // FUNCTIONS_H
