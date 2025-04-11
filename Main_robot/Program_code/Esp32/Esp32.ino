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

int x, y;
void loop() 
{
  if (millis() - lastTimeStamp > 50)
  {
    lastTimeStamp = millis();
  }
  x = PS4.LStickX();
  y = PS4.LStickY();

  if(abs(x) <= 10) x = 0;
  if(abs(y) <= 10) y = 0;

  x = map(x, -127, 127, -255, 255);
  y = map(y, -127, 127, -255, 255);

  Serial.println(x);
  Serial.println(y);
}
