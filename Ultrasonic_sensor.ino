//Ultrasonic sensor function

//http://www.robotshop.com/en/ultrasonic-sensor-scanner-kit-120.html

  
 2 // # Editor     : ZRH from DFRobot
 3 // # Date       : 29.08.2014
 4 
 5 // # Product name: URM V4.0 ultrasonic sensor
 6 // # Product SKU : SEN0001
 7 // # Version     : 1.0
 8 
 9 // # Description:
10 // # The Sketch for scanning 180 degree area 3-500cm detecting range
11 // # The sketch for using the URM37 PWM trigger pin mode from DFRobot  
12 // #   and writes the values to the serialport
13 // # Connection:
14 // #       Vcc (Arduino)    -> Pin 1 VCC (URM V4.0)
15 // #       GND (Arduino)    -> Pin 2 GND (URM V4.0)
16 // #       Pin 3 (Arduino)  -> Pin 4 ECHO (URM V4.0)
17 // #       Pin 5 (Arduino)  -> Pin 6 COMP/TRIG (URM V4.0)
18 // #       Pin A0 (Arduino) -> Pin 7 DAC (URM V4.0)
19 // # Working Mode: PWM trigger pin  mode.
20 
21 #define  Measure  1     //Mode select
22 int URECHO = 3;         // PWM Output 0-25000US,Every 50US represent 1cm
23 int URTRIG = 5;         // PWM trigger pin
24 int sensorPin = A0;     // select the input pin for the potentiometer
25 int sensorValue = 0;    // variable to store the value coming from the sensor
26 
27 unsigned int DistanceMeasured= 0;
28 
29 void setup() 
30 {
31   //Serial initialization
32   Serial.begin(9600);                        // Sets the baud rate to 9600
33   pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
34   digitalWrite(URTRIG,HIGH);                 // Set to HIGH 
35   pinMode(URECHO, INPUT);                    // Sending Enable PWM mode command
36   delay(500);
37   Serial.println("Init the sensor");
38 
39  }
40 void loop()
41 {
42   PWM_Mode();
43   delay(100);
44 } 
45 
46 void PWM_Mode()                              // a low pull on pin COMP/TRIG  triggering a sensor reading
47 { 
48   Serial.print("Distance Measured=");
49   digitalWrite(URTRIG, LOW);
50   digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses  
51   if( Measure)
52   {
53     unsigned long LowLevelTime = pulseIn(URECHO, LOW) ;
54     if(LowLevelTime>=45000)                 // the reading is invalid.
55     {
56       Serial.print("Invalid");
57     }
58     else{
59     DistanceMeasured = LowLevelTime /50;   // every 50us low level stands for 1cm
60     Serial.print(DistanceMeasured);
61     Serial.println("cm");
62   }
63 
64   }
65   else {
66     sensorValue = analogRead(sensorPin); 
67     if(sensorValue<=10)                   // the reading is invalid.
68     {
69       Serial.print("Invalid");
70     }
71     else {
72     sensorValue = sensorValue*0.718;      
73     Serial.print(sensorValue);
74     Serial.println("cm");
75     }
76   } 
77 }
