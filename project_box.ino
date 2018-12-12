#include <Arduino.h>
// Card Library
#include <SPI.h>
#include <SD.h>
//Keyboard
#include <Keypad.h>
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//??
volatile byte state = LOW;
const int T2I = 300;
int T2i = 0;

//SD variables
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 53;

//Keypad
//Keyboard variables
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {30, 32, 34, 36}; //connect to the column pinouts of the keypad
//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Display 0x3F
LiquidCrystal_I2C lcd(0x3F, 20, 4);
//Locks
const int L1 = 2;
const int L2 = 3;
const int L3 = 4;
const int L4 = 5;

//VARIABLES
String FFILE = "hra.txt";
int FINT = 4;
char _otazky[4] = {'X', 'X', 'X', 'X'};
String _text[4] = {"", "", "", ""};
String _kod[4] = {"", "", "", ""};
int _pokusy[4] = {0, 0, 0, 0};
int q, OTAZKA;
String odpoved = "";
char a;
/* LANG */
String init1 = "Nacitam...             ";
String init2 = "Nacteno OK             ";
String init3 = "Soubor existuje        ";
String init4 = "Soubor neexistuje      ";
String init5 = "Zapisuji vychozi       ";
String line1 = "Vyberte otazku:        ";
String line2 = "Spravne                ";
String line3 = "Spatne                 ";
/* LANG */

ISR(TIMER2_OVF_vect) {
  T2i++;
  if (T2i >= T2I) {
    T2i = 0;
    lcdLO();
  }
}

void setup() {
  // Console
  Serial.begin(9600);
  //LCD
  lcdInit();
  //Digit out
  lockInit();
  //Card
  cardInit();
  //File in card
  cardLoadFile();
  //report to display
  lcdl1(init2);
  //Wait
  delay(500);
  //Timer2
  TIMSK2 = (TIMSK2 & B11111110) | 0x01;
  TCCR2B = (TCCR2B & B11111000) | 0x07;
}

void loop() {
  // put your main code here, to run repeatedly:
  //char a = klavesnice.read();
  lcdl1(line1);
  do {
    a = keyGet();
    q = selQ(a, _otazky);
  } while (q < 0);
  while (true) {
    a = keyGet();
    q = selQ(a, _otazky);
    if (a && q < 0) {
      if (a >= '0' && a <= '9') {
        odpoved += a;
        lcdl2(a);
      } else if (a == '*') {
        if (odpoved.length() > 0) {
          odpoved = removeLast(odpoved);
          lcdl2("                         ");
          lcdl2(odpoved);
        }
      } else if (a == '#') {
        if (odpoved.equals(_kod[OTAZKA])) {
          lcdl2(line2);
          odpoved = "";
          openLock(OTAZKA);
          return;
        } else {
          lcdl2(line3);
          delay(2000);
          lcdl2("                         ");
          lcdl2(odpoved);
        }
      }
    }
  }
}
