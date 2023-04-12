#include <Servo.h>
#define THRESHOLD 200

int sensorPin = A0;    // select the input pin for the sensor
int newSensorValue = 0;   // variable to store the sensor value
int baseSensorValue = 0;
int rawSensorValue = 0;
int servo1Pin = 4;
int servo2Pin = 8;
bool turnCheck = false;
Servo SERVO_1;
Servo SERVO_2;
int calibration[500];
int calibrated = 0;

void setup() {
  Serial.begin(115200);  // start the serial communication with a baud rate of 9600
  SERVO_1.attach(servo1Pin);
  SERVO_2.attach(servo2Pin);


  Serial.println("Please keep still for the initial scan...");
  delay(1500);
  calibrate();

  baseSensorValue = calibrated;
  //baseSensorValue = analogRead(sensorPin);
  Serial.println("---------------- Setup done ----------------");
  Serial.print("Base value = ");
  Serial.println(baseSensorValue);
  /*
  add a reading period during setup for reading the muscle during contraction and during rest to have accurate date to read later on
  use these readings to compare to later on
  muscle contraction happens in a spike, activate the servo when the muscle contracts
  */
}

void calibrate(){
  for (int i = 0; i < 100; i++){
    calibration[i] = analogRead(sensorPin);
    Serial.println(calibration[i]);
  }
  for (int i = 0; i < 100; i++){
    calibrated += calibration[i];
  }
    //Serial.println(calibrated);

  calibrated /= 100;
}

// PLACE SENSORS WHITE RED BLACK white on muscle, red on muscle head, and black on ground

void loop() {
  rawSensorValue = analogRead(sensorPin);
  newSensorValue = (analogRead(sensorPin) - baseSensorValue);  // read the sensor value
  
  /*
  Serial.print("Raw sensor value: ");
  Serial.println(rawSensorValue);
  Serial.print("Base sensor value: ");
  Serial.println(baseSensorValue);
  Serial.print("New Adjusted sensor value: ");
  Serial.println(newSensorValue);          // send the value to the serial monitor
  */
  if(newSensorValue > 10 && turnCheck == false)
  {
    SERVO_1.write(170);
    SERVO_2.write(170);
    Serial.println("full turn");
    turnCheck = true;
    delay(5000);
  } 
  else if(newSensorValue > 10 && turnCheck == true)
  {
    SERVO_1.write(10);
    SERVO_2.write(10);
    Serial.println("resetting turn");
    turnCheck = false;
    delay(5000);
  } 
  delay(500);
}
