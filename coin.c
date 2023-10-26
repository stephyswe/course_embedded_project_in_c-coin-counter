// config files
#include "lcd.h"
#include "millis.h"

// header files
#include "define.h"

void get_coin_category(int categoryCounts[NUM_BUTTONS], int lastClickedCoin,
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