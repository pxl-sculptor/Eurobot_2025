#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 25

LiquidCrystal lcd(53, 51, 49, 47, 45, 43);

Servo servoL1;
Servo servoL2;

Servo servoM1;
Servo servoM2;

int relayPin = 26;
int eng1Pin1 = 4, eng1Pin2 = 5;
int eng2Pin1 = 8, eng2Pin2 = 9;
int eng3Pin1 = 6, eng3Pin2 = 7;
int liftPin1 = 2, liftPin2 = 3;

bool eng1_dir, eng2_dir, eng3_dir, lift_dir;
float eng1_F, eng2_F, eng3_F, lift_F;
bool newDataAvailable = false,  // Флаг новых данных
  magn, servoL, servoM,
     L_dir, R, value_flag_R = false, value_flag_L = false;

int angle_closeL1 = 20, angle_openL1 = 60, angle_closeL2 = 160, angle_openL2 = 120,
    angle_closeM1 = 0, angle_openM1 = 180, angle_closeM2 = 0, angle_openM2 = 180,
    value = 60;

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveData);

  lcd.begin(8, 2);
  lcd.print("\xA5O\x48  ION");

  servoL1.attach(10);
  servoL2.attach(11);
  servoL1.write(angle_openL1);
  servoL2.write(angle_openL2);

  servoM1.attach(22);
  servoM2.attach(24);
  servoM1.write(angle_openM1);
  servoM2.write(angle_openM2);

  pinMode(eng1Pin1, OUTPUT);
  pinMode(eng1Pin2, OUTPUT);
  pinMode(eng2Pin1, OUTPUT);
  pinMode(eng2Pin2, OUTPUT);
  pinMode(eng3Pin1, OUTPUT);
  pinMode(eng3Pin2, OUTPUT);
  pinMode(liftPin1, OUTPUT);
  pinMode(liftPin2, OUTPUT);


  pinMode(relayPin, OUTPUT);
}
void loop() {
  if (newDataAvailable) {
    Serial.println(value);

    if (L_dir and !value_flag_L) {
      value_flag_L = true;
      value -= 1;
    }
    if (!L_dir and value_flag_L) value_flag_L = false;

    if (R and !value_flag_R) {
      value_flag_R = true;
      value += 10;
    }
    if (!R and value_flag_R) value_flag_R = false;

    digitalWrite(eng1Pin1, eng1_dir);
    analogWrite(eng1Pin2, eng1_F);

    digitalWrite(eng2Pin1, eng2_dir);
    analogWrite(eng2Pin2, eng2_F);

    digitalWrite(eng3Pin1, eng3_dir);
    analogWrite(eng3Pin2, eng3_F);

    digitalWrite(liftPin1, lift_dir);
    analogWrite(liftPin2, lift_F);

    if (magn) digitalWrite(relayPin, 1);
    else digitalWrite(relayPin, 0);

    if (servoL) {
      servoL1.write(angle_closeL1);
      servoL2.write(angle_closeL2);
    } else {
      servoL1.write(angle_openL1);
      servoL2.write(angle_openL2);
    }

    if (servoM) {
      servoM1.write(angle_closeM1);
      servoM2.write(angle_closeM2);
    } else {
      servoM1.write(angle_openM1);
      servoM2.write(angle_openM2);
    }

    newDataAvailable = false;  // Сбрасываем флаг
  }

  lcd.setCursor(0, 1);
  lcd.print("   ");
  lcd.print(value);
  lcd.print("   ");

  delay(10);
}

void receiveData(int byteCount) {
  if (byteCount == DATA_SIZE) {
    byte buffer[DATA_SIZE];

    // Читаем все данные
    for (int i = 0; i < DATA_SIZE; i++) {
      buffer[i] = Wire.read();
    }
    memcpy(&eng1_dir, &buffer[0], 1);
    memcpy(&eng2_dir, &buffer[1], 1);
    memcpy(&eng3_dir, &buffer[2], 1);
    memcpy(&eng1_F, &buffer[3], 4);
    memcpy(&eng2_F, &buffer[7], 4);
    memcpy(&eng3_F, &buffer[11], 4);
    memcpy(&magn, &buffer[15], 1);
    memcpy(&servoL, &buffer[16], 1);
    memcpy(&servoM, &buffer[17], 1);
    memcpy(&lift_F, &buffer[18], 4);
    memcpy(&lift_dir, &buffer[22], 1);
    memcpy(&L_dir, &buffer[23], 1);
    memcpy(&R, &buffer[24], 1);
    Serial.println(L_dir);
    newDataAvailable = true;
  }
}