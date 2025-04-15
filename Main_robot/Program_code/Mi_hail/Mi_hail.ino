#include <PS4Controller.h>
#include <Servo.h>
#include <esp_bt_defs.h>

const int relayPins[] = {22, 23, 24, 25};
const int numRelays = 4;
boolean relayStates[4] = {LOW, LOW, LOW, LOW};
boolean bottonPressed = false;

PS4Controller ps4;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void setup() {
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    servo1.attach(26);
    servo2.attach(27);
    servo3.attach(28);
    servo4.attach(29);
    servo5.attach(30);
  }
}
void loop() {
  ps4.update();
  if (ps4.getButton(PS4_BUTTON_CROSS)) {
    relayStates[0] = !relayStates[0];
    digitalWrite(relayPins[0], relayStates[0]);
    delay(50);
  }

  if (ps4.getButton(PS4_BUTTON_CIRCLE)) {
    relayStates[1] = !relayStates[1];
    digitalWrite(relayPins[1], relayStates[1]);
    delay(50);
  }

  if (ps4.getButton(PS4_BUTTON_SQUARE)) {
    relayStates[2] = !relayStates[2];
    digitalWrite(relayPins[2], relayStates[2]);
    delay(50);
  }
  if (ps4.getButton(PS4_BUTTON_TRIANGLE)) {
    relayStates[3] = !relayStates[3];
    digitalWrite(relayPins[3], relayStates[3]);
    delay(50);
  }
  if (ps4.getButton(PS4_BUTTON_R1)) {
    servo1.write(0);
  }
  if (ps4.getButton(PS4_BUTTON_R2)) {
    servo1.write(90);
  }
  if (PS4.getButtonPress(PS4ButtonCross)) {
    if (!buttonPressed) {
      buttonPressed = true;
      servo5.write(0);
    } else {
      servo5.write(90);
    }
  }
}

