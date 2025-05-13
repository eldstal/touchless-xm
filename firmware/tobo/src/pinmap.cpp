#include "pinmap.hpp"
#include "headsets.hpp"

const unsigned char BTN_PIN[N_BTNS] = {
    PIN_PB2,
    PIN_PB1,
    PIN_PB0,
    PIN_PD7,
    PIN_PD6,
    PIN_PD5,
    PIN_PC0,
    PIN_PC1
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
    PIN_PC2,  // 1,4   rear
    PIN_PC5,  // 2,4
    PIN_PD2,  // 3,4
    PIN_PC3,  // 4,4   front
};


// Touch points across different Y values
#ifdef IS_XM2
    // The XM2 has its Y pins in a different order
    // in the cable, so we correct for that here
    const unsigned char TOUCH_Y_PIN[N_TOUCH_Y] {
        PIN_PB7, // 2,0,  bottom
        PIN_PB6, // 2,1
        PIN_PC4, // 2,2
        PIN_PC5  // 2,3,  top
    };

#else
    const unsigned char TOUCH_Y_PIN[N_TOUCH_Y] {
        PIN_PC5,  // 2,4,  bottom
        PIN_PC4,  // 2,5
        PIN_PB6,  // 2,6
        PIN_PB7,  // 2,7,  top
    };
#endif