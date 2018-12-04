#include <Arduino.h>
// Card Library
#include <SPI.h>
#include <SD.h>
//Keyboard
#include <Keypad.h>
//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


//SD variables
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 53;

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
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//Display 0x3F
LiquidCrystal_I2C lcd(0x3F, 20, 4);

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
String init1 = "Nacitam...";
String init2 = "Nacteno OK";
String init3 = "Soubor existuje";
String init4 = "Soubor neexistuje";
String init5 = "Zapisuji vychozi";
String line1 = "Vyberte otazku:";
String line2 = "Spravne                ";
String line3 = "Spatne                 ";
/* LANG */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  cardInit();
  lcdInit();
  char t;
  //
  if (cardLoadData(FFILE)) {
    lcdl2(init1);
    File file = cardOpenFile(FFILE);
    do {
      t = cardGetChar(file);
    } while (t != '\n');
    p("--------LD---------------");
    for (int x = 0; x < FINT; x++) {
      p("Loading of question");
      _otazky[x] = cardGetChar(file);
      cardGetChar(file); //:
      p("question text");
      while (true) {
        t = cardGetChar(file);
        if (t == ':') { //:
          break;
        }
        _text[x] += t;
      }
      p("correct key");
      while (true) {
        t = cardGetChar(file);
        if (!(t >= 48 && t <= 58)) {
          break;
        }
        _kod[x] += t;
      }
      p("Next question");
    }
    for (int x = 0; x < FINT; x++) {
      p("------------------");
      p(_otazky[x]);
      p(_text[x]);
      p(_kod[x]);
      p("------------------");
    }
  }
  lcdl1(init2);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  //char a = klavesnice.read();
  lcdl1(line1);
  do {
    a = keypad.getKey();
    q = selQ(a, _otazky);
  } while (q < 0);
  while (true) {
    a = keypad.getKey();
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
          for (int x = 0; x <= OTAZKA; x++) {
            blk();
          }
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
