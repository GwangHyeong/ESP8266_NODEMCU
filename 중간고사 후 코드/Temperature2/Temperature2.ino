#include <SSD1306.h>

#include <DHT.h>
#define DHTPIN D6
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SSD1306 display(0x3c, D2, D1);

void setup() { // put your setup code here, to run once:

Serial.begin(115200);
dht.begin();
display.init();
display.flipScreenVertically();
display.clear();
display.display();
}

void loop(){
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  
  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.print("Temperature:");
  Serial.print(temp);
  Serial.println("ºC");

  display.clear();

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0,20,"Temperature:");
  display.drawString(65,20,String(temp)+String("C"));
  display.drawString(0,40,"Humidity:");
  display.drawString(55,40,String(humidity)+String("%"));
  display.display();

  }
