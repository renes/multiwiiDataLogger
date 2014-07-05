#include <Arduino.h>
#include "protocol.h"

Protocol::Protocol() 
{

}

/*
We have to combine two uint8 to a single int16
 */
int16_t readInt16(uint8_t inBuf[], int index) {
  return  (inBuf[index*2+1] << 8) | inBuf[index*2];
}

uint16_t readuInt16FromIndex(uint8_t inBuf[], int index) {
  return  (inBuf[index+1] << 8) | inBuf[index];
}

uint32_t readUInt32FromIndex(uint8_t inBuf[], int index) {
  uint32_t int1 = ((unsigned int)inBuf[index+1] << 8) | inBuf[index];
  uint32_t int2 =  ((unsigned int)inBuf[index+3] << 8) | inBuf[index+2];
  uint32_t result = (int2 << 16) | int1; 
  return result;
}

void Protocol::send_msp(uint8_t opcode, uint8_t * data, uint8_t n_bytes) {

  uint8_t checksum = 0;

  Serial.write((byte *)"$M<", 3);
  Serial.write(n_bytes);
  checksum ^= n_bytes;

  Serial.write(opcode);
  checksum ^= opcode;

  Serial.write(checksum);
}

XYAngle Protocol::evalAtt(uint8_t inBuf[]) {

  int16_t angx = readInt16(inBuf,0);
  int16_t angy = readInt16(inBuf,1);
  int16_t angle = readInt16(inBuf,2);  

  XYAngle ang = { 
    angx, angy, angle  };
  return ang;
}


IMUValues Protocol::evalIMU(uint8_t inBuf[]) {

  IMUValues result = { 
    readInt16(inBuf,0), readInt16(inBuf,1), readInt16(inBuf,2), readInt16(inBuf,3), readInt16(inBuf,4), readInt16(inBuf,5)        };
  return result;

}


RCInput Protocol::evalRC(uint8_t inBuf[]) {

  int16_t roll = readInt16(inBuf,0);
  int16_t pitch = readInt16(inBuf,1);
  int16_t yaw = readInt16(inBuf,2);
  int16_t throttle = readInt16(inBuf,3);

  RCInput result = { 
    roll, pitch, yaw, throttle           };

  return result;

}

MotorValues Protocol::evalMotor(uint8_t inBuf[]) {

  int16_t motor1 = readInt16(inBuf,0);
  int16_t motor2 = readInt16(inBuf,1);
  int16_t motor3 = readInt16(inBuf,2);
  int16_t motor4 = readInt16(inBuf,3);

  MotorValues result = { 
    motor1, motor2, motor3, motor4         };

  return result;

}

GPSValues Protocol::evalGPS(uint8_t inBuf[]) {

  // 0 or 1
  uint8_t hasFix = inBuf[0];
  uint8_t satNumber = inBuf[1];

  //10 000 000 deg
  uint32_t lat = readUInt32FromIndex(inBuf, 2);
  uint32_t lng = readUInt32FromIndex(inBuf, 6);

  uint16_t alt = readuInt16FromIndex(inBuf,10);
  uint16_t speedValue = readuInt16FromIndex(inBuf,12);

  GPSValues result = { 
    hasFix, satNumber, lat, lng, alt, speedValue        };

  return result;

}

