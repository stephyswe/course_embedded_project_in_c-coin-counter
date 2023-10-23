#include <avr/io.h>
#include "button.h"

void configureButtonPin(uint8_t pin) {
    DDRB &= ~(1 << pin);   // button input
    PORTB |= (1 << pin);   // resistor on pin
}

void configureButtons() {
    configureButtonPin(BUTTON_PIN_1);
    configureButtonPin(BUTTON_PIN_2);
    configureButtonPin(BUTTON_PIN_3);
    configureButtonPin(BUTTON_PIN_4);
    configureButtonPin(BUTTON_PIN_RESET);
    configureButtonPin(BUTTON_PIN_TOGGLE);
}
