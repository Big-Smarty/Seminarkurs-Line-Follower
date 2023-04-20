#include "line_follower.hpp"

SensorArrayState sas;
DrivingParameters parameters;
RFIDState rfid_states[] = {RFIDState(""), RFIDState(""), RFIDState("")};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SENSOR_L, INPUT);
  pinMode(SENSOR_C, INPUT);
  pinMode(SENSOR_R, INPUT);
  pinMode(SERVO_L, OUTPUT);
  pinMode(SERVO_R, OUTPUT);

  servo_l.attach(SERVO_L);
  servo_r.attach(SERVO_R);

  SPI.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  handle_sa_state(sas, parameters);
  drive(parameters);
  handle_rfid(rfid_states);
}
