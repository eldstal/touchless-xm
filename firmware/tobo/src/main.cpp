#include <Arduino.h>

#include "pinmap.hpp"
#include "gestures.hpp"


// Set LED_BUILTIN if undefined or not pin 13
// #define LED_BUILTIN 13

void setup_pins() {
  for (unsigned char p=0; p<N_BTNS; ++p) {
    pinMode(BTN_PIN[p], INPUT);
  }

  for (unsigned char p=0; p<N_TOUCH_X; ++p) {
    pinMode(TOUCH_X_PIN[p], OUTPUT);
  }

  for (unsigned char p=0; p<N_TOUCH_Y; ++p) {
    pinMode(TOUCH_Y_PIN[p], OUTPUT);
  }
}

void setup()
{
   setup_pins();

}

void loop()
{
  // Set the LED HIGH
  //digitalWrite(TOUCH_X_PIN[0], HIGH);

  // Wait for a second
  //delay(1000);

  // Set the LED LOW
  //digitalWrite(TOUCH_X_PIN[0], LOW);

  gesture_perform(&GESTURE_SWIPE_BWD, BTN_PIN[0]);

  // Wait for a second
  delay(1000);
}
