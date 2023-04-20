#include "line_follower.hpp"

RFIDState::RFIDState(const char* name) : rfid_name(name) {}

uint32_t get_sa_state() {
    uint32_t out;
    if(digitalRead(SENSOR_L)) {
        out = out | SensorArrayState::eLeft;
    }
    if(digitalRead(SENSOR_R)) {
        out = out | SensorArrayState::eRight;
    }
    if(digitalRead(SENSOR_C)) {
        out = out | SensorArrayState::eCenter;
    }
    return out;
}

void handle_sa_state(uint32_t sa_state, DrivingParameters &parameters) {
    switch(sa_state) {
        case SensorArrayState::eLeft:
            parameters.error_right = 0;
            parameters.error_left += 2;
            break;
        case SensorArrayState::eSlightLeft:
            parameters.error_right = 0;
            parameters.error_left++;
            break;
        case SensorArrayState::eCenter:
            parameters.error_left = 0;
            parameters.error_right = 0;
            break;
        case SensorArrayState::eSlightRight:
            parameters.error_left = 0;
            parameters.error_right++;
            break;
        case SensorArrayState::eRight:
            parameters.error_left = 0;
            parameters.error_right += 2;
            break;
        default:
            break;
    }
}

void drive(const DrivingParameters &parameters) {
    servo_l.write(parameters.velocity - (parameters.error_left / 5));
    servo_r.write(parameters.velocity - (parameters.error_right / 5));
}

void handle_rfid(RFIDState *states) {
    if(!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }
    if(!mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    String uid_name;
      for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
        uid_name.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        uid_name.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    uid_name.toUpperCase();
    for(int i = 0; i < 3; i++) {
        if (states[i].rfid_name == uid_name.c_str()) {
            states[i].encountered = true;
        }
    }
}