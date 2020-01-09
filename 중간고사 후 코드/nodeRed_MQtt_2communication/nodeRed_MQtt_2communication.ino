#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char * ssid = "SMART324_3";
const char * password = "76543210";

const char * mqtt_server = "broker.mqtt-dashboard.com"; //브로커주소
const char * outTopic = "inTopic62042"; //사용자가 결정해서 기록
const char * inTopic = "outTopic62042"; //사용자가 결정해서 기록  
const char * clientName = "960424Client"; //다음 이름이 중복되지 않게 수정

const int analogInPin = A0;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
long now = millis();
long lastMeasure = 0;
char msg[50];

int led=D4;
int timeIn=1000;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(115200);
  delay(10);
  setup_wifi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);  
  

}
void setup_wifi(){
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

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived[");
  Serial.print(topic);
  Serial.print("]");
  for(int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }
  
  Serial.println();
  
  String inString="";
  
  for(int i = 0; i < length; i++){
    inString += (char)payload[i];
  }
  timeIn=inString.toInt();
}




void reconnect() {
  while(!client.connected()){
    Serial.print("Attempting MQTT connection...");

    if(client.connect(clientName)){
      Serial.println("connected");
      client.publish(outTopic,"Reconnected");
      client.subscribe(inTopic);
    }else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void loop() {

  if(!client.connected())
  {
    reconnect();
  }

now =millis();

if(now - lastMsg > 1000){
  int vreading = analogRead(0);
  
 static char vdata[7];
  dtostrf((float)vreading,6,1,vdata);
  client.publish(outTopic,vdata);
  Serial.print("Resistor");
  Serial.print(vreading);
  Serial.println("OHM");
}

  client.loop(); 
  digitalWrite(led,HIGH);
  delay(timeIn);
  digitalWrite(led,LOW);
  delay(timeIn);
}
