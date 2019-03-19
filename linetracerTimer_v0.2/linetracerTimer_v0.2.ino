// Подключаем библиотеку для работы с жидкокристаллическим
// экраном (англ. Liquid Crystal Display или просто LCD)
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10,  9,  8);

unsigned long start_time = 0;
unsigned long stop_time = 0;
unsigned long finish_time = 0;
boolean start_flag = false;
volatile boolean sensor_flag = false;

void setup()
{
  pinMode(A0, INPUT);
  // начинаем работу с экраном. Сообщаем объекту количество
  // строк и столбцов. Опять же, вызывать pinMode не требуется:
  // функция begin сделает всё за нас
  lcd.begin(16, 2);
  // печатаем сообщение на первой строке
  lcd.setCursor(3, 0);
  lcd.print("Linetracer");
  lcd.setCursor(2, 1);
  lcd.print("Finish timer");
  delay(5000);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Finish time");
  lcd.setCursor(10, 1);
  lcd.print("sec");
  lcd.setCursor(5, 1);
  lcd.print(0.0, 1);
  attachInterrupt(0, timer, FALLING);
}

void loop()
{
  if (!start_flag and sensor_flag) {
    start_flag = true;
    sensor_flag = false;
    start_time = millis();
    stop_time = millis();
  }
  if (start_flag) {
    lcd.setCursor(5, 1);
    lcd.print((millis() - start_time) / 1000.0, 1);
  }

  if (start_flag and sensor_flag) {
    start_flag = false;
    sensor_flag = false;
    finish_time = millis() - start_time;
    //########### Ваш результат #################
    lcd.setCursor(1, 0);
    lcd.print(" ");
    stop_time = millis();
    while (!sensor_flag) {
      lcd.setCursor(5, 1);
      lcd.print(finish_time / 1000.0, 1);
      delay(500);
      lcd.setCursor(5, 1);
      lcd.print("     ");
      delay(500);
    } 
  }
}

void timer() {
  if(millis() - stop_time < 5000){
    sensor_flag = false;
  }else{
    sensor_flag = true;
  }
  
}
