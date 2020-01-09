#include <ESP8266WiFi.h>
const char* ssid = "Smart3242";
const char* password = "Smart3242";
const char* host = "184.106.153.149"; //ThingSpeal.com
void setup()
{
 Serial.begin(115200);
 delay(10);
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
int value = 20;
void loop()
{
 delay(12000);
 value+=10;
 if(value>100)value=20;
 Serial.print("connecting to ");
 Serial.println(host);
 // Use WiFiClient class to create TCP connections
 WiFiClient client;
 const int httpPort = 80;
 if (!client.connect(host, httpPort))
 {
 Serial.println("connection failed");
 return;
 }
 String url = "/update?key=API_KEY&field1=";
 Serial.print("Requesting URL: ");
 Serial.println(url);
 
 Serial.print("value: ");
 Serial.println(value);
 // This will send the request to the server
 client.print(String("GET ") + url + value + " HTTP/1.1\r\n" +
 "Host: " + host + "\r\n" +
 "Connection: close\r\n\r\n");
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
 // Read all the lines of the reply from server and print them to Serial- 3 -
 while (client.available())
 {
 String line = client.readStringUntil('\r');
 Serial.print(line);
 }
 Serial.println();
 Serial.println("closing connection");
}
