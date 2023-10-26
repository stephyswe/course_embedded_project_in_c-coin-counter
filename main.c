#include <avr/interrupt.h>
#include <util/delay.h>

// config files
#include "lcd.h"
#include "millis.h"

// define file
#include "define.h"

// header files
#include "audio_buzzer.h"
#include "button.h"
#include "message.h"
#include "system.h"

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
  int systemOn = 1;                          // system state { 0 - off, 1 - on }
  int coinTotalValue = 0;                    // value of coins
  int coinQuantity = 0;                      // num of coins
  int coinQuantityCount[NUM_BUTTONS] = {0};  // num of coin variants
  int coinValues[NUM_BUTTONS] = {1, 5, 10,
                                 25};  // pre-defined value of coin category
  int lastClickedCoin = -1;            // -
  uint32_t lastCoinTime = millis();    // time of last coin press
  int buttonFlag = 1;

  while (1) {
    if (systemOn) {
      for (int i = 0; i < NUM_BUTTONS; i++) {
        if (bit_is_clear(PINB, BUTTON_PIN_1 + i)) {
          button_click(coinValues[i], &coinQuantity, &coinTotalValue,
                       &buttonFlag, &lastCoinTime);
          play_sound_coin();

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

    // display coin categories after "4" seconds
    if (!buttonFlag) {
      get_coin_category(coinQuantityCount, lastClickedCoin, &buttonFlag,
                        &lastCoinTime);
    }
  }
}

int main(void) {
  play_sound_intro();
  initialize_hardware();
  initialize_message();
  main_loop();

  return 0;
}
