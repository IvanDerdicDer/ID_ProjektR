#include <stdbool.h>

bool buttonState = 0;

void setup() {
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(BLUE_LED, OUTPUT);
}

void loop() {
  buttonState = digitalRead(PUSH2);
  if(!buttonState){
      digitalWrite(BLUE_LED, HIGH);
      delay(250);
      digitalWrite(BLUE_LED, LOW);
      delay(250);
  }
  digitalWrite(BLUE_LED, LOW);
}
