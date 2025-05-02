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

int max_4(int max, int a, int b, int c) {
  if (a > max) max = a;
  if (b > max) max = b;
  if (c > max) max = c;
  return max;
}

int min_4(int min, int a, int b, int c) {
  if (a < min) min = a;
  if (b < min) min = b;
  if (c < min) min = c;
  return min;
}

#include <PS4Controller.h>
#include <Wire.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 25

unsigned long lastTimeStamp = 0;

int change, max_F;

bool eng1_dir, eng2_dir, eng3_dir, lift_dir,
  magn = false, magn_flag = false,
  servoL = false, servoL_flag = false,
  servoM = false, servoM_flag = false,
  L_dir, R;

float k = 0.8,
      eng1_F, eng2_F, eng3_F, lift_F, x4, y4, x5, y5, x6, y6,
      L = 109.985226,
      axis_x1_1 = 109.985226, axis_y1_1 = -63.5, axis_x2_1 = -109.985226, axis_y2_1 = 63.5,
      axis_x1_2 = -109.985226, axis_y1_2 = -63.5, axis_x2_2 = 109.985226, axis_y2_2 = 63.5,
      axis_x1_3 = 0, axis_y1_3 = 127, axis_x2_3 = 0, axis_y2_3 = -127,
      stic_x, stic_y, lift,
      eng_x_1 = -54.992613, eng_y_1 = 31.75, eng_x_2 = 54.992613, eng_y_2 = 31.75, eng_x_3 = 0, eng_y_3 = -63.5,
      sec_wheels_x1_1 = -109.985226, sec_wheels_y1_1 = -63.5, sec_wheels_x2_1 = 0, sec_wheels_y2_1 = 127,
      sec_wheels_x1_2 = 109.985226, sec_wheels_y1_2 = -63.5, sec_wheels_x2_2 = 0, sec_wheels_y2_2 = 127,
      sec_wheels_x1_3 = -109.985226, sec_wheels_y1_3 = -63.5, sec_wheels_x2_3 = 109.985226, sec_wheels_y2_3 = -63.5;

void onConnect() {
  Serial.println("Connected!.");
}

void onDisConnect() {
  Serial.println("Disconnected!.");
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);     // SDA=GPIO21, SCL=GPIO22
  Wire.setClock(100000);  // 100 kHz

  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");
}



void loop() {
  if (millis() - lastTimeStamp > 50) lastTimeStamp = millis();

  L_dir = PS4.L2();
  R = PS4.R2();

  stic_x = PS4.LStickX();
  stic_y = PS4.LStickY();
  lift = PS4.RStickY();

  if (abs(stic_x) <= 10) stic_x = 0;
  if (abs(stic_y) <= 10) stic_y = 0;
  if (abs(lift) <= 10) lift = 0;
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


    change = max_3(-200 - eng1_F, -200 - eng2_F, -200 - eng2_F);

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

    change = min_3(200 - eng1_F, 200 - eng2_F, 200 - eng2_F);

    eng1_F += change;
    eng2_F += change;
    eng3_F += change;
    eng1_F *= -1;
  }

  lift_F = map(lift, -127, 127, -255, 255);
  if (lift_F < -255) lift_F = -255;
  Serial.println(lift_F);
  // Просчёт направления движения
  eng1_dir = DIR(eng1_F);
  eng2_dir = DIR(eng2_F);
  eng3_dir = DIR(eng3_F);
  lift_dir = DIR(lift_F);

  eng1_F *= sign(eng1_F);
  eng2_F *= sign(eng2_F);
  eng3_F *= sign(eng3_F);
  lift_F *= sign(lift_F);

  if (eng1_dir) eng1_F = map(eng1_F, 0, 255, 255, 0);
  if (eng2_dir) eng2_F = map(eng2_F, 0, 255, 255, 0);
  if (eng3_dir) eng3_F = map(eng3_F, 0, 255, 255, 0);
  if (lift_dir) lift_F = map(lift_F, 0, 255, 255, 0);

  // Логика захватов
  //==================================================================== Магниты с подсветкой
  if (PS4.Square() and !magn_flag) {
    magn = !magn;
    magn_flag = true;
  }
  if (!PS4.Square() and magn_flag) magn_flag = false;
  //==================================================================== Сервы
  if (PS4.Circle() and !servoL_flag) {
    servoL = !servoL;
    servoL_flag = true;
  }
  if (!PS4.Circle() and servoL_flag) servoL_flag = false;

  if (PS4.Cross() and !servoM_flag) {
    servoM = !servoM;
    servoM_flag = true;
  }
  if (PS4.Cross() and servoM_flag) servoM_flag = false;

  // Отправка данных
  byte buffer[DATA_SIZE];

  memcpy(&buffer[0], &eng1_dir, 1);
  memcpy(&buffer[1], &eng2_dir, 1);
  memcpy(&buffer[2], &eng3_dir, 1);
  memcpy(&buffer[3], &eng1_F, 4);
  memcpy(&buffer[7], &eng2_F, 4);
  memcpy(&buffer[11], &eng3_F, 4);
  memcpy(&buffer[15], &magn, 1);
  memcpy(&buffer[16], &servoL, 1);
  memcpy(&buffer[17], &servoM, 1);
  memcpy(&buffer[18], &lift_F, 4);
  memcpy(&buffer[22], &lift_dir, 1);
  memcpy(&buffer[23], &L_dir, 1);
  memcpy(&buffer[24], &R, 1);
  //memcpy(&buffer[17], &up, 1);
  //memcpy(&buffer[18], &down, 1);

  //Serial.println(lift_F);
  //Serial.println(lift_dir);

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(buffer, DATA_SIZE);
  byte error = Wire.endTransmission();
  delay(10);
}