#ifndef BUTTON_H
#define BUTTON_H

void button_pin(uint8_t pin);
void button_configuration();

#define BUTTON_PIN_1 0
#define BUTTON_PIN_2 1
#define BUTTON_PIN_3 2
#define BUTTON_PIN_4 3
#define BUTTON_PIN_RESET 4
#define BUTTON_PIN_TOGGLE 5
#define NUM_BUTTONS 4
#define COIN_WAIT_TIME_MS 4000

#endif