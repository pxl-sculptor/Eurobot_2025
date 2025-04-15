int DIR(int x){
  if (x >= 0) return 0;
  else if (x < 0) return 1;
}

#include <PS4Controller.h>
#include <Wire.h>

#define I2C_ADDRESS 0x08
#define DATA_SIZE 24

unsigned long lastTimeStamp = 0;

void onConnect(){
  Serial.println("Connected!.");
}

void onDisConnect(){
  Serial.println("Disconnected!.");    
}

void setup() 
{
  Serial.begin(115200);
  
  Wire.begin(21, 22);  // SDA=GPIO21, SCL=GPIO22
  Wire.setClock(100000);  // 100 kHz

  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");
}
int eng1_dir, eng2_dir, eng3_dir;

float eng1_F, eng2_F, eng3_F, x4, y4, x5, y5, x6, y6,
L = 109.985226, 
axis_x1_1 = 109.985226, axis_y1_1 = -63.5, axis_x2_1 = -109.985226, axis_y2_1 = 63.5,
axis_x1_2 = -109.985226, axis_y1_2 = -63.5, axis_x2_2 = 109.985226, axis_y2_2 = 63.5,
axis_x1_3 = 0, axis_y1_3 = 127, axis_x2_3 = 0, axis_y2_3 = -127,
stic_x, stic_y,
eng_x_1 = -54.992613, eng_y_1 = 31.75, eng_x_2 = 54.992613, eng_y_2 = 31.75, eng_x_3 = 0, eng_y_3 = -63.5,
sec_wheels_x1_1 = -109.985226, sec_wheels_y1_1 = -63.5, sec_wheels_x2_1 = 0, sec_wheels_y2_1 = 127,
sec_wheels_x1_2 = 109.985226, sec_wheels_y1_2 = -63.5, sec_wheels_x2_2 = 0, sec_wheels_y2_2 = 127,
sec_wheels_x1_3 = -109.985226, sec_wheels_y1_3 = -63.5, sec_wheels_x2_3 = 109.985226, sec_wheels_y2_3 = -63.5;

void loop() 
{
  if (millis() - lastTimeStamp > 50)
  {
    lastTimeStamp = millis();
  }
  stic_x = PS4.LStickX();
  stic_y = PS4.LStickY();

  if(abs(stic_x) <= 10) stic_x = 0;
  if(abs(stic_y) <= 10) stic_y = 0;

  x4=((sec_wheels_x2_1-sec_wheels_x1_1)*(sec_wheels_y2_1-sec_wheels_y1_1)*(stic_y-sec_wheels_y1_1)+sec_wheels_x1_1*pow(sec_wheels_y2_1-sec_wheels_y1_1, 2)+stic_x*pow(sec_wheels_x2_1-sec_wheels_x1_1, 2))/(pow(sec_wheels_y2_1-sec_wheels_y1_1, 2)+pow(sec_wheels_x2_1-sec_wheels_x1_1, 2));
  y4=(sec_wheels_y2_1-sec_wheels_y1_1)*(x4-sec_wheels_x1_1)/(sec_wheels_x2_1-sec_wheels_x1_1)+sec_wheels_y1_1;
  eng1_F = ((pow((pow((x4-eng_x_1), 2) + pow((y4-eng_y_1), 2)), 0.5)) / L);
  eng1_dir = DIR(stic_y - ((axis_y2_1-axis_y1_1)*(((axis_x2_1-axis_x1_1)*(axis_y2_1-axis_y1_1)*(stic_y-axis_y1_1)+axis_x1_1*pow(axis_y2_1-axis_y1_1, 2)+stic_x*pow(axis_x2_1-axis_x1_1, 2))/(pow(axis_y2_1-axis_y1_1, 2)+pow(axis_x2_1-axis_x1_1, 2))-axis_x1_1)/(axis_x2_1-axis_x1_1)+axis_y1_1));

  x5=((sec_wheels_x2_2-sec_wheels_x1_2)*(sec_wheels_y2_2-sec_wheels_y1_2)*(stic_y-sec_wheels_y1_2)+sec_wheels_x1_2*pow(sec_wheels_y2_2-sec_wheels_y1_2, 2)+stic_x*pow(sec_wheels_x2_2-sec_wheels_x1_2, 2))/(pow(sec_wheels_y2_2-sec_wheels_y1_2, 2)+pow(sec_wheels_x2_2-sec_wheels_x1_2, 2));
  y5=(sec_wheels_y2_2-sec_wheels_y1_2)*(x5-sec_wheels_x1_2)/(sec_wheels_x2_2-sec_wheels_x1_2)+sec_wheels_y1_2;
  eng2_F = ((pow((pow((x5-eng_x_2), 2) + pow((y5-eng_y_2), 2)), 0.5)) / L);
  eng2_dir = DIR(stic_y - ((axis_y2_2-axis_y1_2)*(((axis_x2_2-axis_x1_2)*(axis_y2_2-axis_y1_2)*(stic_y-axis_y1_2)+axis_x1_2*pow(axis_y2_2-axis_y1_2, 2)+stic_x*pow(axis_x2_2-axis_x1_2, 2))/(pow(axis_y2_2-axis_y1_2, 2)+pow(axis_x2_2-axis_x1_2, 2))-axis_x1_2)/(axis_x2_2-axis_x1_2)+axis_y1_2));

  x6=((sec_wheels_x2_3-sec_wheels_x1_3)*(sec_wheels_y2_3-sec_wheels_y1_3)*(stic_y-sec_wheels_y1_3)+sec_wheels_x1_3*pow(sec_wheels_y2_3-sec_wheels_y1_3, 2)+stic_x*pow(sec_wheels_x2_3-sec_wheels_x1_3, 2))/(pow(sec_wheels_y2_3-sec_wheels_y1_3, 2)+pow(sec_wheels_x2_3-sec_wheels_x1_3, 2));
  y6=(sec_wheels_y2_3-sec_wheels_y1_3)*(x6-sec_wheels_x1_3)/(sec_wheels_x2_3-sec_wheels_x1_3)+sec_wheels_y1_3;
  eng3_F = ((pow((pow((x6-eng_x_3), 2) + pow((y6-eng_y_3), 2)), 0.5)) / L);
  eng3_dir = DIR(axis_x1_3 - stic_x);

  if (eng1_F > 1) eng1_F = 1;
  if (eng2_F > 1) eng2_F = 1;
  if (eng3_F > 1) eng3_F = 1;

  byte buffer[DATA_SIZE];
  
  memcpy(&buffer[0], &eng1_dir, 4);
  memcpy(&buffer[4], &eng2_dir, 4);
  memcpy(&buffer[8], &eng3_dir, 4);
  memcpy(&buffer[12], &eng1_F, 4);
  memcpy(&buffer[16], &eng2_F, 4);
  memcpy(&buffer[20], &eng3_F, 4);

  // Отправка данных
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(buffer, DATA_SIZE);
  byte error = Wire.endTransmission();
}