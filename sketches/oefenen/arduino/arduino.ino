#include "oefenen.h"

void setup() {
    Serial.begin(230400);
}

void loop() {
    Serial.println("Dingieee");
    delay(1000);
    Serial.println(ding);
    delay(500);
    Serial.println(i);
    i++;
}
