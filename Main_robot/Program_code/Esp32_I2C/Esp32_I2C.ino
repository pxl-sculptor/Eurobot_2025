#include <Wire.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 24  // 3 int × 4 + 3 float × 4 = 24 байта

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA=GPIO21, SCL=GPIO22
  Wire.setClock(100000);  // 100 kHz
  Serial.println("ESP32 I2C Master ready");
}

void loop() {
  // Пример данных для передачи
  int intData1 = 1234;
  int intData2 = -5678;
  int intData3 = 91011;
  
  float floatData1 = 3.1415;
  float floatData2 = -2.7182;
  float floatData3 = 1.6180;

  byte buffer[DATA_SIZE];
  
  // Упаковываем данные в буфер
  memcpy(&buffer[0], &intData1, 4);
  memcpy(&buffer[4], &intData2, 4);
  memcpy(&buffer[8], &intData3, 4);
  memcpy(&buffer[12], &floatData1, 4);
  memcpy(&buffer[16], &floatData2, 4);
  memcpy(&buffer[20], &floatData3, 4);

  // Отправка данных
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(buffer, DATA_SIZE);
  byte error = Wire.endTransmission();

  if (error == 0) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Transmission error: ");
    Serial.println(error);
  }

  delay(50);  // Задержка между передачами
}