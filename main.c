#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

// config files
#include "lcd.h"
#include "millis.h"

// define file
#include "define.h"

// header files
#include "button.h"
#include "system.h"
#include "message.h"

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

void update_coin_category(int lastClickedCoin, int coinValues[NUM_BUTTONS],
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

// Initialize hardware and peripherals
void initialize_hardware() {
  button_configuration();
  millis_init();
  sei();
  lcd_init();
  lcd_enable_cursor();
}

void main_loop() {

  // ** variables
  int systemOn = 1;                               // system state { 0 - off, 1 - on }
  int coinTotalValue = 0;                         // value of coins
  int coinQuantity = 0;                           // num of coins 
  int coinQuantityCount[NUM_BUTTONS] = {0};       // num of coin variants
  int coinValues[NUM_BUTTONS] = {1, 5, 10, 25};   // pre-defined value of coin category
  int lastClickedCoin = -1;                       // -
  uint32_t lastCoinTime = millis();               // time of last coin press
  int buttonFlag = 1;                             // flag on button click
  

  while (1) {
    if (systemOn) {
      for (int i = 0; i < NUM_BUTTONS; i++) {
        if (bit_is_clear(PINB, BUTTON_PIN_1 + i)) {
          button_click(coinValues[i], &coinQuantity, &coinTotalValue,
                              &buttonFlag, &lastCoinTime);

          lastClickedCoin = coinValues[i];
          update_coin_category(lastClickedCoin, coinValues, coinQuantityCount);
        }
      }
    }

    if (bit_is_clear(PINB, BUTTON_PIN_RESET)) {
      system_reset();
    }

    if (bit_is_clear(PINB, BUTTON_PIN_TOGGLE)) {
      system_toggle(&systemOn);
    }

    lcd_set_cursor(0, 1);

    // display coin categories after "4" seconds
    if (!buttonFlag) {
      get_coin_category(coinQuantityCount, lastClickedCoin, &buttonFlag, &lastCoinTime);
    }
  }
}

int main(void) {
  initialize_hardware();
  initialize_message();
  main_loop();

  return 0;
}
