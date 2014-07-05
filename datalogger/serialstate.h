#include <Arduino.h>

struct XYAngle {
  int16_t angleX;
  int16_t angleY;
  int16_t heading;
};

struct IMUValues {
  int16_t accX;
  int16_t accY;
  int16_t accZ;

  int16_t gyroX;
  int16_t gyroY;
  int16_t gyroZ;

};

struct RCInput {
  int16_t roll;
  int16_t pitch;
  int16_t yaw;
  int16_t throttle;
};

struct MotorValues {
  int16_t motor1;
  int16_t motor2;
  int16_t motor3;
  int16_t motor4;
};

struct GPSValues {
  uint8_t hasFix;
  uint8_t satNumber;
  uint32_t lat;
  uint32_t  lng;
  uint16_t altitude;
  uint16_t groundSpeed;
};


static enum _serial_state {
  IDLE,
  HEADER_START,
  HEADER_M,
  HEADER_ARROW,
  HEADER_SIZE,
  HEADER_CMD,
} 
c_state;




