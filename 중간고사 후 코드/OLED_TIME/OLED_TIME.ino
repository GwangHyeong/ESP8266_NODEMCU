#include <SSD1306.h>

SSD1306 display(0x3c, D2, D1);

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

}


void drawHelloWorld() {

  display.setTextAlignment(TEXT_ALIGN_LEFT);

  display.display();

  for (int i = 0; i < 9999; i++) {
    display.clear();
    String a = String(i);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 15, a);
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 40, "LGH");
    display.display();
    delay(1000);
  }
}
