#include <Arduino.h>
/* SD Card setup
   51 - MOSI
   50 - MISO
   52 - CLK | SCK
   53 - CS
   53,51,52,50,
*/

void cardInit() {
  pp("\nInitializing SD card...");
  if (!SD.begin(chipSelect)) {
    p("initialization failed!");
    while (1);
  }
  p("initialization done.");
}

bool cardFile(String file) {
  if (SD.exists(file)) {
    p("Soubor " + file + " existije");
    return true;
  } else {
    p("Soubor " + file + " NEexistije");
    return false;
  }
}

void cardZastatDefault(String file) {
  File myFile;
  myFile = SD.open(file, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to " + file + "...");
    myFile.print("#:##:##\n");
    myFile.print("A:line 1:1111\n");
    myFile.print("B:line 2:222\n");
    myFile.print("C:line 3:33\n");
    myFile.print("D:line 4:4\n");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + file);
  }

}
File cardOpenFile(String file) {
  File myFile =  SD.open(file);
  if (myFile) {
    return myFile;
  }
  return File();
}
char cardGetChar(File myFile) {
  char r;
  do {
    r = cardReadChar(myFile);
  } while (!((r >= 32 && r <= 125 ) || r == '\n'));
  return r;
}
char cardReadChar(File myFile) {
  if (myFile.available()) {
    return myFile.read();
  } else {
    return ';';
  }
}

bool cardLoadData(String file) {
  if (cardFile(file)) {
    p("File exists");
    lcdl1(init3);
    return true;
  } else {
    lcdl1(init4);
    lcdl2(init5);
    cardZastatDefault(file);
    return cardLoadData(file);
  }
  return false;
}
