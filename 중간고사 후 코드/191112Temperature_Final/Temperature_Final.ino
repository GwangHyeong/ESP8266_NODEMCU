/*
  도연쓰 바보 ㅇㅅㅇa
*/
#include <SSD1306.h>
#include <DHT.h>
#define DHTPIN D6
#define DHTTYPE DHT11
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);


//WIFI 로그인할 변수 에 값지정
const char * ssid = "SMART324_3";
const char * password = "76543210";
DHT dht(DHTPIN, DHTTYPE);

float temp = dht.readTemperature();

float humidity = dht.readHumidity();


void handleRoot() {
  float temp = dht.readTemperature();
  Serial.print("Temp:");
  Serial.println(temp);
  float humidity = dht.readHumidity();
  Serial.print("Humidity:");
  Serial.println(humidity);
  String temp1 = String(temp);
  String humidity1 = String(humidity);

  String message = "Temperature";
  message += temp1;
  message += "\n Humidity :";
  message += humidity1;
  server.send(200, "text/html", message);

}


//온습도 센서 , 화면 디스플레이 매개변수
SSD1306 display(0x3c, D2, D1);

void setup() {

  Serial.begin(115200); //Serial 통신
  WiFi.mode(WIFI_STA); //Wifi통신 모드
  WiFi.begin(ssid, password); //저장된 아이디랑비밀번호 로 시작
  while (WiFi.status() != WL_CONNECTED) { // 와이파이 연결표시
    delay(500);
    Serial.print(".");
  
  }



  // 와이파이 통신 눈으로 확인할 수 있는 코드
  Serial.println("");
  Serial.print("Connecting to");
  Serial.println(ssid);
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());

  server.begin();

  Serial.println("Server started");

  dht.begin(); //온습도 시작


  // 화면표시
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.display();

  server.on("/", handleRoot);

}

void loop() {


  server.handleClient();
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
 // Serial.print("Humidity:");
 // Serial.print(humidity);
 // Serial.print("Temperature:");
 // Serial.print(temp);
 // Serial.println("ºC");


  display.clear();

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 20, "Temperature:");
  display.drawString(65, 20, String(temp) + String("C"));
  display.drawString(0, 40, "Humidity:");
  display.drawString(55, 40, String(humidity) + String("%"));
  display.display();

}
