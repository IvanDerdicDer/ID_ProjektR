// Core library for code-sense - IDE-based
#   include "Energia.h"


// Include application, user and local libraries
#include "rtosGlobals.h"
#include "Clock.h"
#include <stdint.h>

#define RED     0xff0000
#define GREEN   0x00ff00
#define BLUE    0x0000ff
#define BLACK   0x0
#define WHITE   0xffffff

#define MAX_NUMBER_OF_THREADS 4

enum threads{T0, T1, T2, T3};

Clock myClock;
uint8_t currentThread = T0, nextThread = T0;
uint32_t threadAllotedTime[MAX_NUMBER_OF_THREADS], threadColors[] = {RED, GREEN, BLUE, WHITE}, toParse; // Array of times alloted to a thread in ms

void analogWriteRGB(uint32_t rgb){
    analogWrite(RED_LED,    (rgb >> 16) & 0xff);
    analogWrite(GREEN_LED,  (rgb >>  8) & 0xff);
    analogWrite(BLUE_LED,   (rgb >>  0) & 0xff);
}

void errorCode(uint8_t thread){
    /*
     * Error in this context means thats a thread has been executing longer than its alloted time.
     * In the case of that happening the whole code halts and the error code is shown on the RGB LED.
     * Error code is a color generated depending on the ID of the running thread
     *
     * thread: a number between [0, MAX_NUMBER_OF_THREADS>
     * The first 3 bits determine the error code by selecting which color shows on the RGB LED.
     * 0xb00000000
     *         |||
     *         vvv
     *         RGB
     *
     */

     uint32_t color = 0;

     if(thread & 1){
         color |= 0xff <<  0;
     }

     if(thread & 2){
         color |= 0xff <<  8;
     }

     if(thread & 4){
         color |= 0xff << 16;
     }

     analogWriteRGB(color);
}

void clockFunction()
{
    errorCode(currentThread);
    exit(-1);
}

void testFunc(void* timeIn){
    uint32_t time = *((uint32_t*)timeIn);
    analogWriteRGB(threadColors[currentThread]);
    delay(time);
    analogWriteRGB(BLACK);
    delay(time);
}

void runDeterministicThread(void (*function)(void*), void* arg){
    myClock.begin(clockFunction, threadAllotedTime[currentThread], 0);
    myClock.start();
    (*function)(arg);
    myClock.stop();
}

// Add setup code
void setup()
{
    //myClock.begin(clockFunction, initialPeriod, repeatedPeriod); // 1000 ms = 1 s
    //myClock.start();
    for(uint8_t i = 0; i < MAX_NUMBER_OF_THREADS; i++){
        threadAllotedTime[i] = (300 + 200 * i) * 2;
    }
    
}

// Add loop code
void loop()
{
    currentThread = nextThread;

    switch(currentThread){
    case T0:
        toParse = threadAllotedTime[currentThread] / 2 - 1;
        runDeterministicThread(testFunc, &toParse);
        nextThread = T1;
        break;
    case T1:
        toParse = threadAllotedTime[currentThread] / 2 - 10;
        runDeterministicThread(testFunc, &toParse);
        nextThread = T2;
        break;
    case T2:
        toParse = threadAllotedTime[currentThread] / 2 - 10;
        runDeterministicThread(testFunc, &toParse);
        nextThread = T3;
        break;
    case T3:
        toParse = threadAllotedTime[currentThread] / 2 - 10;
        runDeterministicThread(testFunc, &toParse);
        nextThread = T0;
        break;
    }
}

