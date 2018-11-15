// Berekeningen
// Straal van band in inch:
// 
// Omtrek is pi*2*straal=
// 
// Max snelheid is 35 mph / 56 kph
// max rotatie per secondes: 7.25

const int reed = A0;

// vars
int reedVal;
// Tijd voor 1 rotatie in ms
long timer;
float mph;
float kmh = mph * 1.609344;
// Straal van band in inches;
float radius;
float circumference;


// Minuten tijd in ms voor 1 rotatie, voor debouncen.
int maxReedCounter;
int reedCounter;

void setup() {
  reedCounter = maxReedCounter;
  circumference = 2 * 3.14159 * radius;
  pinMode(reed, INPUT);

  // TIMER SETUP.
  // Met de timer kan ik precies de reed switch meten
  cli(); // stopt de interrupts.

  // Zet de timer om op 1khz te onderbreken.
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 1999;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11);
  TIMSK1 |= (1 << OCIE1A);

  sei();//sta onderbreken toe.

  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect) {
  reedVal = digitalRead(reed);
  if (reedVal) {
    if (reedCounter == 0) {
      mph = (56.8 * float(circumference)) / float(timer);
      timer = 0;
      reedCounter = maxReedCounter;
    } else {
      if (reedCounter > 0) {
        reedCounter -= 1;
      }
    }
  } else {
    if (reedCounter > 0) {
      reedCounter -= 1;
    }
  }

  if (timer > 2000) {
    mph = 0;
  } else {
    timer += 1;
  }
}

void displayMPH() {
  Serial.print("mph: ");
  Serial.print(mph);
  Serial.print(".  kmh: ");
  Serial.println(kmh);
  Serial.println();
}

void loop() {
  displayMPH();
  delay(1000);
}

