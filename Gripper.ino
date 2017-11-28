//function for gripper arm

/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo foamgripservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

Servo wristgripservo; // create servo to control wrist on gripper

int closedgrip = 90;    // variable to store the servo position

int nintydeg = 90;
int opengrip = 0; // variable to store the servo position

void setup() {
  foamgripservo.attach(9);  // attaches the servo on pin 9 to the servo object
  wristgripservo.attach(7);  // attaches the servo on pin 7 to the servo object
}

void loop() {

foamgripservo.write(opengrip);              // tell servo to go to position in variable 'pos'
delay(1000);                       // waits 15ms for the servo to reach the position
foamgripservo.write(closedgrip);              // tell servo to go to position in variable 'pos'
delay(10000);
wristgripservo.write(180);
delay(10000);
foamgripservo.write(opengrip);              // tell servo to go to position in variable 'pos'
delay(5000);
wristgripservo.write(180);
 delay(10000);
 wristgripservo.write(90);
 delay(2000);
 
}
