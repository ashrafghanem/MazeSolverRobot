#include <SoftwareSerial.h>
#include "declarations.h"

SoftwareSerial hc06(BluetoothTX, BluetoothRX);

void setup() {
  pinMode(leftMotorSpeed, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);
  pinMode(leftMotorControl, OUTPUT);
  pinMode(rightMotorControl, OUTPUT);

  // 38400 is the default baud rate of the bluetooth module HC-06
  hc06.begin(38400);
  Serial.begin(38400);
}

void loop() {
  control = hc06.read();
  //  Serial.println("still outside while");
  //  delay(2000);

  if (control == '1') {
    while (true) {
      if (hc06.read() == '0') {
        //        Serial.println("stopped");
        stopRobot();
        break;
      }
      // Serial.println("running");
      // 1 means black, one led is lighting
      // 0 means white, two leds are lighting
      printSensorReadings();

      if ((sensors[1] | sensors[2]) == 1) {
        startRobot();
        // straight
        if (sensors[0] == 0 && sensors[3] == 0) {
          moveForward();
        }
        // left
        if (sensors[0] == 1 && sensors[3] == 0) {
          turnLeft();
        }
        // right
        if (sensors[0] == 0 && sensors[3] == 1) {
          turnRight();
        }
        // stop
        if (sensors[0] == 1 && sensors[1] == 1 && sensors[2] == 1 && sensors[3] == 1) {
          bool stop = moveOneInch();
          if (stop) {
            stopRobot();
            continue;
          }
          else {
            turnLeft();
          }
        }
        else{
          turnLeft();
        }
      }
      // U turn (180 degrees)
      else if (sensors[0] == 0 && sensors[1] == 0 &&
               sensors[2] == 0 && sensors[3] == 0) {
        startRobot();
        turnU();
      }

      else if (sensors[0] == 0 && sensors[1] == 0 &&
               sensors[2] == 1 && sensors[3] == 1) {
        startRobot();
        turnRight();
      }
      else if (sensors[0] == 0 && sensors[1] == 0 &&
               sensors[2] == 0 && sensors[3] == 1) {
        startRobot();
        turnRight();
      }

      else if (sensors[0] == 1 && sensors[1] == 1 &&
               sensors[2] == 0 && sensors[3] == 0) {
        startRobot();
        turnLeft();
      }
      else if (sensors[0] == 1 && sensors[1] == 0 &&
               sensors[2] == 0 && sensors[3] == 0) {
        startRobot();
        turnLeft();
      }
    }
  }
}
