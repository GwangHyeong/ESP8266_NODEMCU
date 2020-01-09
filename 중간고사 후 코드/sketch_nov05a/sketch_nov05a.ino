#include <ESP8266WiFi.h>

#include <ESP8266WebServer.h>

#include "1.h"
#include "2.h"
#include "3.h"


const char * ssid = "SMART324_3";
const char * password = "76543210";


ESP8266WebServer server(80);

int ledPin = D0; 

void handleMain(){

  String s = pageMain;

  server.send(200,"text/html", s);

  }

void handleSecondPage(){

  String s = pageSecond;

  server.send(200,"text/html", s);

  }

void handleForm(){
  String device = server.arg("device");
  String number = server.arg("number");

  Serial.print("Device:");
  Serial.println(device);

  Serial.print("Number:");
  Serial.println(number);

  int num = number.toInt();

  Serial.print("num:");
  Serial.println(number);

  for(int i = 0; i<num; i++)
  {
    digitalWrite(ledPin,LOW);
    delay(500);
    digitalWrite(ledPin,HIGH);
    delay(500);
  }
  String s = "<a href='/'> Go Back </a>";
  server.send(200,"text/html", s);
}


void setup() {

  Serial.begin(115200);

  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
 
  while(WiFi.status() != WL_CONNECTED){

    delay(500);
    Serial.print(".");
    }

   Serial.println("");
   Serial.print("Connecting to");
   Serial.println(ssid);

   Serial.print("IP address:");
   Serial.println(WiFi.localIP());

   server.on("/",handleSecondPage);
   server.on("/action_page",handleForm);

   server.begin();

   Serial.println("Server started");

}

 

void loop() {

  server.handleClient();

}
