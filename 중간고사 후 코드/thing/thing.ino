#include <ESP8266WiFi.h>

//WIFI 로그인할 변수 에 값지정
const char * ssid = "SMART324_3";
const char * password = "76543210";
WiFiClient client;

const char* WriteAPIkey = "RKFLOURXYXEF30YJ";

unsigned long ChannelID = 910446;
const char * host ="184.106.153.149"; //Thingspeal.com
void setup() {
 Serial.begin(115200);
 delay(10);
 Serial.println();
 Serial.println();
 Serial.print("Connecting to");
 Serial.println(ssid);

 WiFi.begin(ssid,password);

 while(WiFi.status() != WL_CONNECTED){

  delay(500);

  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());

}

 int value=20;

 

void loop() {

  delay(12000);

  value+=10;

  if(value>100)value=20;

  Serial.print("connecting to ");

  Serial.println(host);

 

  WiFiClient client;

  const int httpPort =80;

 

  if(!client.connect(host,httpPort)){

    Serial.println("connection failed");

    return;

    }

    String url ="/update?key= RJKEYPTATIQ7Y98J &field1=";

    Serial.print("Requesting URL:");

    Serial.println(url);

 

    Serial.print("value:");

    Serial.println(value);

 

    client.print(String("GET")+url+value+"HTTP/1.1\r\n"+

                  "Host:"+host+"\r\n"+

                  "Connection:close\r\n\r\n");

    unsigned long timeout =millis();

    while(client.available() ==0)

    {

      if(millis()-timeout>5000){

        Serial.println(">>>Client Timeout!");

        client.stop();

        return;

        }

      }

      while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);
        }
        Serial.println();
        Serial.println("closing connection");

}
