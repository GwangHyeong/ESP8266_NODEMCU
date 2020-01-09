#include <ESP8266WiFi.h>
#include <PubSubClient.h>
String channelid = "921625";
String apiwritekey = "LAHFK75X2PUF67WT";
String apiKey = "YD7ZUY0Z6HPD137Q";
const char * ssid = "SMART324_3";
const char * password = "76543210";

WiFiClient client;
PubSubClient mqttClient(client);

const char* server = "mqtt.thingspeak.com";

unsigned long lastConnectionTime = 0;

const unsigned long postingInterval = 15L * 1000L;
const int analogInPin = A0;

void setup() {

  Serial.begin(115200);

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

  mqttClient.setServer(server,1883);
}


  
void loop() {

  if(!mqttClient.connected())
  {
    reconnect();
  }
  mqttClient.loop();

  if(millis() - lastConnectionTime > postingInterval)
  {
    mqttpublish();
  }
}
  void reconnect()
  {
    while(!mqttClient.connected())
    {
      Serial.print("attempting mqtt connection..");

      if(mqttClient.connect("ArduionWiFi101Client")){
        Serial.println("connected");
      }else
      {
        Serial.print("failed, rc=");
        Serial.print(mqttClient.state());
        delay(5000);
      }
    }
}
void mqttpublish(){
  float t = analogRead(analogInPin);
  String data = String(t,DEC);

  int length = data.length();
  char msgBuffer[length];

  data.toCharArray(msgBuffer, length + 1);
  Serial.println(msgBuffer);

  mqttClient.publish("channels/921625/publish/fields/field1/LAHFK75X2PUF67WT",msgBuffer);

  lastConnectionTime = millis();
}

