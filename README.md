# GRiP-EMG-Sensor-Code

## V1
This version is the modified code from the seeeduino EMG example.

It is a rough design that does an unknown modification to the sensor value that brings it down to values 1-10.

My code serial prints and moves the servo in small increments depending on the input.

## V2
This version is a basic servo moving code dependant upon a set threshold value, in this code it is set to 200.

It will move the servo to its max set value if the value of the sensor is greater than the threshold. Otherwise the servo is set back its default value.

## V3
This version is the first where I try to implement a setup base sensor value that is read in during the setup of the lotus*.

During the loop a new sensor value is read and then subtracted from the base sensor value. If this value is greater than **_a number_** in this case 8, then the servo is moved to its max position. If the value is between **_any two numbers_** in this case between 4 and 8, then the servo is moved to its half way position. If the value is less than **_a number_** in this case 4, then the servo is moved to its minimum position.

## V4
The second version of my pre-read sensor value uses a map to remap the incoming sensor values to be a value that is between 10 and 170 to suit the servo's movable degrees. The servo is then moved.

This version is very finicky since the servo "twitches" a lot due to the small differences in the incoming values.

## V5
This third version of my pre-read sensor value utilizes 2 servos moved to the same degrees. This version also has a calibrate function* that I will describe below. The calibrate function needs work as right now it constantly moves the servo to the same position.

In my loop I use the same concept as version 3 where I do a subtraction to get a new sensor value based off of the base sensor value subtracted by the new read sensor value. There is also a boolean that is stored and checked per if statement to see if the servo is moved to a "flex" position or the max degree or if the servo is in the default position. The servo is moved correspondingly.

> Calibrate function
>
> The function has a for loop that loops 500 times to read in 500 EMG values and stores it.
>
> After storing, the values are then averaged into a average calibrated int value to be used later.


* Lotus refers to our seeedunio lotus board
