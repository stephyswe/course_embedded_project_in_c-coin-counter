#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

// config files
#include "lcd.h"
#include "millis.h"

// header files
#include "button.h"
#include "system.h"

// Function to handle button click
void HandleButtonClick(int value, int *coinCount, int *coinCounter) {
    _delay_ms(200);
    lcd_clear();
    lcd_set_cursor(0, 1);

    *coinCounter += value;
    (*coinCount)++;

    lcd_set_cursor(0, 0);
    lcd_printf("%d Coin(s)", *coinCount);
    lcd_set_cursor(0, 1);
    lcd_printf("Total: %d SEK", *coinCounter);
}

// Initialize hardware and peripherals
void InitializeHardware() {
    configureButtons();
    millis_init();
    sei();
    lcd_init();
    lcd_enable_cursor();
    lcd_puts("Money box:");
    lcd_set_cursor(0, 1);
    lcd_puts("Coin (1,5,10,25)");
}

// Main loop
void MainLoop() {
    int coinCounter = 0;
    int coinCount = 0;
    int systemOn = 1;
    int coinValues[NUM_BUTTONS] = {1, 5, 10, 25};

    while (1) {
        if (systemOn) {
            for (int i = 0; i < NUM_BUTTONS; i++) {
                if (bit_is_clear(PINB, BUTTON_PIN_1 + i)) {
                    HandleButtonClick(coinValues[i], &coinCount, &coinCounter);
                }
            }
        }

        if (bit_is_clear(PINB, BUTTON_PIN_RESET)) {
            software_reset();
        }

        if (bit_is_clear(PINB, BUTTON_PIN_TOGGLE)) {
            toggle_system(&systemOn);
            _delay_ms(500);
        }

        lcd_set_cursor(0, 1);
    }
}

int main(void) {
    InitializeHardware();
    MainLoop();

    return 0;
}
