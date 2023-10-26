#include <avr/io.h>
#include <util/delay.h>

#include "audio_buzzer.h"

void t0_set_prescaler(enum t0_prescaler ps) {
  TCCR0B = ps;
}