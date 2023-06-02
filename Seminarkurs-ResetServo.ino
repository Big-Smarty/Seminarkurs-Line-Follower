#include "Servo.h"

#define PIN 3

Servo servo;

void setup() {
    servo.attach(PIN);
}

void loop() {
    servo.write(90);
}