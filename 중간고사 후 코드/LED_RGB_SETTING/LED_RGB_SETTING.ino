int LED_pin_R = 15;
int LED_pin_G = 12;
int LED_pin_B = 13;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  delay(10);

  pinMode(LED_pin_R,OUTPUT);
  pinMode(LED_pin_G,OUTPUT);
  pinMode(LED_pin_B,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  digitalWrite(LED_pin_R,1);
  delay(1000);
  digitalWrite(LED_pin_R,0);
  delay(100);
  
  digitalWrite(LED_pin_G,1);
  delay(1000);
  digitalWrite(LED_pin_G,0);
  delay(100);
  
  digitalWrite(LED_pin_B,1);
  delay(1000);
  digitalWrite(LED_pin_B,0);
  delay(100);
}
