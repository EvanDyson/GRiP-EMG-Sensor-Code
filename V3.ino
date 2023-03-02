#include <Servo.h>
#define THRESHOLD 200

int sensorPin = A0;    // select the input pin for the sensor

int newSensorValue = 0;   // variable to store the sensor value
int baseSensorValue = 0;

int servoPin = 4;

Servo SERVO_1;

void setup() {
  Serial.begin(115200);  // start the serial communication with a baud rate of 9600
  SERVO_1.attach(servoPin);
  baseSensorValue = analogRead(sensorPin);
  Serial.println("---------------- Setup done ----------------");
  Serial.print("Base value = ");
  Serial.println(baseSensorValue);
  /*
  add a reading period during setup for reading the muscle during contraction and during rest to have accurate date to read later on
  use these readings to compare to later on
  muscle contraction happens in a spike, activate the servo when the muscle contracts
  */
}

void loop() {
  newSensorValue = (analogRead(sensorPin) - baseSensorValue);  // read the sensor value
  Serial.println(newSensorValue);          // send the value to the serial monitor
  
  if(newSensorValue > 8)
  {
    SERVO_1.write(170);
    Serial.println("full turn");
    delay(2000);
  } 
  else if (newSensorValue > 4 && newSensorValue < 8)
  { 
    SERVO_1.write(90);
    Serial.println("half turn");
    delay(2000);
  } 
  else
  {
    SERVO_1.write(10);
    Serial.println("back to start");
    delay(750);
  } 
}