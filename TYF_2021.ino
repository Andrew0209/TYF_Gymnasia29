

// Include the required Arduino libraries:
//подключение библиотек
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//ширина и высота экрана
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in 


OneWire sens1 (3);
OneWire sens2 (4);
DallasTemperature sensors_1(&sens1);
DallasTemperature sensors_2(&sens2);

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void pinssetup();
const int LedLeft_1 = 6;
const int LedLeft_2 = 5;
const int LedRight_1 = 16;
const int LedRight_2 = 15;
const int ButtonLeft = 11;
const int ButtonRight = 12;
const int DatLeft = 3;
const int DatRight = 4;
const bool LEDS_1 = 0;
const bool LEDS_2 = 0;


float tempC_1 = 0;
float tempC_2 = 0;

float temp1 = 0;
float temp2 = 0;

void setup() {

  Serial.begin(9600);//настройка сериал порта для обмена данными с компьтером
  sensors_1.begin();//начальная настройка датчиков
  sensors_2.begin();
  sensors_2.setResolution(12);//устанавливаем 12-ти битную разрядность(точность до сотых)
  sensors_1.setResolution(12);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32 - проверка экрана на подключение
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  pinssetup();
  display.clearDisplay();
  //задаём размер и цвет текста
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {


  sensors_1.requestTemperatures();
  sensors_2.requestTemperatures();
  tempC_1 = sensors_1.getTempCByIndex(0);
  tempC_2 = sensors_2.getTempCByIndex(0);
  //код для вывода на компьютер
  //  Serial.print("Left dat:");
  //  Serial.print(tempC_1);
  //  Serial.print("       Right dat:");
  //  Serial.println(tempC_2);

  if (!digitalRead(ButtonLeft)) {//фиксируем значение относительно которого считаем относительное по левому датчику
    temp1 = tempC_1;
    digitalWrite(LedLeft_1, 1);
    delay(200);
    digitalWrite(LedLeft_1, 0);
  }
  if (!digitalRead(ButtonRight)) {//фиксируем значение относительно которого считаем относительное по правому датчику
    temp2 = tempC_2;
    digitalWrite(LedRight_1, 1);
    delay(200);
    digitalWrite(LedRight_1, 0);
  }
  //вывод на экран
  display.setCursor(0, 0);
  display.print(tempC_1, 1);

  display.setCursor(64, 0);
  display.print((tempC_1 - temp1), 1);

  display.setCursor(0 , 17);
  display.print(tempC_2, 1);

  display.setCursor(64, 17);
  display.print((tempC_2 - temp2), 1);
  display.display();

  //отчистка экрана перед новым выводом
  display.clearDisplay();
}

void pinssetup() {
  //настройка пинов на выход
  pinMode(LedRight_2, OUTPUT);
  pinMode(LedRight_1, OUTPUT);
  pinMode(LedLeft_2, OUTPUT);
  pinMode(LedLeft_1, OUTPUT);

  //настройка пинов кнопок
  pinMode(ButtonRight, INPUT_PULLUP);
  pinMode(ButtonLeft, INPUT_PULLUP);
  
  //настройка пинов на вход
  pinMode(DatLeft, INPUT);
  pinMode(DatLeft, INPUT);
}
