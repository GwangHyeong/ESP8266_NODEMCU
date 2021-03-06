#include <ESP8266WiFi.h>
#include <SSD1306.h>
SSD1306 display(0x3c, D2, D1);
void setup() {

  delay(1000);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Initializing OLED Display");

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}


void loop() {
  drawFontFaceDemo();
  delay(1000);
  drawRectDemo();
  delay(1000);
  drawCircleDemo();
  delay(1000);
}

void drawFontFaceDemo() {

  display.clear();


  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);

  display.drawString(0, 0, "Hello world");
  display.setFont(ArialMT_Plain_16);

  display.drawString(0, 10, "Hello world");
  display.setFont(ArialMT_Plain_24);

  display.drawString(0, 26, "Hello world");

  display.display();

}

void drawRectDemo() {

  display.clear();

  for (int i = 0; i < 10; i++) {

    display.setPixel(10 - i, i);

  }

  display.drawRect(12, 12, 20, 20);

  display.fillRect(14, 14, 17, 17);

  display.drawHorizontalLine(0, 40, 20);

  display.drawVerticalLine(40, 0, 20);

  display.display();
  
}

void drawCircleDemo() {
  display.clear();
  for (int i = 1; i < 8; i++){
    display.setColor(WHITE);
     display.drawCircle(32, 32, i * 3);
  if (i % 2 == 0) {
    display.setColor(BLACK);
  }
  display.fillCircle(96, 32, 32 - i * 3);
}
display.display();
}
