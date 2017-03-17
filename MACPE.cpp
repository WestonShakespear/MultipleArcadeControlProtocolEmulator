//Weston Shakespear
//MACPE Firmware
//SWATC C++ Final

//Ms. Pacman control setup

/* Todo:
 * - Fix coin door code
 * - Allow 3+ combos
 * - Add start, select, p1, p2
 

//Amount of coins received from player One and Two slots
int coins[2] = {0, 0};
int addr = 0;

//Pin assignments for controls
/*
 * 0: Coin Slot One
 * 1: Coin Slot Two
 * 2: Joystick Up
 * 3: Joystick Down
 * 4: Joystick Left
 * 5: Joystick Right
 * 6: Player One Button
 * 7: Player Two Button
 */
 //Default is {0, 1,2, 3, 4, 5, 6, 7}
int pins[8] = {0, 1, 2, 3, 4, 5, 6, 7};
unsigned long ticker[2] = {0};

unsigned long tick = 50;

bool activePins[8] = {false};

unsigned long delayMeasure[2][8] = {0};

int checkInput();
int readPins();
int initMeasure();
int initPins();
int displayPins();

void resetController();

void setup() {

  Serial.begin(9600);
  Serial.print("RESET");
  
  initPins();
  initMeasure();

}

void loop() {

  ticker[0] = millis();

  readPins();
  displayPins();
  checkInput();

  ticker[1] = millis();
  delay(tick - (ticker[1] - ticker[0]));

}

int checkInput() {


//Joystick
 if (activePins[2] == true && activePins[5] == true) {
  Keyboard.press(KEY_7);
 }
 else if (activePins[5] == true && activePins[3] == true) {
  Keyboard.press(KEY_8);
 }
 else if (activePins[3] == true && activePins[4] == true) {
  Keyboard.press(KEY_9);
 }
 else if (activePins[4] == true && activePins[2] == true) {
  Keyboard.press(KEY_0);
 }
 else {
  if (activePins[2] == true) {
    Keyboard.press(KEY_UP);
  }
  else if (activePins[2] == false) {
    Keyboard.release(KEY_UP);
  }
  if (activePins[3] == true) {
    Keyboard.press(KEY_DOWN);
  }
  else if (activePins[3] == false) {
    Keyboard.release(KEY_DOWN);
  }
  if (activePins[4] == true) {
    Keyboard.press(KEY_LEFT);
  }
  else if (activePins[4] == false) {
    Keyboard.release(KEY_LEFT);
  }
  if (activePins[5] == true) {
    Keyboard.press(KEY_RIGHT);
  }
  else if (activePins[5] == false) {
    Keyboard.release(KEY_RIGHT);
  }
  if (activePins[6] == true) {
    Keyboard.press(KEY_1);
  }
  else if (activePins[6] == false) {
    Keyboard.release(KEY_1);
  }
  if (activePins[7] == true) {
    Keyboard.press(KEY_2);
  }
  else if (activePins[7] == false) {
    Keyboard.release(KEY_2);
  }
 }


 if (activePins[2] == false && activePins[5] == false) {
  Keyboard.release(KEY_7);
 }
 if (activePins[5] == false && activePins[3] == false) {
  Keyboard.release(KEY_8);
 }
 if (activePins[3] == false && activePins[4] == false) {
  Keyboard.release(KEY_9);
 }
 if (activePins[4] == false && activePins[2] == false) {
  Keyboard.release(KEY_0);
 }

  
 
  return 0;
}

int readPins() {
  
  for(int i = 0;i < 8;i++) {
    if (digitalRead(pins[i]) == LOW) {
      activePins[i] = true;
    }
    else {
      activePins[i] = false;
    }
  }

  return 0;
}

int initMeasure() {
  
  for(int a = 0;a < 2;a++) {
    for(int b = 0;b < 8;b++) {
      delayMeasure[a][b] = millis();
    }
  }

  return 0;
}

int initPins() {
  
    for(int i = 0;i < 8;i++) {
    pinMode(pins[i], INPUT);
  }

  return 0;
}

int displayPins() {

  for(int i = 0;i < 8;i++) {
    Serial.print(activePins[i]);
    EEPROM.write(addr, active[i]);
    if (addr == EEPROM.length()) {
     addr = 0;
    } else {
     addr += 1;
    }
  }
  Serial.print("\n");

  return 0;
}



