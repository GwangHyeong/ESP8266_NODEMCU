#include <ESP8266WiFi.h>

const char * ssid = "SMART324_3";

const char * password = "76543210";

const char * host = "184.106.153.149";

const char * WriteAPIKey = "RKFLOURXYXEF30YJ";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
}

int value = 20;

void loop() {
  delay(12000);
  value+=10;

  if(value>100)value=20;

  Serial.print("connecting to " );
  Serial.print(host);

  WiFiClient client;
  const int httpPort = 80;

  if(!client.connect(host,httpPort))
  {
    Serial.println("connection failed");
    return;
  }

  String url = "/update?key=PZUFBH2URGCXMTD3&field1=";

  Serial.print("URL:");
  Serial.print(url);

  Serial.print("value: ");
  Serial.print(value);

  client.print(String("GET ") + url + value + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close \r\n\r\n");
  unsigned long timeout = millis();
  while(client.available() == 0)
  {
    if (millis() - timeout > 5000)
    {
      Serial.println(">>>client timeout 1");
      client.stop();
      return;
    }
  }
  while(client.available())
  {
    String line = client.readStringUntil('r');
    Serial.print(line);
    
  }
  Serial.println();
  Serial.println("closing connection");
}
