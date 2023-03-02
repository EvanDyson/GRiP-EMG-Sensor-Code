// Grove - EMG Sensor demo code
// This demo will need a Grove - Led Bar to show the motion 
// Grove - EMG Sensor connect to A0
// Grove - LED Bar connect to D8, D9
// note: it'll take about serval seconds to detect static analog value
// when you should hold your muscle static. You will see led bar from level 10 turn to 
// level 0, it means static analog value get ok

//#include <LED_Bar.h>
#include <Servo.h>
//LED_Bar bar(9, 8);

int max_analog_dta      = 700;              // max analog data
int min_analog_dta      = 80;              // min analog data
int static_analog_dta   = 0;                // static analog data
int output = 0;
int servoPin = 4;
Servo myservo;
int servoMin = 10;          // minimum servo position
int servoMax = 170;        // maximum servo position

// get analog value
int getAnalog(int pin)
{
    long sum = 0;
    
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pin);
    }
    
    int dta = sum>>5;
    
    max_analog_dta = dta>max_analog_dta ? dta : max_analog_dta;         // if max data
    min_analog_dta = min_analog_dta>dta ? dta : min_analog_dta;         // if min data
    
    return sum>>5;
}

void setup()
{
    Serial.begin(115200);
    myservo.attach(servoPin);
    long sum = 0;

    for(int i=0; i<=10; i++)
    {
        for(int j=0; j<100; j++)
        {
            sum += getAnalog(A0);
            delay(1);
        }
        
        //bar.setLevel(10-i);
        output = 10 - i;
    }
    
    sum /= 1100;
    
    static_analog_dta = sum;

    Serial.print("static_analog_dta = ");
    Serial.println(static_analog_dta);
}

int level       = 5;
int level_buf   = 5;

void loop()
{

    int val = getAnalog(A0);                    // get Analog value
    
    int level2;
    
    if(val>static_analog_dta)                   // larger than static_analog_dta
    {
        level2 = 5 + map(val, static_analog_dta, max_analog_dta, 0, 5);
    }
    else 
    {
        level2 = 5 - map(val, min_analog_dta, static_analog_dta, 0, 5);
    }
    
    // to smooth the change of led bar
    if(level2 > level)
    {
        level++;
    }
    else if(level2 < level)
    {
        level--;
    }

    if(level != level_buf)
    {
        level_buf = level;
        //bar.setLevel(level);
        output = level;
    }
  if (output == 1)
    myservo.write(servoMin);
  else if (output == 2)
    myservo.write(servoMin + 10);
    else if (output == 3)
    myservo.write(servoMin + 20);
    else if (output == 4)
    myservo.write(servoMin + 30);
    else if (output == 5)
    myservo.write(servoMin + 40);
    else if (output == 6)
    myservo.write(servoMin + 50);
    else if (output == 7)
    myservo.write(servoMin + 60);
    delay(100);

    // in serial monitor MAKE SURE 115200 baud rate is set.
    Serial.println(output);

}