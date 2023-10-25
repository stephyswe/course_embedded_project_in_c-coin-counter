#include <avr/io.h>

#include "lcd.h"

void initialize_message() {
  lcd_puts("Money box:");
  lcd_set_cursor(0, 1);
  lcd_puts("Coin (1,5,10,25)");
}