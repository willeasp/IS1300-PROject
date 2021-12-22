/*
 * display.h
 *
 *  Created on: Dec 19, 2021
 *      Author: Dell
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_



#endif /* SRC_DISPLAY_H_ */

#define WHITE 0
#define GREEN 1

void set_backlight (uint8_t color, GPIO_PinState state);
void test_backlight (void);

void init_display (void);


int display_write_row (char *characters, uint16_t length, uint8_t row);
int clear_display ();
