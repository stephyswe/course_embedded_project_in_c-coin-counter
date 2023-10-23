#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

// header files
#include "system.h"

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)
// https://wokwi.com/projects/379402088569472001


#define BUTTON_PIN_1 0
#define BUTTON_PIN_2 1
#define BUTTON_PIN_3 2
#define BUTTON_PIN_4 3
#define BUTTON_PIN_RESET 4
#define BUTTON_PIN_TOGGLE 5

char currentText[5] = {0};
int coinCounter = 0; // coin counter
int coinCount = 0;   // num of coins
int systemOn = 1;     // System state (1 = on, 0 = off)

void configureButtonPin(uint8_t pin) {
    DDRB &= ~(1 << pin);   // button input
    PORTB |= (1 << pin);   // resistor on pin
}

void HandleButtonClick(char *txt, int value) {
    _delay_ms(200);
    strcat(currentText, txt);
    lcd_clear();
    lcd_set_cursor(0, 1);

    //lcd_clear();  // clear
    lcd_puts(txt); // show pressed number
    coinCounter += value; // Increment sum
    coinCount++;          // Increment number
    lcd_set_cursor(0, 0);
    lcd_printf("%d Coin(s)", coinCount);
    lcd_set_cursor(0, 1);
    lcd_printf("Total: %d SEK", coinCounter);
}

void configureButtons() {
    configureButtonPin(BUTTON_PIN_1);
    configureButtonPin(BUTTON_PIN_2);
    configureButtonPin(BUTTON_PIN_3);
    configureButtonPin(BUTTON_PIN_4);
    configureButtonPin(BUTTON_PIN_RESET);
    configureButtonPin(BUTTON_PIN_TOGGLE);
}

int main(void) {
    configureButtons();

    millis_init();
    sei();

    lcd_init();
    //lcd_enable_blinking();
    lcd_enable_cursor();
    lcd_puts("Money box:");
    lcd_set_cursor(0, 1);
    lcd_puts("Coin (1,5,10,25)");

    while (1) {
        if (systemOn) {
            if (bit_is_clear(PINB, BUTTON_PIN_1)) {
                HandleButtonClick("1", 1);
            }
            if (bit_is_clear(PINB, BUTTON_PIN_2)) {
                HandleButtonClick("2", 5);
            }
            if (bit_is_clear(PINB, BUTTON_PIN_3)) {
                HandleButtonClick("3", 10);
            }
            if (bit_is_clear(PINB, BUTTON_PIN_4)) {
                HandleButtonClick("4", 25);
            }
        }

        if (bit_is_clear(PINB, BUTTON_PIN_RESET)) {
            software_reset();
        }

        if (bit_is_clear(PINB, BUTTON_PIN_TOGGLE)) {
            toggle_system(&systemOn);
            _delay_ms(500); // Delay to prevent immediate toggle back
        }

        lcd_set_cursor(0, 1);
    }
    return 0;
}