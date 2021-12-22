/*
 * uart.c
 *
 *  Created on: Dec 21, 2021
 *      Author: Dell
 */

#include "main.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"

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
 * @param[in] string The string to send
 */
int uart_println (char *string) {
    uart_send(string, strlen(string));
    return uart_send("\r\n", 2);
}

/**
 * @brief Print a number over uart
 */
int uart_printnum (uint32_t num) {
    char buf[20];
    sprintf(buf, "%lu", num);
    return uart_println(buf);
}

/**
 * @brief Let user input the time
 * @param[out] buffer The buffer to write to
 */
void uart_get_clock_input (char *buffer) {
    uart_println("Please enter the time in HH:MM:SS format!");

    char c;
    uint8_t i = 0;
    while (1) {
        uart_receive(&c, 1);
        /* as long as i < 8 and c != \r
         * If a char 127 (backspace) is written
         * move cursor back */

        /* check if done */
        if (i == 8) {
            if (c == '\r')
                break;
            else if (c != 127)
                continue;
        }

        uart_send(&c, 1);

        /* write to buffer */
        if (c == 127) {
            if (i != 0)
                --i;
        }
        else
            buffer[i++] = c;
    }
}








