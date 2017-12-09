/******************************************************************************
  MostBasicFollower.ino

  A very simple method for following a line with a redbot and the line follower array.

  Marshall Taylor, SparkFun Engineering

  5-27-2015

  Library:
  https://github.com/sparkfun/SparkFun_Line_Follower_Array_Arduino_Library
  Product:
  https://github.com/sparkfun/Line_Follower_Array

  This example demonstrates the easiest way to interface the redbot sensor bar.
  "SensorBar mySensorBar(SX1509_ADDRESS);" creates the sensor bar object.
  "mySensorBar.init();" gets the bar ready.
  "mySensorBar.getDensity()" gets the number of points sensed.
  "mySensorBar.getPosition()" gets the average center of sensed points.

  The loop has three main points of operation.
  1.  check if the density is reasonable
  2.  get the position
  3.  choose a drive mode based on position

******************************************************************************/


#include "Wire.h"
#include "sensorbar.h"
//removed redbot library

// Uncomment one of the four lines to match your SX1509's address
//  pin selects. SX1509 breakout defaults to [0:0] (0x3E).
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
//const byte SX1509_ADDRESS = 0x3F;  // SX1509 I2C address (01)
//const byte SX1509_ADDRESS = 0x70;  // SX1509 I2C address (10)
//const byte SX1509_ADDRESS = 0x71;  // SX1509 I2C address (11)

SensorBar mySensorBar(SX1509_ADDRESS);



//Define the states that the decision making machines uses:
#define IDLE_STATE 0
#define READ_LINE 1
#define GO_FORWARD 2
#define GO_LEFT 3
#define GO_RIGHT 4

// Pins for motors
#define dir_1 11    //Right Track Direction
#define pwm_1 10    //Right Track Speed
#define dir_2 8     //Left Track Direction
#define pwm_2 9     //Left Track Speed


uint8_t state;

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


void setup()
{
  Serial.begin(9600);  // start serial for output
  Serial.println("Program started.");
  Serial.println();

  //Default: the IR will only be turned on during reads.
  mySensorBar.setBarStrobe();
  //Other option: Command to run all the time
  //mySensorBar.clearBarStrobe();

  //Default: dark on light
  mySensorBar.clearInvertBits();
  //Other option: light line on dark
  //mySensorBar.setInvertBits();

  //Don't forget to call .begin() to get the bar ready.  This configures HW.
  uint8_t returnStatus = mySensorBar.begin();
  if (returnStatus)
  {
    Serial.println("sx1509 IC communication OK");
  }
  else
  {
    Serial.println("sx1509 IC communication FAILED!");
  }
  Serial.println();

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

void loop()
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

  uint8_t nextState = state;
  switch (state) {
    case IDLE_STATE:   //stops both motors

     Serial.println("STATE: IDLE");
    
      digitalWrite(dir_1, HIGH);    //controls the direction the motor HIGH = Forward
      digitalWrite(dir_2, HIGH);    //controls the direction the motor HIGH = Forward
      analogWrite(pwm_2, 0);        //increase the speed of the motor from 0 to 255
      analogWrite(pwm_1, 0);        //decrease the speed of the motor from 255 to 0;
      nextState = READ_LINE;
      break;
    case READ_LINE:
        Serial.println("STATE: read line");
      if ( mySensorBar.getDensity() < 7 )
      {
        nextState = GO_FORWARD;
        if ( mySensorBar.getPosition() < -50 )
        {
          nextState = GO_LEFT;
        }
        if ( mySensorBar.getPosition() > 50 )
        {
          nextState = GO_RIGHT;
        }
      }
      else
      {
        nextState = IDLE_STATE;
      }
      break;
    case GO_FORWARD:



 
      neckservo.write(90);              // tell servo to go to position in variable 'pos'

      Serial.println("case: go forward");
      digitalWrite(dir_1, HIGH);    //controls the direction the motor HIGH = Forward
      digitalWrite(dir_2, HIGH);    //controls the direction the motor HIGH = Forward
      analogWrite(pwm_2, 125);        //increase the speed of the motor from 0 to 255
      analogWrite(pwm_1, 125);        //decrease the speed of the motor from 255 to 0;    POWER SENT TO RIGHT TRACK MUST BE ~75% POWER BECASUE OF HIGH FRICTION ON LEFT SIDE.
      nextState = READ_LINE;
      break;
    case GO_LEFT:

  
    neckservo.write(150);              // tell servo to go to position in variable 'pos'

     Serial.println("case: go left");
      digitalWrite(dir_1, HIGH);    //controls the direction the motor HIGH = Forward
      digitalWrite(dir_2, LOW);    //controls the direction the motor HIGH = Forward
      analogWrite(pwm_2, 125);        //increase the speed of the motor from 0 to 255
      analogWrite(pwm_1, 125);        //decrease the speed of the motor from 255 to 0;    POWER SENT TO RIGHT TRACK MUST BE ~75% POWER BECASUE OF HIGH FRICTION ON LEFT SIDE.
      nextState = READ_LINE;
      break;
    case GO_RIGHT:

    
    neckservo.write(30);              // tell servo to go to position in variable 'pos'
    Serial.println("cdase: go right");
      digitalWrite(dir_1, LOW);    //controls the direction the motor HIGH = Forward
      digitalWrite(dir_2, HIGH);    //controls the direction the motor HIGH = Forward
      analogWrite(pwm_2, 125);        //increase the speed of the motor from 0 to 255
      analogWrite(pwm_1, 125);        //decrease the speed of the motor from 255 to 0;    POWER SENT TO RIGHT TRACK MUST BE ~75% POWER BECASUE OF HIGH FRICTION ON LEFT SIDE.

      nextState = READ_LINE;
      break;
    default:
      digitalWrite(dir_1, HIGH);    //controls the direction the motor HIGH = Forward
      digitalWrite(dir_2, HIGH);    //controls the direction the motor HIGH = Forward
      analogWrite(pwm_2, 0);        //increase the speed of the motor from 0 to 255
      analogWrite(pwm_1, 0);        //decrease the speed of the motor from 255 to 0;
      
      break;
  }
  state = nextState;





}







