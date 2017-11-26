
// https://github.com/wayoda/LedControl LED Control Library
#include "LedControl.h"

//This setups the pins for the LED matrix - I know it works with one LED matrix but I haven't tested with two yet. 
// pin 12 is connected to the DataIn 
// pin 11 is connected to the CLK 
// pin 10 is connected to LOAD 
// We have only a single MAX72XX.
LedControl lc=LedControl(12,11,10,1);

void setup()

//LED MATRIX FOR EYES
{
lc.shutdown(0,false);
lc.setIntensity(0,1);
lc.clearDisplay(0);

lc.shutdown(1,false);
lc.setIntensity(1,1);
lc.clearDisplay(1);
}

void loop()
{
neutral();
}

