// подключаем стандартную библиотеку LiquidCrystal
#include <LiquidCrystal.h>
 
// инициализируем объект-экран, передаём использованные 
// для подключения контакты на Arduino в порядке:
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(53, 51, 49, 47, 45, 43);

int value = 0;
 
void setup() {
  // устанавливаем размер (количество столбцов и строк) экрана
  lcd.begin(8, 2);
  // печатаем первую строку
  lcd.print("\xA5O\x48  ION");
  // устанавливаем курсор в колонку 0, строку 1
  // на самом деле это вторая строка, т.к. нумерация начинается с нуля
  lcd.setCursor(0, 1);
  // печатаем вторую строку
  lcd.print("   ");
  lcd.print(value);
}
 
void loop() {
  for (int i = 0; i < 60; i++){
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.print(i);
    delay(100);
  }
}