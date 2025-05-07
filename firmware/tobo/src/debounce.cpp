#include <Arduino.h>

#include "debounce.hpp"


bool debounced_check(pin_debounce* db, unsigned long now, uint8_t value) {
    if (!db->interrupted) return false;
    db->interrupted = false;

    // On the very first check, don't bother checking time
    if (!db->fresh) {
        unsigned long diff = now - db->last_triggered_ms;
        if (db->last_triggered_ms > now) diff = (__LONG_MAX__ - db->last_triggered_ms) - now;

        if (diff < DEBOUNCE_MS) return false;

    }

    if (digitalRead(db->pin) != value) return false;

    db->fresh = false;

    db->last_triggered_ms = now;

    return true;
}


void debounce_interrupt(pin_debounce* db) {
    db->interrupted = true;
}