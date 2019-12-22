void printSensorReadings() {
  //Serial.print("llSensor: ");
  sensors[0] = digitalRead(llSensor);
  //Serial.println(sensors[0]);

  //Serial.print("lSensor: ");
  sensors[1] = digitalRead(lSensor);
  //Serial.println(sensors[1]);

  //Serial.print("rSensor: ");
  sensors[2] = digitalRead(rSensor);
  //Serial.println(sensors[2]);

  //Serial.print("rrSensor: ");
  sensors[3] = digitalRead(rrSensor);
  //Serial.println(sensors[3]);
  //Serial.println('\n');

  digitalWrite(13, !digitalRead(13));
}

void stopRobot() {
  digitalWrite(leftMotorControl, LOW);
  digitalWrite(rightMotorControl, LOW);
  analogWrite(rightMotorSpeed, 0);
  analogWrite(leftMotorSpeed, 0);
}

void startRobot() {
  digitalWrite(leftMotorControl, HIGH);
  digitalWrite(rightMotorControl, HIGH);
}

void moveForward() {
  analogWrite(rightMotorSpeed, 75);
  analogWrite(leftMotorSpeed, 95);
  //delay(2);
}

void turnLeft() {
  analogWrite(rightMotorSpeed, 120);
  analogWrite(leftMotorSpeed, 0);
  //delay(2);
}

void turnRight() {
  analogWrite(rightMotorSpeed, 0);
  analogWrite(leftMotorSpeed, 120);
  //delay(2);
}

void turnU() {
  //  startRobot();
  //  moveForward();
  //  delay(3);

  digitalWrite(rightMotorControl, HIGH);
  digitalWrite(leftMotorControl, LOW);
  analogWrite(rightMotorSpeed, 120);
  analogWrite(leftMotorSpeed, 0);
}

bool moveOneInch() {
  //  stopRobot();
  //  delay(1000);

  startRobot();
  analogWrite(rightMotorSpeed, 75);
  analogWrite(leftMotorSpeed, 95);
  delay(200);

  printSensorReadings();
  if (sensors[0] == 0 && sensors[1] == 0 && sensors[2] == 0 && sensors[3] == 0) {
    return false;
  }
  else if (sensors[0] == 1 && sensors[1] == 1 && sensors[2] == 1 && sensors[3] == 1) {
    return true;
  }
  return true;
}
