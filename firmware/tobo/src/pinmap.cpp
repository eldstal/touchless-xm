#include <pinmap.hpp>

const unsigned char BTN_PIN[N_BTNS] = {
    10, // PB2
    9,  // PB1
    8,  // PB0
    7,  // PD7
    6,  // PD6
    5,  // PD5
    21, // PB7
    20  // PB6
};

const unsigned char BTN_INT[N_BTNS] {
    2,  // PB2
    1,  // PB1
    0,  // PB0
    23, // PD7
    22, // PD6
    21, // PD5
    7,  // PB7
    6   // PB6
};


// Touch points across different X values
const unsigned char TOUCH_X_PIN[N_TOUCH_X] {
    2,  // PD2, 5,4,  rear
    17, // PC3, 6,4
    19, // PC5, 7,4
    16  // PC2, 8,4,  front
};


// Touch points which have a common Y
const unsigned char TOUCH_Y_PIN[N_TOUCH_Y] {
    19, // PC5,  7,4,  bottom
    18, // PC4,  7,5
    15, // PC1,  7,6
    14  // PC0,  7,7,  top
};
