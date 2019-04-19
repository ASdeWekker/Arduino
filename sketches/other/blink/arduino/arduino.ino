int led = 13;
int wacht = 100;

void setup () {
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(wacht);
  digitalWrite(led, LOW);
  delay(wacht);
}

