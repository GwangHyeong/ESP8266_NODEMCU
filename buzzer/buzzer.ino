#define Buzzer D2
int tones[] = {261,294,330,349,392,440,494,523};
int numTones = 8;
void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  int idata;
  if(Serial.available())
  {
    idata = Serial.parseInt();
    Serial.println(idata);
    music(idata);
  }
  // put your main code here, to run repeatedly:

}

void music(int mdata)
{
  tone(Buzzer, tones[mdata-1]);
  delay(100);
  noTone(Buzzer);
}

