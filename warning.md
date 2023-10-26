C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/main.o -c main.c
In file included from main.c:5:
lcd.h:13:10: warning: #warning is a GCC extension
   13 |         #warning "LCD Using default pin"
      |          ^~~~~~~
lcd.h:13:10: warning: #warning "LCD Using default pin" [-Wcpp]
main.c: In function 'main_loop':
main.c:48:11: warning: implicit declaration of function 'update_coin_category' [-Wimplicit-function-declaration]
   48 |           update_coin_category(lastClickedCoin, coinValues, coinQuantityCount);
      |           ^~~~~~~~~~~~~~~~~~~~
main.c:54:7: warning: implicit declaration of function 'system_reset' [-Wimplicit-function-declaration]
   54 |       system_reset();
      |       ^~~~~~~~~~~~
main.c:58:7: warning: implicit declaration of function 'system_toggle' [-Wimplicit-function-declaration]
   58 |       system_toggle(&systemOn);
      |       ^~~~~~~~~~~~~
main.c:63:7: warning: implicit declaration of function 'get_coin_category' [-Wimplicit-function-declaration]
   63 |       get_coin_category(coinQuantityCount, lastClickedCoin, &buttonFlag,
      |       ^~~~~~~~~~~~~~~~~
C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/lcd.o -c lcd.c
In file included from lcd.c:1:
lcd.h:13:10: warning: #warning is a GCC extension
   13 |         #warning "LCD Using default pin"
      |          ^~~~~~~
lcd.h:13:10: warning: #warning "LCD Using default pin" [-Wcpp]
lcd.c: In function 'lcd_write_nibble':
lcd.c:37:23: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   37 |   LCD_PORT = LCD_PORT & ~(1 << LCD_EN);
lcd.c:39:23: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   39 |   LCD_PORT = LCD_PORT & ~(1 << LCD_EN);
lcd.c: In function 'lcd_send':
lcd.c:25:25: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   25 |     LCD_PORT = LCD_PORT & ~(1 << LCD_RS);
lcd.c: In function 'lcd_init':
lcd.c:59:5: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   59 |     & ~(1 << LCD_RS);
C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/millis.o -c millis.c
In file included from millis.c:12:
In function '__iRestore',
    inlined from 'millis_get' at millis.c:136:2:
c:\avr\avr\include\util\atomic.h:70:10: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   70 |     SREG = *__s;
      |          ^
millis.c: In function 'millis_pause':
millis.c:153:19: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
  153 |         REG_TIMSK &= ~_BV(BIT_OCIE);
      |                   ^~
In function '__iRestore',
    inlined from 'millis_reset' at millis.c:160:2:
c:\avr\avr\include\util\atomic.h:70:10: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   70 |     SREG = *__s;
      |          ^
In function '__iRestore',
    inlined from 'millis_add' at millis.c:169:2:
c:\avr\avr\include\util\atomic.h:70:10: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   70 |     SREG = *__s;
      |          ^
In function '__iRestore',
    inlined from 'millis_subtract' at millis.c:178:2:
c:\avr\avr\include\util\atomic.h:70:10: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
   70 |     SREG = *__s;
      |          ^
C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/button.o -c button.c
In file included from button.c:5:
lcd.h:13:10: warning: #warning is a GCC extension
   13 |         #warning "LCD Using default pin"
      |          ^~~~~~~
lcd.h:13:10: warning: #warning "LCD Using default pin" [-Wcpp]
C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/system.o -c system.c
In file included from system.c:5:
lcd.h:13:10: warning: #warning is a GCC extension
   13 |         #warning "LCD Using default pin"
      |          ^~~~~~~
lcd.h:13:10: warning: #warning "LCD Using default pin" [-Wcpp]
C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/message.o -c message.c
In file included from message.c:3:
lcd.h:13:10: warning: #warning is a GCC extension
   13 |         #warning "LCD Using default pin"
      |          ^~~~~~~
lcd.h:13:10: warning: #warning "LCD Using default pin" [-Wcpp]
C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/coin.o -c coin.c
In file included from coin.c:2:
lcd.h:13:10: warning: #warning is a GCC extension
   13 |         #warning "LCD Using default pin"
      |          ^~~~~~~
lcd.h:13:10: warning: #warning "LCD Using default pin" [-Wcpp]
C:\avr\bin\avr-gcc -Wall -Wextra  -Wundef -pedantic -Os -std=gnu99 -DF_CPU=16000000UL -mmcu=atmega328p -DBAUD=19200 -MD -o bin/debug/audio_buzzer.o -c audio_buzzer.c
audio_buzzer.c: In function 'play_sound_intro':
audio_buzzer.c:81:24: warning: comparison of integer expressions of different signedness: 'size_t' {aka 'unsigned int'} and 'int' [-Wsign-compare]
   81 |   for (size_t i = 0; i < count; i++) {
      |                        ^
In function 't0_set_prescaler',
    inlined from 'play_sound_func' at audio_buzzer.c:60:3:
audio_buzzer.c:8:10: warning: array subscript 0 is outside array bounds of 'volatile uint8_t[0]' {aka 'volatile unsigned char[]'} [-Warray-bounds]
    8 |   TCCR0B = ps;
      |          ^