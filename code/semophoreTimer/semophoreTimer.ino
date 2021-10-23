
#include "Timer.h"

#define STATE1  0xff0000
#define STATE2  0xff00ff
#define STATE3  0x00ff00
#define STATE4  0xffff00

 Timer myTimer;

 int currentState = 0, nextState = 0, timePassed = 0;

void timerFunction()
{
    timePassed++;
}

void analogWriteRGB(int rgb){
    analogWrite(RED_LED,    (rgb >> (4 * 4)) & 0x11);
    analogWrite(GREEN_LED,  (rgb >> (2 * 4)) & 0x11);
    analogWrite(BLUE_LED,   (rgb >> (0 * 4)) & 0x11);
}

void setup()
{
    myTimer.begin(timerFunction, 1, 1000000);
    myTimer.start();
}

void loop() 
{
    currentState = nextState;
    switch(currentState){
        case 0:
            analogWriteRGB(STATE1);
            if(timePassed >= 10){
                nextState = 1;
                timePassed = 0;
            }
            break;
        case 1:
            analogWriteRGB(STATE2);
            if(timePassed >= 3){
                nextState = 2;
                timePassed = 0;
            }
            break;
        case 2:
            analogWriteRGB(STATE3);
            if(timePassed >= 8){
                nextState = 3;
                timePassed = 0;
            }
            break;
        case 3:
            analogWriteRGB(STATE4);
            if(timePassed >= 3){
                nextState = 0;
                timePassed = 0;
            }
            break;
    }
}
