/*
 * uart.c
 *
 *  Created on: Dec 21, 2021
 *      Author: Dell
 */

#include "main.h"
#include "usart.h"
#include "string.h"

#define TIMEOUT 0xFFFFFFFF

/**
 * @brief Send a string over uart
 * @param[in] message The character array to send
 */
int uart_send (char *buffer, uint16_t length) {
    return HAL_UART_Transmit(&huart5, (uint8_t*)buffer, length, TIMEOUT);
}

/**
 * @brief Recieve a string over uart
 * @param[out] buffer The place to write the recieved string
 * @param[in] length The amount of data to read
 */
int uart_receive (char *buffer, uint16_t length) {
    return HAL_UART_Receive(&huart5, (uint8_t *)buffer, length, TIMEOUT);
}

/**
 * @brief send a string line to uart
 * @param string The string to send
 */
int uart_println (char *string) {
    uart_send(string, strlen(string));
    return uart_send("\r\n", 2);
}
