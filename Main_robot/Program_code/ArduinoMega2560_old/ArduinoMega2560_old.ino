#include <Wire.h>
#include <Servo.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 40

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int eng1Pin1 = 4, eng1Pin2 = 5;
int eng2Pin1 = 2, eng2Pin2 = 3;
int eng3Pin1 = 8, eng3Pin2 = 9;
int lift1Pin = 6, lift2Pin = 7;

int eng1_dir, eng2_dir, eng3_dir, lift_dir, angle_close = 90, angle_open = 180;
float eng1_F, eng2_F, eng3_F, lift_F;
bool newDataAvailable = false, servo_jar1, servo_jar2;

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveData);

  servo1.attach(28);
  servo2.attach(29);
  servo3.attach(23);
  servo4.attach(11);

  pinMode(eng1Pin1, OUTPUT);
  pinMode(eng1Pin2, OUTPUT);
  pinMode(eng2Pin1, OUTPUT);
  pinMode(eng2Pin2, OUTPUT);
  pinMode(eng3Pin1, OUTPUT);
  pinMode(eng3Pin2, OUTPUT);
}
void loop() {
  if (newDataAvailable) {
    digitalWrite(eng1Pin1, eng1_dir);
    analogWrite(eng1Pin2, eng1_F);

    digitalWrite(eng2Pin1, eng2_dir);
    analogWrite(eng2Pin2, eng2_F);

    digitalWrite(eng3Pin1, eng3_dir);
    analogWrite(eng3Pin2, eng3_F);

    /*digitalWrite(eng1Pin1, lift_dir);
    analogWrite(eng1Pin2, lift_F);

    if (servo_jar1) {
      servo1.write(angle_open);
      servo2.write(angle_open);
    } else {
      servo3.write(angle_close);
      servo4.write(angle_close);
    }*/

    newDataAvailable = false;  // Сбрасываем флаг
  }
  delay(10);
}

void receiveData(int byteCount) {
  if (byteCount == DATA_SIZE) {
    byte buffer[DATA_SIZE];

    // Читаем все данные
    for (int i = 0; i < DATA_SIZE; i++) {
      buffer[i] = Wire.read();
    }
    memcpy(&eng1_dir, &buffer[0], 4);
    memcpy(&eng2_dir, &buffer[4], 4);
    memcpy(&eng3_dir, &buffer[8], 4);
    memcpy(&eng1_F, &buffer[12], 4);
    memcpy(&eng2_F, &buffer[16], 4);
    memcpy(&eng3_F, &buffer[20], 4);
    memcpy(&buffer[24], &lift_F, 4);
    memcpy(&buffer[28], &lift_dir, 4);
    //memcpy(&buffer[32], &lift_F, 4);
    //memcpy(&buffer[36], &lift_F, 4);

    newDataAvailable = true;
  }
}