int DIR(int x) {
  if (x >= 0) return 0;
  else if (x < 0) return 1;
}

int sign(int x) {
  if (x > 0) return 1;
  else if (x < 0) return -1;
  else return 0;
}

int max_3(int max, int b, int c) {
  if (b > max) max = b;
  if (c > max) max = c;
  return max;
}

int min_3(int min, int b, int c) {
  if (b < min) min = b;
  if (c < min) min = c;
  return min;
}

#include <PS4Controller.h>
#include <Wire.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 40

unsigned long lastTimeStamp = 0;

void onConnect() {
  Serial.println("Connected!.");
}

void onDisConnect() {
  Serial.println("Disconnected!.");
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);     // SDA=GPIO21, SCL=GPIO22
  Wire.setClock(50000);  // 100 kHz

  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");
}

bool flag_jar1 = false, flag_jar2 = false, servo_jar1 = false, servo_jar2 = false; 

int eng1_dir, eng2_dir, eng3_dir, lift_dir = 0, change;

float k = 0.7, eng1_F, eng2_F, eng3_F, lift_F = 0,
      x4, y4, x5, y5, x6, y6,
      L = 109.985226,
      axis_x1_1 = 109.985226, axis_y1_1 = -63.5, axis_x2_1 = -109.985226, axis_y2_1 = 63.5,
      axis_x1_2 = -109.985226, axis_y1_2 = -63.5, axis_x2_2 = 109.985226, axis_y2_2 = 63.5,
      axis_x1_3 = 0, axis_y1_3 = 127, axis_x2_3 = 0, axis_y2_3 = -127,
      stic_x, stic_y, lift_y,
      eng_x_1 = -54.992613, eng_y_1 = 31.75, eng_x_2 = 54.992613, eng_y_2 = 31.75, eng_x_3 = 0, eng_y_3 = -63.5,
      sec_wheels_x1_1 = -109.985226, sec_wheels_y1_1 = -63.5, sec_wheels_x2_1 = 0, sec_wheels_y2_1 = 127,
      sec_wheels_x1_2 = 109.985226, sec_wheels_y1_2 = -63.5, sec_wheels_x2_2 = 0, sec_wheels_y2_2 = 127,
      sec_wheels_x1_3 = -109.985226, sec_wheels_y1_3 = -63.5, sec_wheels_x2_3 = 109.985226, sec_wheels_y2_3 = -63.5;

