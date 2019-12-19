#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

//
const char* ssid = "SMART324_3";
const char* password = "76543210";

ESP8266WebServer server(80);

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
  
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

  server.on("/",handleRoot);
  server.begin();
  Serial.println("http start");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
