#pragma once

#include <stdint.h>

#define DEBOUNCE_MS 5


typedef struct {
    uint8_t pin;
    bool fresh;
    bool interrupted;
    unsigned long last_triggered_ms;
} pin_debounce;

extern bool debounced_check(pin_debounce* db, unsigned long now, uint8_t value);
extern void debounce_interrupt(pin_debounce* db);