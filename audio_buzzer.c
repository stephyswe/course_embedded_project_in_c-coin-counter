#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>

#include "audio_buzzer.h"

void t0_set_prescaler(enum t0_prescaler ps) {
  TCCR0B = ps;
}

unsigned short t0_get_prescaler_rate(enum t0_prescaler ps) {
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

unsigned long div_round(unsigned long d, unsigned long q) {
  return (d + (q / 2)) / q;
}

void t0_set_ctc_a(unsigned long hz, unsigned long timer_freq) {
  OCR0A = div_round(timer_freq, hz * 2) - 1;
  TCCR0A = _BV(COM0A0)    // toggle
           | _BV(WGM01);  // CTC
}

void stop_sound() {

  DDRD |= _BV(DDD3);

  // Add a delay if needed
  _delay_ms(
      200);  // Adjust this value as needed for your timing requirements              // flag on button click
}

void play_sound_coin() {
  unsigned long timer_freq;
  enum t0_prescaler ps = T0_PRESCALER_256;

  DDRD |= _BV(DDD6);
  t0_set_prescaler(ps);
  timer_freq = div_round(F_CPU, t0_get_prescaler_rate(ps));

  t0_set_ctc_a(1024, timer_freq);
  _delay_ms(200);

  // After your for loop, turn off the buzzer
  OCR0A = 0;  // Set the output compare register to 0 to stop the tone

  // Optionally, you can update the timer control registers to disconnect the output
  TCCR0A = 0;  // Clear all bits in the timer control register A
  TCCR0B = 0;  // Clear all bits in the timer control register B
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