void lockInit() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
}

void openLock(int id) {
  int l;
  switch (id) {
    case 0:
      l = L1;
      break;
    case 1:
      l = L2;
      break;
    case 2:
      l = L3;
      break;
    case 3:
      l = L4;
      break;
  }
  digitalWrite(l, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2500);                     // wait for a second
  digitalWrite(l, LOW);    // turn the LED off by making the voltage LOW
}
