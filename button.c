#include <avr/io.h>
#include <util/delay.h>

// config files
#include "lcd.h"

// define file
#include "define.h"

// header files
#include "button.h"
#include "millis.h"


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

// Function to handle button click
void button_click(int value, int* coinCount, int* coinCounter,
                         int* buttonFlag, uint32_t* lastCoinTime) {
  _delay_ms(200);
  lcd_clear();
  lcd_set_cursor(0, 1);

  *coinCounter += value;
  (*coinCount)++;

  lcd_set_cursor(0, 0);
  lcd_printf("%d Coin(s)", *coinCount);
  lcd_set_cursor(0, 1);
  lcd_printf("Total: %d SEK", *coinCounter);

  // Set the last coin press time to the current time
  *lastCoinTime = millis();

  // Reset the "Random" message flag
  *buttonFlag = 0;
}
