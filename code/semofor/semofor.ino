
void setup() {
  pinMode(RED_RGB, OUTPUT);
  pinMode(GREEN_RGB, OUTPUT);
  pinMode(BLUE_RGB, OUTPUT);

}

void loop() {
    digitalWrite(BLUE_RGB, LOW);
    digitalWrite(RED_RGB, HIGH);
    sleep(500);
    digitalWrite(RED_RGB, LOW);
    digitalWrite(GREEN_RGB, HIGH);
    sleep(500);
    digitalWrite(GREEN_RGB, LOW);
    digitalWrite(BLUE_RGB, HIGH);
    sleep(500);
}
