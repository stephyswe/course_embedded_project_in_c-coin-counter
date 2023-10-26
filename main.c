#include <avr/interrupt.h>
#include <util/delay.h>

#include <stddef.h>

// config files
#include "lcd.h"
#include "millis.h"

// define file
#include "define.h"

// header files
#include "button.h"
#include "message.h"
#include "system.h"

enum t0_prescaler {
  T0_PRESCALER_1 = _BV(CS00),
  T0_PRESCALER_8 = _BV(CS01),
  T0_PRESCALER_64 = _BV(CS00) | _BV(CS01),
  T0_PRESCALER_256 = _BV(CS02),
  T0_PRESCALER_1024 = _BV(CS02) | _BV(CS00),
};

static void t0_set_prescaler(enum t0_prescaler ps) {
  TCCR0B = ps;
}

static unsigned short t0_get_prescaler_rate(enum t0_prescaler ps) {
  unsigned short rate;
  switch (ps) {
    case T0_PRESCALER_1:
      rate = 1;
      break;
    case T0_PRESCALER_8:
      rate = 8;
      break;
    case T0_PRESCALER_64:
      rate = 64;
      break;
    case T0_PRESCALER_256:
      rate = 256;
      break;
    case T0_PRESCALER_1024:
      rate = 1024;
      break;
    default:
      rate = 0;
      break;
  }
  return rate;
}

static unsigned long div_round(unsigned long d, unsigned long q) {
  return (d + (q / 2)) / q;
}

static void t0_set_ctc_a(unsigned long hz, unsigned long timer_freq) {
  OCR0A = div_round(timer_freq, hz * 2) - 1;
  TCCR0A = _BV(COM0A0)    // toggle
           | _BV(WGM01);  // CTC
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

void stop_sound() {

  DDRD |= _BV(DDD3);

  // Add a delay if needed
  _delay_ms(
      200);  // Adjust this value as needed for your timing requirements              // flag on button click
}

void play_sound_intro() {
  unsigned long timer_freq;
  enum t0_prescaler ps = T0_PRESCALER_256;

  DDRD |= _BV(DDD6);
  t0_set_prescaler(ps);
  timer_freq = div_round(F_CPU, t0_get_prescaler_rate(ps));

  int count = 3;
  for (size_t i = 0; i < count; i++) {
    t0_set_ctc_a(440, timer_freq);
    _delay_ms(200);
    t0_set_ctc_a(880, timer_freq);
    _delay_ms(200);
  }

  // After your for loop, turn off the buzzer
  OCR0A = 0;  // Set the output compare register to 0 to stop the tone

  // Optionally, you can update the timer control registers to disconnect the output
  TCCR0A = 0;  // Clear all bits in the timer control register A
  TCCR0B = 0;  // Clear all bits in the timer control register B

  // Add a delay if needed
  _delay_ms(200);  // Adjust this value as needed for your timing requirements
}

int main(void) {
  play_sound_intro();
  initialize_hardware();
  initialize_message();
  main_loop();

  return 0;
}
