#ifndef AUDIO_BUZZER_H
#define AUDIO_BUZZER_H

enum t0_prescaler {
  T0_PRESCALER_1 = _BV(CS00),
  T0_PRESCALER_8 = _BV(CS01),
  T0_PRESCALER_64 = _BV(CS00) | _BV(CS01),
  T0_PRESCALER_256 = _BV(CS02),
  T0_PRESCALER_1024 = _BV(CS02) | _BV(CS00),
};

void t0_set_prescaler(enum t0_prescaler ps);

#endif