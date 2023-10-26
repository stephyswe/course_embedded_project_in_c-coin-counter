#ifndef BUTTON_H
#define BUTTON_H

void button_pin(uint8_t pin);
void button_configuration();
void button_click(int value, int* coinCount, int* coinCounter, int* buttonFlag, uint32_t* lastCoinTime);

#endif