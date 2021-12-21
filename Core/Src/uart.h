/*
 * uart.h
 *
 *  Created on: Dec 21, 2021
 *      Author: Dell
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_



#endif /* SRC_UART_H_ */


int uart_send (char *buffer, uint16_t length);
int uart_receive (char *buffer, uint16_t length);
int uart_println (char *string);
void uart_get_clock_input (char *buffer);
