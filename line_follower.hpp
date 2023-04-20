#pragma once

#include <Servo.h>

#include <SPI.h>
#include <MFRC522.h>

#define SENSOR_L 0
#define SENSOR_C 1
#define SENSOR_R 2

#define SERVO_L 3
#define SERVO_R 4

#define SS_PIN 10
#define RST_PIN 9

Servo servo_l;
Servo servo_r;

MFRC522 mfrc522(SS_PIN, RST_PIN);

enum SensorArrayState : uint32_t {
    eLeft = 0x100,
    eSlightLeft = 0x110,
    eCenter = 0x010,
    eSlightRight = 0x011,
    eRight = 0x001,
};

struct DrivingParameters {
    uint32_t velocity{0};
    uint32_t error_left{0};
    uint32_t error_right{0};
};

struct RFIDState {
    RFIDState(const char* name);
    const char* rfid_name;
    bool encountered{false};
};

uint32_t get_sa_state();
void handle_sa_state(uint32_t sa_state, DrivingParameters &parameters);
void drive(const DrivingParameters &parameters);

void handle_rfid(RFIDState *states);