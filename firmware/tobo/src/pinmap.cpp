#include "pinmap.hpp"
#include "headsets.hpp"

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
    16,  // PC2, 1,4   rear
    19,  // PC5, 2,4
    2,   // PD2, 3,4
    17,  // PC3, 4,4   front
};


// Touch points which have a common Y
#ifdef IS_XM2
    // The XM2 has its Y pins in a different order
    // in the cable, so we correct for that here
    const unsigned char TOUCH_Y_PIN[N_TOUCH_Y] {
        14, // PC0,  3,0,  bottom
        15, // PC1,  3,1
        18, // PC4,  3,2
        19  // PC5,  3,3,  top
    };

#else
    const unsigned char TOUCH_Y_PIN[N_TOUCH_Y] {
        19, // PC5,  3,4,  bottom
        18, // PC4,  3,5
        15, // PC1,  3,6
        14  // PC0,  3,7,  top
    };
#endif