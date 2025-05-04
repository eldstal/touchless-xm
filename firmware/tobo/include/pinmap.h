#pragma once


#define N_BTNS 8
extern unsigned char BTN_PIN[N_BTNS];   // Arduino pin numbers
extern unsigned char BTN_INT[N_BTNS];   // AVR Pin change interrupt number

// Pins which control our touch X-axis
#define N_TOUCH_X 4
extern unsigned char TOUCH_X_PIN[N_TOUCH_X];

// Pins which control our touch Y axis
// One of the pins here is the same as one of the pins in the X axis
#define N_TOUCH_Y 4
extern unsigned char TOUCH_Y_PIN[N_TOUCH_Y];