#pragma once
#include <Arduino.h>

#define BUTTON_ACTIVE LOW
#define BUTTON_INACTIVE HIGH

#define TOUCH_ACTIVE HIGH
#define TOUCH_INACTIVE LOW

#define N_BTNS 8
extern const unsigned char BTN_PIN[N_BTNS];   // Arduino pin numbers
extern const unsigned char BTN_INT[N_BTNS];   // AVR Pin change interrupt number

// Pins which control our touch X-axis
#define N_TOUCH_X 4
extern const unsigned char TOUCH_X_PIN[N_TOUCH_X];

// Pins which control our touch Y axis
// One of the pins here is the same as one of the pins in the X axis
#define N_TOUCH_Y 4
extern const unsigned char TOUCH_Y_PIN[N_TOUCH_Y];
