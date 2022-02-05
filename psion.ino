const int bitpin[8] = {2,3,4,5,9,8,7,6};

void setup() {
  // initialize serial:
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {
    pinMode(bitpin[i], OUTPUT);
  }

  psion('\r');
  psion(0);

}

void loop() {
  static bool wantnl = false;
  char ch;
  
  while (Serial.available() > 0) {
    ch = Serial.read();
    Serial.print(ch);
    if (wantnl) {
      psion('\n'); psion(0);
      wantnl = false;
    }
    if (ch == '\n') {
      wantnl = true;
    } else {
      psion(ch); psion(0);
    }
  }
}

void linesleep() {
  delay(500);
}

void psion(int ch) {
  static int x = 0;

  if (ch == 0) { // no scroll
    
  } else if (ch == '\r') { // no scroll
    x = 0;
  } else if (ch == '\n') { // scroll
    linesleep();
    x = 0;
  } else {
    x++;
    if (x == 17) { // scroll
      linesleep();
      x = 1;
    }
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(bitpin[i], ch & (1<<i));
  }
  delay(20);
}
