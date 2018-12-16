char keyGet() {
  char c;
  c = keypad.getKey();
  if (c > 0) {
    T2i = 0;
    lcdLI();
  }
  if (T2i >= T2I) {
    T2i = 0;
    lcdLO();
  }
  return c;
}
