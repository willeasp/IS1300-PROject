/*
 * display.h
 *
 *  Created on: Dec 19, 2021
 *      Author: Dell
 */

#ifndef SRC_DISPLAY_H_
#define SRC_DISPLAY_H_



#endif /* SRC_DISPLAY_H_ */


void init_backlight (void);
void test_backlight (void);

void init_display (void);


int display_write_row (char *characters, uint16_t length, uint8_t row);
