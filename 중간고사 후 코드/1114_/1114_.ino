#include <ESP8266WiFi.h>
#include <DHT.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#define DHTPIN D6 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
// wifi
const char * ssid = "SMART324_3";

const char * password = "76543210";
WiFiClient client;
// thingSpeak 
unsigned long ChannelID = 915151;
const char* WriteAPIKey = "GXS3DA53VPSDCPL0";
//DHT
uint8_t temperature, humidity;
unsigned long lastCheck;
void setup() {
 Serial.begin(115200);
 delay(10);
 
 initWiFi();
 ThingSpeak.begin(client);
 lastCheck = 0;
}
void loop() {
 float c_time = 60000 * 0.1;
 if(millis() - lastCheck > c_time) {
 static boolean data_state = false;
 temperature = dht.readTemperature();
 humidity = dht.readHumidity();
 Serial.print("Temperature : ");
 Serial.print(temperature); Serial.println("C");
 Serial.print("Humidity : ");
 Serial.print(humidity);
 Serial.println("%");
 if(data_state){
 ThingSpeak.writeField(ChannelID, 1, temperature, WriteAPIKey);
 data_state = false;
 } else {
 ThingSpeak.writeField(ChannelID, 2, humidity, WriteAPIKey);
 data_state = true;
 }
 lastCheck = millis();
 }
 delay(100);
}
void initWiFi(){
 Serial.println();
 Serial.println();
 Serial.println("Connectiong to ssid ...");
 // attempt to connect to WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED){
 delay(500);
 Serial.println(".");
 }
 Serial.println();
 Serial.println("Connected WiFi");
 
 Serial.println(WiFi.localIP());
 Serial.println();
}
