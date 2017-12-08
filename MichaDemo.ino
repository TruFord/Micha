//function for gripper arm

/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

//define pin name
#define dir_1 11
#define pwm_1 10
#define dir_2 8
#define pwm_2 9



#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc2=LedControl(32,36,34,2);
LedControl lc1=LedControl(52,50,48,2);

/* we always wait a bit between updates of the display */
unsigned long delaytime=100;


#include <Servo.h>

Servo neckservo;  // create servo object to control a servo
Servo chinservo; // create servo to control wrist on gripper
Servo gripservo; // create servo to control wrist on gripper
Servo rotategripservo;

int closedgrip = 90;    // variable to store the servo position

int nintydeg = 90;
int opengrip = 0; // variable to store the servo position

void setup() {


   //declare pins as INPUT/OUTPUT 
  pinMode(pwm_1,OUTPUT);
  pinMode(dir_1,OUTPUT);
  pinMode(pwm_2,OUTPUT);
  pinMode(dir_2,OUTPUT);

  
  neckservo.attach(33);  // attaches the servo on pin 9 to the servo object
  chinservo.attach(35);
  gripservo.attach(37); // 0 deg is open 90+ is closed
  rotategripservo.attach(39); //34 is to the right

   /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc2.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc2.setIntensity(0,8);
  /* and clear the display */
  lc2.clearDisplay(0);

   lc1.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc1.setIntensity(0,8);
  /* and clear the display */
  lc1.clearDisplay(0);
  

}

void loop() {
 
 {
neutral();
}
//chinservo.write(80);
//rotategripservo.write(90);
//delay(1000);
//rotategripservo.write(34);
//delay(1000);
//rotategripservo.write(90);
//gripservo.write(0);

 // digitalWrite(dir_1,HIGH);    //controls the direction the motor
//digitalWrite(dir_2,HIGH);
//analogWrite(pwm_2,200);         //increase the speed of the motor from 0 to 255
 // analogWrite(pwm_1, 150);  //decrease the speed of the motor from 255 to 0



//delay(4500);
//gripservo.write(90);
//neckservo.write(30);              // tell servo to go to position in variable 'pos'
//delay(6000);                       // waits 15ms for the servo to reach the position
//neckservo.write(90);              // tell servo to go to position in variable 'pos'
delay(4000);
//chinservo.write(120);
delay(4000);
}

void neutral()
{
lc2.setRow(0,0,60);
lc2.setRow(0,1,126);
lc2.setRow(0,2,102);
lc2.setRow(0,3,102);
lc2.setRow(0,4,102);
lc2.setRow(0,5,126);
lc2.setRow(0,6,60);

lc1.setRow(0,0,60);
lc1.setRow(0,1,126);
lc1.setRow(0,2,102);
lc1.setRow(0,3,102);
lc1.setRow(0,4,102);
lc1.setRow(0,5,126);
lc1.setRow(0,6,60);



delay(50);
}
