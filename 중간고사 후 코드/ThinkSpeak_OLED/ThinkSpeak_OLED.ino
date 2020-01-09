#include <ESP8266WiFi.h>
#include <SSD1306.h>
#include <DHT.h>
#define PIN_DHT D6
#define DHTTYPE DHT11
String apiKey = "YD7ZUY0Z6HPD137Q";
const char * ssid = "SMART324_3";
const char * password = "76543210";
const char * host = "184.106.153.149";


DHT dht(PIN_DHT, DHTTYPE);
WiFiServer server(80);
WiFiClient client;

const int analogInPin = A0;

int sensorValue = 0;
int outputValue = 0;

//온습도 센서 , 화면 디스플레이 매개변수
SSD1306 display(0x3c, D2, D1);

void setup() {
    // 화면표시
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.display();
  Serial.begin(115200);
  delay(10);
  pinMode(PIN_DHT,INPUT);
  dht.begin();
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}
float value;
float hvalue;


  
void loop() {
  delay(10000);

  value = dht.readTemperature();
  String tt = (String)value;
  hvalue = dht.readHumidity();
  sensorValue = analogRead(analogInPin);
  String vvalue = (String)sensorValue;
  //OLED  
  display.clear();

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, "Temperature:");
  display.drawString(65, 10, String(value) + String("C"));
  display.drawString(0, 25, "Humidity:");
  display.drawString(55, 25, String(hvalue) + String("%"));
  display.drawString(0, 40, "Potentiometer:");
  display.drawString(70, 40, String(vvalue) + String(""));
  display.display();
  



 Serial.print("Temperature : ");
 Serial.println(tt);

 Serial.print("connecting to ");
 Serial.println(host);
 const int httpPort = 80;  

 if(client.connect(host,80)){
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr += "&field1=";
  getStr += String(value);
  getStr += "&field2=";
  getStr += String(hvalue);
  getStr += "&field3=";
  getStr += (vvalue);
  getStr += "\r\n\r\n";
   client.print(getStr + " HTTP/1.1\r\n" +
 "Host: " + host + "\r\n" +
 "Connection: close\r\n\r\n");

  Serial.print("Temp_A: ");
  Serial.print(value);
  Serial.print(" C ");
  Serial.print(" Humidity_A: ");
  Serial.print(hvalue);
  Serial.print(" % ");
  Serial.print(" Reeistor_A: ");
  Serial.print(vvalue);
  Serial.print(" send to Thingspeak");
 }
  unsigned long timeout = millis();
 while (client.available() == 0)
 {
 if (millis() - timeout > 5000)
 {
 Serial.println(">>> Client Timeout !");
 client.stop();
 return;
 }
 }
}
