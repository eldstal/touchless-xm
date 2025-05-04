#include <pinmap.h>

unsigned char BTN_PIN[N_BTNS] = {
    10, // PB2
    9,  // PB1
    8,  // PB0
    7,  // PD7
    6,  // PD6
    5,  // PD5
    21, // PB7
    20  // PB6
};

unsigned char BTN_INT[N_BTNS] {
    2,  // PB2
    1,  // PB1
    0,  // PB0
    23, // PD7
    22, // PD6
    21, // PD5
    7,  // PB7
    6   // PB6
};


unsigned char TOUCH_X_PIN[N_TOUCH_X] {
    2,  // PD2
    17, // PC3
    19, // PC5
    16  // PC2
};


unsigned char TOUCH_Y_PIN[N_TOUCH_Y] {
    19, // PC5
    18, // PC4
    15, // PC1
    14 // PC0
};