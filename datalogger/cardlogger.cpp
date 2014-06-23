#include <Arduino.h>

#ifndef cardlogger_h
#define cardlogger_h
#include "cardlogger.h"
#endif

#include <SD.h>

/*
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 or 53 on mega
 
 For mega check
 
 http://arduino.cc/de/Reference/SPI
 
 */


const int chipSelect = 53;
const String seperator = ";";

String  directory;

CardLogger::CardLogger() {


}

void CardLogger::init() {
  while (!Serial) {
  }

  pinMode(chipSelect, OUTPUT);

  if (!SD.begin(chipSelect)) {
    return;
  }

  String directoryPreFix = "log_";

  for (int i = 0; i <= 500; i++) {

    String dir  = directoryPreFix;
    dir.concat(i);
    char charDir[dir.length()+1];
    dir.toCharArray(charDir, sizeof(charDir));

    if (!SD.exists(charDir)) {
      if(SD.mkdir(charDir)) {
        directory =  String(charDir);
        break;
      } 

    }
  }
}

void CardLogger::logXYAngle(XYAngle angle) {

  String s(directory);
  s.concat("/angle.csv");
  char charDir[s.length()+1];
  s.toCharArray(charDir, sizeof(charDir));

  File dataFile = SD.open(charDir, FILE_WRITE);

  dataFile.print(millis());
  dataFile.print(seperator);
  dataFile.print(angle.angleX);
  dataFile.print(seperator);
  dataFile.print(angle.angleY);
  dataFile.print(seperator);
  dataFile.println(angle.heading);

  dataFile.close(); 

}

void CardLogger::logIMU(IMUValues values) {

  String s(directory);
  s.concat("/imu.csv");
  char charDir[s.length()+1];
  s.toCharArray(charDir, sizeof(charDir));

  File dataFile = SD.open(charDir, FILE_WRITE);

  dataFile.print(millis());

  dataFile.print(seperator);
  dataFile.print(values.accX);

  dataFile.print(seperator);
  dataFile.print(values.accY);

  dataFile.print(seperator);
  dataFile.print(values.accZ);

  dataFile.print(seperator);
  dataFile.print(values.gyroX);

  dataFile.print(seperator);
  dataFile.print(values.gyroY);

  dataFile.print(seperator);
  dataFile.println(values.gyroZ);

  dataFile.close(); 

}

void CardLogger::logRC(RCInput values) {

  String s(directory);
  s.concat("/rc.csv");
  char charDir[s.length()+1];
  s.toCharArray(charDir, sizeof(charDir));

  File dataFile = SD.open(charDir, FILE_WRITE);


  dataFile.print(millis());

  dataFile.print(seperator);
  dataFile.print(values.roll);

  dataFile.print(seperator);
  dataFile.print(values.pitch);

  dataFile.print(seperator);
  dataFile.print(values.yaw);

  dataFile.print(seperator);
  dataFile.println(values.throttle);

  dataFile.close(); 

}
