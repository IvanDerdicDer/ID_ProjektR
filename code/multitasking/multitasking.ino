#include<stdint.h>

#define RED     0xff0000
#define GREEN   0x00ff00
#define BLUE    0x0000ff

int color = RED;

void toGreen(){
    color = GREEN;
}

void toBlue(){
    color = BLUE;
}

void initRGBLED(){
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
}

void initButtons(){
    pinMode(PUSH1, INPUT_PULLUP);
    pinMode(PUSH2, INPUT_PULLUP);
}

void initInterrupts(){
    attachInterrupt(digitalPinToInterrupt(PUSH1), toBlue, FALLING);
    attachInterrupt(digitalPinToInterrupt(PUSH2), toGreen, FALLING);
}

void analogWriteRGB(uint32_t rgb){
    analogWrite(RED_LED,    (rgb >> 16) & 0xff);
    analogWrite(GREEN_LED,  (rgb >>  8) & 0xff);
    analogWrite(BLUE_LED,   (rgb >>  0) & 0xff);
}


void setup() {
    initRGBLED();
    initButtons();
    initInterrupts();
}

void loop() {
    analogWriteRGB(color);
    delay(500);
    analogWriteRGB(0);
    delay(500);
}
