#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "lcd.h"

void system_reset() {
  lcd_clear();
  wdt_enable(WDTO_15MS);  // Enable the Watchdog Timer with a short timeout
  while (1)
    ;  // Wait for the watchdog timer to reset the microcontroller
}

void system_toggle(int* systemOn) {
  if (*systemOn) {
    *systemOn = 0;  // Turn off
    lcd_clear();
    lcd_puts("SYSTEM OFF");
    _delay_ms(1000);
    lcd_clear();
  } else {
    *systemOn = 1;  // Turn on
    lcd_clear();
    lcd_puts("SYSTEM ON");
    _delay_ms(2000);
    system_reset();
  }
}
