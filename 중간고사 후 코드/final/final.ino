#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <SSD1306.h>

#define PIN_DHT D6
#define DHTTYPE DHT11
const char * ssid = "SMART324_3";
const char * password = "76543210";
SSD1306 display(0x3c, D2, D1); //온습도 센서 , 화면 디스플레이 매개변수

const char * mqtt_server = "broker.mqtt-dashboard.com"; //브로커주소
const char * outTopic = "inTopic62042"; //사용자가 결정해서 기록
const char * outTopic2 = "inTopic62042_1"; //사용자가 결정해서 기록
const char * outTopic3 = "inTopic62042_2"; //사용자가 결정해서 기록
const char * inTopic = "outTopic62042"; //사용자가 결정해서 기록  
const char * clientName = "960424Client"; //다음 이름이 중복되지 않게 수정

const int analogInPin = A0;

DHT dht(PIN_DHT, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
long now = millis();
long lastMeasure = 0;
char msg[50];

int led=D4;
int timeIn=1000;

void setup() {
      // 화면표시
  display.init();
  display.flipScreenVertically();
  display.clear();
  display.display();
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
      client.publish(outTopic2,"Reconnected");
      client.publish(outTopic3,"Reconnected");
      client.subscribe(inTopic);
    }else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
float value;
float hvalue;
void loop() {

  if(!client.connected())
  {
    reconnect();
  }

now =millis();

if(now - lastMsg > 1000){
  int vreading = analogRead(0);
  
  value = dht.readTemperature();
  String tt = (String)value;
  hvalue = dht.readHumidity();
  
  static char vvdata[6];
  static char vvdata2[6];
  dtostrf((float)value,5,1,vvdata2);
  dtostrf((float)hvalue,5,1,vvdata);
  client.publish(outTopic2,vvdata2);
  client.publish(outTopic3,vvdata);
  Serial.print(" 온도 : ");
  Serial.print(value);
  Serial.print(" 습도 : ");
  Serial.print(hvalue);
  
  //OLED  
  display.clear();

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, " Temperature:");
  display.drawString(65, 10, String(value) + String("C"));
  display.drawString(0, 25, " Humidity:");
  display.drawString(55, 25, String(hvalue) + String("%"));
  display.drawString(0, 40, " CDS:");
  display.drawString(55, 40, String(vreading));
  display.display();
  
  static char vdata[6];
  dtostrf((float)vreading,5,1,vdata);
  client.publish(outTopic,vdata);
  Serial.print(" CDS : ");
  Serial.println(vreading);
 


  
}
  
  client.loop(); 
  digitalWrite(led,HIGH);
  delay(timeIn);
  digitalWrite(led,LOW);
  delay(timeIn);
}

