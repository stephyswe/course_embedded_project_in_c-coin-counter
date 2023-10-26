#include <avr/io.h>

#include "button.h"
#include "define.h"

void button_pin(uint8_t pin) {
  DDRB &= ~(1 << pin);  // button input
  PORTB |= (1 << pin);  // resistor on pin
}

void button_configuration() {
  button_pin(BUTTON_PIN_1);
  button_pin(BUTTON_PIN_2);
  button_pin(BUTTON_PIN_3);
  button_pin(BUTTON_PIN_4);
  button_pin(BUTTON_PIN_RESET);
  button_pin(BUTTON_PIN_TOGGLE);
}
