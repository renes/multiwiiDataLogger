#include <Arduino.h>

#ifndef serialstate_h
#define serialstate_h
#include "serialstate.h"
#endif

class CardLogger {

public:
  CardLogger();
  void init();
  void logXYAngle(XYAngle angle);
  void logIMU(IMUValues values);
  void logRC(RCInput values);
  void logGPS(GPSValues values);

private:
  String dir;
};

