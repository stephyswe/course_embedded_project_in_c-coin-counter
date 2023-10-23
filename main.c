#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

// config files
#include "lcd.h"
#include "millis.h"

// header files
#include "button.h"
#include "system.h"

#define COIN_WAIT_TIME_MS 4000

// Function to handle button click
void HandleButtonClick(int value, int* coinCount, int* coinCounter,
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

void displayCategory(int categoryCounts[NUM_BUTTONS], int lastClickedCoin,
                     int* buttonFlag, uint32_t* lastCoinTime) {
  uint32_t currentTime = millis();
  if (!(*buttonFlag) && currentTime - *lastCoinTime >=
                            COIN_WAIT_TIME_MS) {  // 4 seconds have passed
    lcd_clear();
    lcd_set_cursor(0, 0);

    if (lastClickedCoin != -1) {
      lcd_clear();

      lcd_printf("A: %d / B: %d", categoryCounts[0], categoryCounts[1]);
      lcd_set_cursor(0, 1);
      lcd_printf("C: %d / D: %d", categoryCounts[2], categoryCounts[3]);
    } else {
      lcd_printf("User None");  // No coin clicked
    }
    *buttonFlag = 1;  // Set the flag
  }
}

// Initialize hardware and peripherals
void InitializeHardware() {
  configureButtons();
  millis_init();
  sei();
  lcd_init();
  lcd_enable_cursor();
}

void initMessage() {
  lcd_puts("Money box:");
  lcd_set_cursor(0, 1);
  lcd_puts("Coin (1,5,10,25)");
}

void updateCoinCategory(int lastClickedCoin, int coinValues[NUM_BUTTONS],
                        int categoryCounts[NUM_BUTTONS]) {
  // Category index for clicked coin
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

void MainLoop() {

  // variables
  int coinCounter = 0;
  int coinCount = 0;
  int systemOn = 1;
  int coinValues[NUM_BUTTONS] = {1, 5, 10, 25};
  int buttonFlag = 1;                // flag on button click
  uint32_t lastCoinTime = millis();  // Track time of last coin press

  // Initialize last clicked coin value
  int lastClickedCoin = -1;
  int categoryCounts[NUM_BUTTONS] = {0};  // Initialize to all zeros

  while (1) {
    if (systemOn) {
      for (int i = 0; i < NUM_BUTTONS; i++) {
        if (bit_is_clear(PINB, BUTTON_PIN_1 + i)) {
          HandleButtonClick(coinValues[i], &coinCount, &coinCounter,
                            &buttonFlag, &lastCoinTime);
          lastClickedCoin = coinValues[i];
          updateCoinCategory(lastClickedCoin, coinValues, categoryCounts);
        }
      }
    }

    if (bit_is_clear(PINB, BUTTON_PIN_RESET)) {
      software_reset();
    }

    if (bit_is_clear(PINB, BUTTON_PIN_TOGGLE)) {
      toggle_system(&systemOn);
    }

    lcd_set_cursor(0, 1);

    // display count categories after "4" seconds
    if (!buttonFlag) {
      displayCategory(categoryCounts, lastClickedCoin, &buttonFlag,
                      &lastCoinTime);
    }
  }
}

int main(void) {
  InitializeHardware();
  initMessage();
  MainLoop();

  return 0;
}
