#include <Wire.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 24  // 3 int × 4 + 3 float × 4 = 24 байта

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveData);
  Serial.println("Mega I2C Slave ready");
}

void loop() {
  delay(100);
}

void receiveData(int byteCount) {
  if (byteCount == DATA_SIZE) {
    byte buffer[DATA_SIZE];
    
    // Читаем все данные
    for (int i = 0; i < DATA_SIZE; i++) {
      buffer[i] = Wire.read();
    }
    
    // Извлекаем int значения
    int int1, int2, int3;
    memcpy(&int1, &buffer[0], 4);
    memcpy(&int2, &buffer[4], 4);
    memcpy(&int3, &buffer[8], 4);
    
    // Извлекаем float значения
    float float1, float2, float3;
    memcpy(&float1, &buffer[12], 4);
    memcpy(&float2, &buffer[16], 4);
    memcpy(&float3, &buffer[20], 4);
  }

}