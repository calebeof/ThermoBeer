#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <DallasTemperature.h>
#include <OneWire.h>
#include <LiquidCrystal.h>

//defini��o da constante ONE_WIRE_BUS, na qual representar� o pino de comunica��o dos dados do sensor
#define RX 8
#define TX 9
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define D9 3
#define D10 1
//const int  D0 = 16, D1 = 5, D2 = 4, D3 = 0, D4 = 2, D5 = 14, D6 = 12, D7 = 13, D8 = 15, D9 = 3;
const int rs = D5, e = D4, d4 = D3, d5 = D2, d6 = D1, d7 = D0, dados = D6, rele = D7;

String data = "", data2 = "Abbaye";
int Limite1 = 0, Limite2 = 0;
double tempC = 0;
bool conexao = false;
OneWire oneWire(dados);
DallasTemperature sensors(&oneWire);
//DeviceAddress sensor1;
LiquidCrystal lcd (rs,e,d4,d5,d6,d7);

const char* SSID = "Andressa";
const char* PASS = "12312322";
const String SENSOR = "\"SENSOR\":";
const String LEVEDURA = "\"LEVEDURA\":";
const String LOWTEMP = "\"LOWTEMP\":";
const String HIGHTEMP = "\"HIGHTEMP\":";
const String STA = "\"STATUS\":";
const String RELE = "\"RELE\":";

HTTPClient http;
const String LOCATION = "http://thermobeer.herokuapp.com/";
const String UPLOAD = "upload";
const String DOWNLOAD = "download";

String JSON_SENSOR(){
  return "{" + SENSOR + String(tempC) + "}";
}

String JSON_RELE(){
  return "{" + RELE + digitalRead(rele) + "}";
}

String JSON_STATUS(){
  return "{" + STA + conexao + "}";
}


void uploadSENSOR(){
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
  //Serial.println(JSON_RELE());
  http.end();
}

void uploadSTATUS(){
  http.begin(LOCATION+UPLOAD);
  http.addHeader("Content-Type", "application/json");
  http.POST(JSON_STATUS());
  //Serial.println(JSON_STATUS());
  http.end();
}

String downloadWEB(){
  http.begin(LOCATION+DOWNLOAD);
  http.GET();
  String payload = http.getString();
  http.end();
  /*Serial.println("INICIO DO PAYLOAD");
  Serial.println(payload);
  Serial.println("FIM DO PAYLOAD");
  */
  return payload;
}

bool verifyStatus(){
  if(WiFi.status() != WL_CONNECTED)
    return false;
  return true;  
}

void atualizarRele(String comando){
  if(comando.startsWith("{") and comando.endsWith("}")){
    if(comando.indexOf(RELE + " 1")>0)
      digitalWrite(rele, HIGH);
    else if(comando.indexOf(RELE + " 0")>0)
      digitalWrite(rele, LOW);
  }
 }

void setup()
{
 Serial.begin(115200);
 pinMode(rele, OUTPUT);
  sensors.begin();
  WiFi.begin(SSID, PASS);
  //sensors.getDeviceCount();
  //sensors.getAddress(sensor1, 0);
  while(!verifyStatus()){
    delay(500);
    //Serial.println("Aguardando conexao...");
  }
  conexao = true;
  //Serial.println(conexao);
  uploadSTATUS();
  lcd.begin(20,4);
  delay(2000);
}

void print_data2(String data2);
void print_lcd(double tempC, int Limite1, int Limite2, String data2);

void loop(){
  conexao = verifyStatus();
  if(Serial.available()>0){
    data2 = Serial.read();
  }
  print_data2(data2);
  print_lcd(tempC, Limite1, Limite2, data2);
  /*Serial.print("Rele: ");
  if(digitalRead(rele)==HIGH)
    Serial.println("Alto");
  else
    Serial.println("Baixo");*/
  atualizarRele(downloadWEB());
  print_lcd(tempC, Limite1, Limite2, data2);
  print_data2(data2);
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  uploadSENSOR();
  delay(1500);
  uploadRELE();
  uploadSTATUS();
}

void print_lcd(double tempC, int Limite1, int Limite2, String data2)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.setCursor(12,0);
  lcd.print(tempC);
  lcd.write(223); //caractere ��� para exibi��o no LCD
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("LOW: ");
  lcd.setCursor(4,1);
  lcd.print(Limite1,1);
  lcd.write(223);
  lcd.print("C");
  lcd.setCursor(10,1);
  lcd.print("HIGH: ");
  lcd.setCursor(15,1);
  lcd.print(Limite2,1);
  lcd.write(223);
  lcd.print("C");
  lcd.setCursor(0, 2);
  lcd.print(data2);
  lcd.setCursor(0, 3);
  if(Limite1>tempC or Limite2<tempC)
    lcd.print("EXCEDENDO OS LIMITES");
  else
    lcd.print("DENTRO DOS LIMITES");
}

void print_data2(String data2){
  if(data2 == "Abbaye"){
      Limite1 = 17;
      Limite2 = 25;
  }else if (data2 == "Belle Saison"){
      Limite1 = 15;
      Limite2 = 35;
  }else if(data2 == "BRY-97"){
      Limite1 = 15;
      Limite2 = 22;
  }else if(data2 == "Diamond"){
      Limite1 = 10;
      Limite2 = 15;
  }else if (data2 == "Munich"){
      Limite1 = 17;
      Limite2 = 22;
  }else if (data2 == "Nottingham"){
      Limite1 = 10;
      Limite2 = 22;
  }else if(data2 == "Windsor"){
      Limite1 = 15;
      Limite2 = 22;
  }
}
