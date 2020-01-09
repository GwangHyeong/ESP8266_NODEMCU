//웹에서 입력한 값으로 LED 켜기
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>
<body>
<h2>Dept of Smartmedia</h2>
<h3>HTML Form ESP8266</h3>
<form action="/action_page">
Device name:<br>
<input type="text" name="device" value="LED"><br>
Control data:<br>
<input type="text" name="number" value="On/Off number"><br>
<input type="submit" name="Submit"><br>
</body>
</html>
)=====";
const char * ssid = "SMART324_3";
const char * password = "76543210";
ESP8266WebServer server(80);

int ledPin=D0;
void handleRoot(){
  String s=MAIN_page;
  server.send(200, "text/html",s);
}
void handleForm(){
  String device = server.arg("device");
  String number = server.arg("number");
  Serial.print("Debice:");
  Serial.println(device);
  Serial.print("Number:");
  Serial.println(number);

  int num = number.toInt();

  Serial.print("num:");
  Serial.println(number);

  for(int i =0; i<num; i++)
  {
    digitalWrite(ledPin,LOW);
    delay(500);
    digitalWrite(ledPin,HIGH);
    delay(500);
    }

    String s ="<a href='/'>Go Back</a>";
    server.send(200,"text/html",s);
    }

  void setup(void){
    Serial.begin(115200);
    pinMode(ledPin,OUTPUT);
    digitalWrite(ledPin,HIGH);

    WiFi.begin(ssid,password);
    Serial.println("");

    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }

  Serial.println("");
  Serial.println("connected to");
  Serial.println("WiFi");
  Serial.println("IP address:");
  Serial.print(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/action_page", handleForm);
  server.begin();
  Serial.println("HTTP server started");
  }

  void loop(void) {
  server.handleClient();
  }
