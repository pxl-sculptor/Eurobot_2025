#include <Wire.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 24

int eng1Pin1 = 4, eng1Pin2 = 5;
int eng2Pin1 = 2, eng2Pin2 = 3;
int eng3Pin1 = 9, eng3Pin2 = 8;

int eng1_dir, eng2_dir, eng3_dir;
float eng1_F, eng2_F, eng3_F;
bool newDataAvailable = false;  // Флаг новых данных

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveData);

  pinMode(eng1Pin1, OUTPUT);
  pinMode(eng1Pin2, OUTPUT);
  pinMode(eng2Pin1, OUTPUT);
  pinMode(eng2Pin2, OUTPUT);
  pinMode(eng3Pin1, OUTPUT);
  pinMode(eng3Pin2, OUTPUT);

}
void loop() {
  if (newDataAvailable) {
    //Serial.println(eng1_dir);
    digitalWrite(eng1Pin1, eng1_dir);
    analogWrite(eng1Pin2, eng1_F);

    digitalWrite(eng2Pin1, eng2_dir);
    analogWrite(eng2Pin2, eng2_F);

    digitalWrite(eng3Pin1, eng3_dir);
    analogWrite(eng3Pin2, eng3_F);
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
    Serial.println(eng1_F);

    newDataAvailable = true;
  }
}