#include <Keyboard.h>

const int PRINT_THRESHOLD = 700;
int ROW_PIN[] = {1, 0, 4, 3, 2};
int COL_PIN[] = {6, 7, 8, 9};
const int ROW_COUNT = sizeof(ROW_PIN)/sizeof(ROW_PIN[0]);
const int COL_COUNT = sizeof(COL_PIN)/sizeof(COL_PIN[0]);
char layout[5][4] = {
  {177, '0', '.', 176},
  {'1', '2', '3', 177},
  {'=', '/', '*', '-'},
  {'7', '8', '9', 177},
  {'4', '5', '6', '+'}
};
int pressCount[5][4] = {
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0},
  {0,0,0,0}
};

void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();
  for (int i = 0; i < ROW_COUNT; i++) {
    pinMode(ROW_PIN[i], OUTPUT);
  };
  for (int i = 0; i < COL_COUNT; i++) {
    pinMode(COL_PIN[i], INPUT);
  };
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int row = 0; row < ROW_COUNT; row++) digitalWrite(ROW_PIN[row], LOW);
  for (int row = 0; row < ROW_COUNT; row++) {
    digitalWrite(ROW_PIN[row], HIGH);
    for (int col = 0; col < COL_COUNT; col++) {
      if (digitalRead(COL_PIN[col]) == HIGH) {
        if (pressCount[row][col] == 0 || pressCount[row][col] > PRINT_THRESHOLD) {
          Keyboard.press(layout[row][col]);
          delay(1);
          Keyboard.release(layout[row][col]);
          if (pressCount[row][col] > PRINT_THRESHOLD) pressCount[row][col] *= 0.9;
        }
        pressCount[row][col]++;        
      } else pressCount[row][col] = 0;
    }
    digitalWrite(ROW_PIN[row], LOW);
  }
  delay(1);
}
