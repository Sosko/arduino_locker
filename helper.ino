void p(String text) {
  Serial.println(text);
}

void p(char text) {
  Serial.println(text);
}

void p(int text) {
  Serial.println(text);
}

void pp(String text) {
  Serial.print(text);
}

int selQ(char o, char* pole) {
  for (int x = 0; x < FINT; x++) {
    if (o == pole[x]) {
      lcdl1(_text[x]);
      odpoved = "";
      OTAZKA = x;
      return x;
    }
  }
  return -1;
}

void blk() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}

String removeLast(String text) {
  String ret = "";
  for (unsigned int x = 0; x < text.length()-1; x++) {
    ret += text[x];
  }
  return ret;

}
