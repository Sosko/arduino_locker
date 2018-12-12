void lcdInit() {
  Serial.println("LCD init");
  lcd.init();
  lcd.init();
  lcdLI();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Init ");
}

void lcdp(String text) {
  lcd.print(text);
}


void lcdl1(String text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
  lcd.setCursor(0, 1);
}

void lcdl2(String text) {
  lcd.setCursor(0, 1);
  lcd.print(text);
}
void lcdl2(char text) {
  lcd.print(text);
}

void lcdLO() {
  lcd.noBacklight();
}
void lcdLI() {
  lcd.backlight();
}
