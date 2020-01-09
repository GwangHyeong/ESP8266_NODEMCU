int VR_Pin = A0;
int LED_pin = D0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // 저항값에 따라서 led
  int reading = analogRead(VR_Pin);
  Serial.println(reading);
  delay(500);
}
