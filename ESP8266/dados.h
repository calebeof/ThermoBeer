#ifndef DADOS_H
#define DADOS_H

class Dados{
private:
    String LOCATION, UPLOAD, DOWNLOAD, STATUS, RELE;
    bool CONEXAO; 
public:
    String JSON_SENSOR(double tempC);
    String JSON_RELE(bool estado);
    String JSON_STATUS();
    void uploadSENSOR();
    void uploadRELE();
    void uploadSTATUS();
    int updateRELE(string comando);
    String downloadWEB();
    bool verifySTATUS();
};

#endif // DADOS_H