void loop() {
  if (millis() - lastTimeStamp > 50) {
    lastTimeStamp = millis();
  }
  stic_x = PS4.LStickX();
  stic_y = PS4.LStickY();
  lift_y = PS4.RStickY();

  if (abs(stic_x) <= 10) stic_x = 0;
  if (abs(stic_y) <= 10) stic_y = 0;
  if (abs(lift_y) <= 30) stic_y = 0;

  // Просчёт стрэйфа
  //==================================================================== Первый двигатель
  x4 = ((sec_wheels_x2_1 - sec_wheels_x1_1) * (sec_wheels_y2_1 - sec_wheels_y1_1) * (stic_y - sec_wheels_y1_1) + sec_wheels_x1_1 * pow(sec_wheels_y2_1 - sec_wheels_y1_1, 2) + stic_x * pow(sec_wheels_x2_1 - sec_wheels_x1_1, 2)) / (pow(sec_wheels_y2_1 - sec_wheels_y1_1, 2) + pow(sec_wheels_x2_1 - sec_wheels_x1_1, 2));
  y4 = (sec_wheels_y2_1 - sec_wheels_y1_1) * (x4 - sec_wheels_x1_1) / (sec_wheels_x2_1 - sec_wheels_x1_1) + sec_wheels_y1_1;
  eng1_F = (((pow((pow((x4 - eng_x_1), 2) + pow((y4 - eng_y_1), 2)), 0.5)) / L)) * 255 * sign(stic_y - ((axis_y2_1 - axis_y1_1) * (((axis_x2_1 - axis_x1_1) * (axis_y2_1 - axis_y1_1) * (stic_y - axis_y1_1) + axis_x1_1 * pow(axis_y2_1 - axis_y1_1, 2) + stic_x * pow(axis_x2_1 - axis_x1_1, 2)) / (pow(axis_y2_1 - axis_y1_1, 2) + pow(axis_x2_1 - axis_x1_1, 2)) - axis_x1_1) / (axis_x2_1 - axis_x1_1) + axis_y1_1));
  //==================================================================== Второй двигатель
  x5 = ((sec_wheels_x2_2 - sec_wheels_x1_2) * (sec_wheels_y2_2 - sec_wheels_y1_2) * (stic_y - sec_wheels_y1_2) + sec_wheels_x1_2 * pow(sec_wheels_y2_2 - sec_wheels_y1_2, 2) + stic_x * pow(sec_wheels_x2_2 - sec_wheels_x1_2, 2)) / (pow(sec_wheels_y2_2 - sec_wheels_y1_2, 2) + pow(sec_wheels_x2_2 - sec_wheels_x1_2, 2));
  y5 = (sec_wheels_y2_2 - sec_wheels_y1_2) * (x5 - sec_wheels_x1_2) / (sec_wheels_x2_2 - sec_wheels_x1_2) + sec_wheels_y1_2;
  eng2_F = (((pow((pow((x5 - eng_x_2), 2) + pow((y5 - eng_y_2), 2)), 0.5)) / L)) * 255 * sign(stic_y - ((axis_y2_2 - axis_y1_2) * (((axis_x2_2 - axis_x1_2) * (axis_y2_2 - axis_y1_2) * (stic_y - axis_y1_2) + axis_x1_2 * pow(axis_y2_2 - axis_y1_2, 2) + stic_x * pow(axis_x2_2 - axis_x1_2, 2)) / (pow(axis_y2_2 - axis_y1_2, 2) + pow(axis_x2_2 - axis_x1_2, 2)) - axis_x1_2) / (axis_x2_2 - axis_x1_2) + axis_y1_2));
  //==================================================================== Третий двигатель
  x6 = ((sec_wheels_x2_3 - sec_wheels_x1_3) * (sec_wheels_y2_3 - sec_wheels_y1_3) * (stic_y - sec_wheels_y1_3) + sec_wheels_x1_3 * pow(sec_wheels_y2_3 - sec_wheels_y1_3, 2) + stic_x * pow(sec_wheels_x2_3 - sec_wheels_x1_3, 2)) / (pow(sec_wheels_y2_3 - sec_wheels_y1_3, 2) + pow(sec_wheels_x2_3 - sec_wheels_x1_3, 2));
  y6 = (sec_wheels_y2_3 - sec_wheels_y1_3) * (x6 - sec_wheels_x1_3) / (sec_wheels_x2_3 - sec_wheels_x1_3) + sec_wheels_y1_3;
  eng3_F = (((pow((pow((x6 - eng_x_3), 2) + pow((y6 - eng_y_3), 2)), 0.5)) / L)) * 255 * sign(stic_x - axis_x1_3);

  // Просчёт мёртвой зоны джойстика
  if (eng1_F > 255) eng1_F = 255;
  if (eng2_F > 255) eng2_F = 255;
  if (eng3_F > 255) eng3_F = 255;
  if (eng1_F < -255) eng1_F = -255;
  if (eng2_F < -255) eng2_F = -255;
  if (eng3_F < -255) eng3_F = -255;

  // Просчёт поворота
  //==================================================================== Правый поворот
  if (PS4.R1()) {
    eng1_F *= k;
    eng2_F *= k;
    eng3_F *= k;

    change = max_3(-255 - eng1_F, -255 - eng2_F, -255 - eng2_F);

    eng1_F += change;
    eng2_F += change;
    eng3_F += change;
    eng1_F *= -1;
  }
  //==================================================================== Левый поворот
  else if (PS4.L1()) {
    eng1_F *= k;
    eng2_F *= k;
    eng3_F *= k;

    change = min_3(255 - eng1_F, 255 - eng2_F, 255 - eng2_F);

    eng1_F += change;
    eng2_F += change;
    eng3_F += change;
    eng1_F *= -1;
  }

  // Просчёт направления движения
  eng1_dir = DIR(eng1_F);
  eng2_dir = DIR(eng2_F);
  eng3_dir = DIR(eng3_F);

  eng1_F *= sign(eng1_F);
  eng2_F *= sign(eng2_F);
  eng3_F *= sign(eng3_F);

  if (eng1_dir) eng1_F = map(eng1_F, 0, 255, 255, 0);
  if (eng2_dir) eng2_F = map(eng2_F, 0, 255, 255, 0);
  if (eng3_dir) eng3_F = map(eng3_F, 0, 255, 255, 0);

  // Логика подъёмника
  lift_F = map(lift_y, -127, 127, -255, 255);
  lift_dir = DIR(lift_F);
  lift_F *= sign(lift_F);
  if (lift_dir) lift_F = map(lift_F, 0, 255, 255, 0);

  // Логика захватов
  //==================================================================== Первый захват
  if (PS4.R1() and !flag_jar1) {
    servo_jar1 = !servo_jar1;
    flag_jar1 = true;
  }
  if (!PS4.R1() and flag_jar1) {
    servo_jar1 = !servo_jar1;
    flag_jar1 = true;
  }
  //==================================================================== Второй захват
  if (PS4.L1() and !flag_jar2) {
    servo_jar2 = !servo_jar2;
    flag_jar2 = true;
  }
  if (!PS4.L1() and flag_jar2) {
    servo_jar2 = !servo_jar2;
    flag_jar2 = true;
  }

  Serial.println(lift_F);
  //Serial.println(eng1_F);

  // Отправка данных
  byte buffer[DATA_SIZE];

  memcpy(&buffer[0], &eng1_dir, 4);
  memcpy(&buffer[4], &eng2_dir, 4);
  memcpy(&buffer[8], &eng3_dir, 4);
  memcpy(&buffer[12], &eng1_F, 4);
  memcpy(&buffer[16], &eng2_F, 4);
  memcpy(&buffer[20], &eng3_F, 4);
  memcpy(&buffer[24], &lift_F, 4);
  memcpy(&buffer[28], &lift_dir, 4);
  //memcpy(&buffer[32], &lift_F, 4);
  //memcpy(&buffer[36], &lift_F, 4);

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(buffer, DATA_SIZE);
  byte error = Wire.endTransmission();

  delay(100);
}