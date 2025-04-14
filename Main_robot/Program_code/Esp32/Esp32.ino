int sign(int x){
  if (x > 0) return 1;
  else if (x < 0) return -1;
  else return 0;
}

#include <PS4Controller.h>

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
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");
}

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
  eng1_F = ((pow((pow((x4-eng_x_1), 2) + pow((y4-eng_y_1), 2)), 0.5)) / L);// * sign(stic_y - ((axis_y2_1-axis_y1_1)*(((axis_x2_1-axis_x1_1)*(axis_y2_1-axis_y1_1)*(stic_y-axis_y1_1)+axis_x1_1*pow(axis_y2_1-axis_y1_1, 2)+stic_x*pow(axis_x2_1-axis_x1_1, 2))/(pow(axis_y2_1-axis_y1_1, 2)+pow(axis_x2_1-axis_x1_1, 2))-axis_x1_1)/(axis_x2_1-axis_x1_1)+axis_y1_1));

  x5=((sec_wheels_x2_2-sec_wheels_x1_2)*(sec_wheels_y2_2-sec_wheels_y1_2)*(stic_y-sec_wheels_y1_2)+sec_wheels_x1_2*pow(sec_wheels_y2_2-sec_wheels_y1_2, 2)+stic_x*pow(sec_wheels_x2_2-sec_wheels_x1_2, 2))/(pow(sec_wheels_y2_2-sec_wheels_y1_2, 2)+pow(sec_wheels_x2_2-sec_wheels_x1_2, 2));
  y5=(sec_wheels_y2_2-sec_wheels_y1_2)*(x5-sec_wheels_x1_2)/(sec_wheels_x2_2-sec_wheels_x1_2)+sec_wheels_y1_2;
  eng2_F = ((pow((pow((x5-eng_x_2), 2) + pow((y5-eng_y_2), 2)), 0.5)) / L) * sign(stic_y - ((axis_y2_2-axis_y1_2)*(((axis_x2_2-axis_x1_2)*(axis_y2_2-axis_y1_2)*(stic_y-axis_y1_2)+axis_x1_2*pow(axis_y2_2-axis_y1_2, 2)+stic_x*pow(axis_x2_2-axis_x1_2, 2))/(pow(axis_y2_2-axis_y1_2, 2)+pow(axis_x2_2-axis_x1_2, 2))-axis_x1_2)/(axis_x2_2-axis_x1_2)+axis_y1_2));

  x6=((sec_wheels_x2_3-sec_wheels_x1_3)*(sec_wheels_y2_3-sec_wheels_y1_3)*(stic_y-sec_wheels_y1_3)+sec_wheels_x1_3*pow(sec_wheels_y2_3-sec_wheels_y1_3, 2)+stic_x*pow(sec_wheels_x2_3-sec_wheels_x1_3, 2))/(pow(sec_wheels_y2_3-sec_wheels_y1_3, 2)+pow(sec_wheels_x2_3-sec_wheels_x1_3, 2));
  y6=(sec_wheels_y2_3-sec_wheels_y1_3)*(x6-sec_wheels_x1_3)/(sec_wheels_x2_3-sec_wheels_x1_3)+sec_wheels_y1_3;
  eng3_F = ((pow((pow((x6-eng_x_2), 2) + pow((y6-eng_y_2), 2)), 0.5)) / L) * sign(stic_x - (axis_x2_2-axis_x1_2)*(axis_y2_2-axis_y1_2)*(stic_y-axis_y1_2)+axis_x1_2*pow(axis_y2_2-axis_y1_2, 2)+stic_x*pow(axis_x2_2-axis_x1_2, 2))/(pow(axis_y2_2-axis_y1_2, 2)+pow(axis_x2_2-axis_x1_2, 2));

  Serial.println(stic_x);
  Serial.println(stic_y);
  /*Serial.println(x6);
  Serial.println(y6);*/
  Serial.println(eng1_F);
}