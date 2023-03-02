#include <Servo.h>

int sensorPin = A0;    // select the input pin for the sensor
int sensorValue = 0;   // variable to store the sensor value
int servoPin = 4;          // select the pin for the servo
int servoMin = 10;          // minimum servo position
int servoMax = 170;        // maximum servo position
Servo myservo;             // create servo object to control a servo
int beg_val = 0;
void setup() {
  Serial.begin(115200);  // start the serial communication with a baud rate of 9600
  myservo.attach(servoPin);
  beg_val = analogRead(sensorPin);
  Serial.print("starting value: ");
  Serial.println(beg_val);
    delay(250);                           // wait 100 milliseconds

}


// PLACE SENSORS WHITE RED BLACK white on muscle, red on muscle head, and black on ground

void loop() {
  sensorValue = analogRead(sensorPin);  // read the sensor value
  int servoPos = map(sensorValue, beg_val, 800, servoMin, servoMax); // map the sensor value to a servo position
  if (servoPos < 0)
    servoPos = 0;
  myservo.write(servoPos);  // move the servo to the new position
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue); // send the sensor value to the serial monitor
  Serial.print(", ");
  Serial.print("Servo Value: ");
  Serial.println(servoPos);
  delay(250);                           // wait 100 milliseconds
}
