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
void HandleButtonClick(int value, int *coinCount, int *coinCounter, int *randomMessageFlag, uint32_t *lastCoinTime) {
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
    *randomMessageFlag = 0;
}

// Function to display the coin counts
void DisplayCoinCounts(int coinCount, int coinValues[NUM_BUTTONS]) {
    lcd_clear();
    lcd_set_cursor(0, 0);

    // Create a message like "A: x / B: y" where x and y are the counts of coins A and B
    for (int i = 0; i < NUM_BUTTONS; i++) {
        lcd_printf("%c: %d", 'A' + i, coinCount / coinValues[i]);

        if (i == 1) {
            // Move to the next line after displaying A and B counts
            lcd_set_cursor(0, 1);
        } else if (i < NUM_BUTTONS - 1) {
            lcd_printf(" / ");
        }
    }
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
    int buttonFlag = 1; // flag on button click
    uint32_t lastCoinTime = millis(); // Track time of last coin press
    
    // Initialize last clicked coin value
    int lastClickedCoin = -1;
    int categoryCounts[NUM_BUTTONS] = {0}; // Initialize to all zeros

    while (1) {
        if (systemOn) {
            for (int i = 0; i < NUM_BUTTONS; i++) {
                if (bit_is_clear(PINB, BUTTON_PIN_1 + i)) {
                    HandleButtonClick(coinValues[i], &coinCount, &coinCounter, &buttonFlag, &lastCoinTime);
                     lastClickedCoin = coinValues[i];

                     // category index for clicked coin
                    int categoryIndex = -1;
                    for (int j = 0; j < NUM_BUTTONS; j++) {
                        if (lastClickedCoin == coinValues[j]) {
                            categoryIndex = j;
                            break;
                        }
                    }

                    // Update categoryCounts array
                    if (categoryIndex != -1) {
                        categoryCounts[categoryIndex] += 1;
                    }
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

        // Check if it's time to display "Random"
        if (!buttonFlag) {
            uint32_t currentTime = millis();
            if (currentTime - lastCoinTime >= 4000) { // 4 seconds have passed
                lcd_clear();
                lcd_set_cursor(0, 0);


                if (lastClickedCoin != -1) {
                    lcd_clear();

                    lcd_printf("A: %d / B: %d", categoryCounts[0], categoryCounts[1]);
                    lcd_set_cursor(0, 1);
                    lcd_printf("C: %d / D: %d", categoryCounts[2], categoryCounts[3]);
                }

                 else {
                    lcd_printf("User None"); // No coin clicked
                }
                buttonFlag = 1; // Set the "Random" message flag
            }
        }
    }
}

int main(void) {
    InitializeHardware();
    MainLoop();

    return 0;
}
