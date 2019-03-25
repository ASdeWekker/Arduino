#define led D2

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(230400);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 256; i += 5) {
    analogWrite(led, i);
    delay(100);
  }
  delay(500);
  for (int i = 256; i > 0; i -= 5) {
    analogWrite(led, i);
    delay(100);
  }
  delay(499);
}
