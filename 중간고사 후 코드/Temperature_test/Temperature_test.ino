#include <ESP8266WiFi.h>
#include <SSD1306.h>

#include <DHT.h>
#define DHTPIN D6
#define DHTTYPE DHT11
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

DHT dht(DHTPIN, DHTTYPE);
SSD1306 display(0x3c, D2, D1);



const char MAIN_page[] PROGMEM = R"=====(

 float s2 = temp;

<!doctype html>

<html>

<body>
s
s2
<h2>Dept of Smartmedia</h2>

<h3>HTML Form ESP8266</h3>

<form action="/action_page">

s
s2
</form>
</body>

</html>



)=====";



const char * ssid = "SMART324_3";
const char * password = "76543210";

ESP8266WebServer server(80);



int ledPin=D0;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};
int numTones = 8;

void handleRoot(){
 float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
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
  
  Serial.print("num:");
  Serial.println(number);

  int num = number.toInt();



    String s ="<a href='/'>Go Back</a>";

    server.send(200,"text/html",s);

    }

  void setup(void){
    dht.begin();
    display.init();
    display.flipScreenVertically();
    display.clear();
    display.display();
    Serial.begin(115200);
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
 float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  
  //Serial.print("Humidity:");
  //Serial.print(humidity);
  //Serial.print("Temperature:");
  //Serial.print(temp);
  //Serial.println("ºC");

  display.clear();

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0,20,"Temperature:");
  display.drawString(65,20,String(temp)+String("C"));
  display.drawString(0,40,"Humidity:");
  display.drawString(55,40,String(humidity)+String("%"));
  display.display();


  }
