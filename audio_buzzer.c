#include <avr/io.h>
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