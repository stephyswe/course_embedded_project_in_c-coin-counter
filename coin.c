// config files
#include "lcd.h"
#include "millis.h"

// header files
#include "define.h"

void update_coin_category(int lastClickedCoin, int coinValues[NUM_BUTTONS], int categoryCounts[NUM_BUTTONS]) {
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
      lcd_printf("Category not found");  // No coin clicked
    }
    *buttonFlag = 1;  // Set the flag
  }
}