#include <Wire.h>
#include "Keyboard.h"
#include "Mouse.h"


#define CARDKB_ADDR 0x5F
const int ctrlButton = 5;
char ctrlKey = KEY_LEFT_CTRL;
const int mouseButton = 7;    // input pin for the mouse pushButton
const int lmouseButton = 6;    // input pin for the mouse pushButton
const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis
int range = 3;               // output range of X or Y movement
int responseDelay = 5;        // response delay of the mouse, in ms
int threshold = range / 4;    // resting threshold
int center = range / 2;       // resting position value
int xMap, yMap;
const int sensitivity = 1;


void setup()
{
  pinMode(ctrlButton, INPUT_PULLUP);
  pinMode(mouseButton, INPUT_PULLUP);
  pinMode(lmouseButton, INPUT_PULLUP);
  Wire.begin();
  Serial.begin(115200);
  Keyboard.begin();
  Mouse.begin();
}
void loop()
{
  Wire.requestFrom(CARDKB_ADDR, 1);
  while(Wire.available())
  {
    char c = Wire.read(); // receive a byte as characterif
    if (c != 0)
    {
  if (digitalRead(ctrlButton) == LOW) {
      Keyboard.press(ctrlKey);
      Keyboard.press(char(c));
      delay(100);
      Keyboard.releaseAll();
      return ;
  }
    if (c == 0xFFFFFFAF) {
      Keyboard.write(KEY_UP_ARROW);
      return ;
  }
    if (c == 0xFFFFFFB0) {
      Keyboard.write(KEY_DOWN_ARROW);
      return ;
  }
    if (c == 0xFFFFFFB2) {      //right arrow
      Keyboard.write(0xD7);
      return ;
  }
    if (c == 0xFFFFFFB1) {      //left arrow
      Keyboard.write(0xD8);
      return ;
  }
    if (c == 0xFFFFFFB5) {      //shift |
      Keyboard.press(ctrlKey);
 //     Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('v');
      delay(100);
      Keyboard.releaseAll();
      return ;
  }
    if (c == 0xFFFFFFB4) {      //shift ?
      Keyboard.press(ctrlKey);
 //     Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('c');
      delay(100);
      Keyboard.releaseAll();
      return ;
  }
    if (c == 0xFFFFFFB6) {      //shift {
      Keyboard.press(ctrlKey);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('c');
      delay(100);
      Keyboard.releaseAll();
      return ;
  }
    if (c == 0xFFFFFFB7) {      //shift }
      Keyboard.press(ctrlKey);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('v');
      delay(100);
      Keyboard.releaseAll();
      return ;
  }
    if (c == 0xFFFFFF8E) {      //fn t
      Keyboard.press(ctrlKey);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      delay(100);
      Keyboard.releaseAll();
      return ;
  }
    if (c == 0x1B) {
      Keyboard.write(KEY_ESC);
      return ;
  }
    if (c == 0x0D) {
      Keyboard.write(KEY_RETURN);
      return ;
  }
      Serial.println(c, HEX);
      Serial.println(char(c));
      Keyboard.write(char(c));

    }
  }
    int xReading = readAxis(A0);
    int yReading = readAxis(A1);
    Mouse.move(xReading, yReading, 0);
  if (digitalRead(mouseButton) == LOW) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
  if (digitalRead(lmouseButton) == LOW) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
    }
  }
  else {
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  delay(responseDelay);
}
  int readAxis(int thisAxis) {
  // read the analog input:
  int reading = analogRead(thisAxis);

  // map the reading from the analog input range to the output range:
  reading = map(reading, 0, 1023, 0, range);

  // if the output reading is outside from the rest position threshold, use it:
  int distance = reading - center;

  if (abs(distance) < threshold) {
    distance = 0;
}

  // return the distance for this axis:
  return distance;
}
