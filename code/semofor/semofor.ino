#include <stdint.h>
#include <timer_a.h>

#define STATE1  0xff0000
#define STATE2  0xff00ff
#define STATE3  0x00ff00
#define STATE4  0xffff00

enum semaphoreStates{R, RY, G, Y};

int32_t currentState = R, nextState = R;
uint32_t timeStart;

void analogWriteRGB(int rgb){
    analogWrite(RED_LED,    (rgb >> (4 * 4)) & 0x11);
    analogWrite(GREEN_LED,  (rgb >> (2 * 4)) & 0x11);
    analogWrite(BLUE_LED,   (rgb >> (0 * 4)) & 0x11);
}

void setNextState(){
    nextState = (nextState + 1) % 4;
    Timer_A_clearInterruptFlag(TIMER_A0_BASE);
}

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  Timer_A_UpModeConfig timerConf;
  timerConf.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_48;
  timerConf.timerPeriod = 5;
  timerConf.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;

  Timer_A_configureUpMode(TIMER_A0_BASE, &timerConf);
  Timer_A_registerInterrupt(TIMER_A0_BASE, TIMER_A_CCR0_INTERRUPT, setNextState);
}

void loop() {
    switch(currentState){
        case R:
            analogWriteRGB(STATE1);
            if(millis() - timeStart >= 5000){
                nextState = RY;
                timeStart = millis();
            }
            break;
        case RY:
            analogWriteRGB(STATE2);
            if(millis() - timeStart >= 1000){
                nextState = G;
                timeStart = millis();
            }
            break;
        case G:
            analogWriteRGB(STATE3);
            if(millis() - timeStart >= 5000){
                nextState = Y;
                timeStart = millis();
            }
            break;
        case Y:
            analogWriteRGB(STATE4);
            if(millis() - timeStart >= 1000){
                nextState = R;
                timeStart = millis();
            }
            break;
    }
}
