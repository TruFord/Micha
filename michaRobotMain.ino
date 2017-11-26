#include "LedControl.h"
LedControl lc=LedControl(12,11,10,1);

void setup()
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

void neutral()
{
lc.setRow(0,0,60);
lc.setRow(0,1,126);
lc.setRow(0,2,102);
lc.setRow(0,3,102);
lc.setRow(0,4,102);
lc.setRow(0,5,126);
lc.setRow(0,6,60);
lc.setRow(1,1,60);
lc.setRow(1,2,126);
lc.setRow(1,3,102);
lc.setRow(1,4,102);
lc.setRow(1,5,102);
lc.setRow(1,6,126);
lc.setRow(1,7,60);
delay(50);
}
