#include <SSD1306.h>

SSD1306 display(0x3c,D2,D1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.init();
  display.flipScreenVertically();

  display.clear();
  drawHelloWorld();
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void drawHelloWorld(){
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0,0,"Hello OLED");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,20,"Smart Media");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0,40,"gooooood");
}

