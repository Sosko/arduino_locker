char keyGet() {
  T2i = 0;
  lcdLI();
  return keypad.getKey();
}
