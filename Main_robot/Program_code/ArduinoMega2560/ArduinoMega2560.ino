#include <Wire.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 24

int eng1Pin1 = , eng1Pin2 = ;
int eng2Pin1 = , eng2in2 = ;
int eng3Pin1 = , eng3Pin2 = ;

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

    memcpy(&buffer[0], &eng1_dir, 4);
    memcpy(&buffer[4], &eng2_dir, 4);
    memcpy(&buffer[8], &eng3_dir, 4);
    memcpy(&buffer[12], &eng1_F, 4);
    memcpy(&buffer[16], &eng2_F, 4);
    memcpy(&buffer[20], &eng3_F, 4);

    newDataAvailable = true;
  }