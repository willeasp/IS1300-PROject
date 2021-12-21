/*
 * display.c
 *
 *  Created on: Dec 19, 2021
 *      Author: Dell
 */
#include "main.h"
#include "spi.h"
#include "error.h"


/**
 * @brief Set the backlight to white
 */
void init_backlight () {
    HAL_GPIO_WritePin(Disp_White_GPIO_Port, Disp_White_Pin, SET);
}


/**
 * @brief Test all backlight colors
 */
void test_backlight () {
    GPIO_TypeDef* ports[] = {Disp_White_GPIO_Port, Disp_Green_GPIO_Port, Disp_Red_GPIO_Port};
    uint16_t pins[] = {Disp_White_Pin, Disp_Green_Pin, Disp_Red_Pin};
    for (int i = 0; i < 3; ++i) {
        HAL_GPIO_WritePin(ports[i], pins[i], SET);
        HAL_Delay(200);
        HAL_GPIO_WritePin(ports[i], pins[i], RESET);
    }
}

/**
 * @brief Split a byte to send to the display
 * @param[in] byte The byte to split into two
 * @param[out] buffer Where to place the two new bytes
 */
void split_byte (uint8_t byte, uint8_t *buffer) {
    buffer[0] = byte & 0x0F;            // lower bits first
    buffer[1] = (byte & 0xF0) >> 4;     // upper bits second
}

/**
 * @brief Send the display data or instructions
 * @param[in] startbyte The byte setting that initiates the transmit
 * @param[in] bytes The bytes that will be sent to the display
 * @param[in] length The number of bytes to send
 */
int display_transmit (uint8_t startbyte, uint8_t *bytes, uint16_t length) {
    /* create message to transmit */
    uint16_t mes_length = length*2 +1; // +1 for start byte
    uint8_t message[mes_length];

    message[0] = startbyte;  // start byte

    uint8_t divided[2]; // for splitting a byte into two
    for (int i = 0; i < length; ++i) {
        split_byte(bytes[i], divided);
        message[1 + i*2] = divided[0];
        message[1 + i*2 +1] = divided[1];
    }

    if (HAL_SPI_Transmit(&hspi2, message, mes_length, 100) != HAL_OK) {
        return 1;
    }
    return 0;
}

/**
 * @brief Send instruction bytes via spi to the display
 * @param[in] instructions A pointer to the instructions to send to the display
 * @param[in] length The number of instructions
 */
int display_send_instruction (uint8_t *instructions, uint16_t length) {
    return display_transmit(0x1F, instructions, length);
}

/**
 * @brief Write characters to the display where the cursor currently are
 * @param characters The characters to write
 * @param length The number of characters
 */
int display_write (uint8_t *characters, uint16_t length) {
    return display_transmit(0b01011111, characters, length);
}

/**
 * @brief Initialise the display
 */
void init_display () {
    HAL_Delay(5);
    init_backlight();

    uint16_t ins_length = 12;
    uint8_t instructions[] = {
        0x3A,
        0x09,
        0x06,
        0x1E,
        0x39,
        0x1B,
        0x6E,
        0x56,
        0x7A,
        0x01,
        0x38,
        0x0F,
    };

    if (display_send_instruction(instructions, ins_length))
        handle_error();

    HAL_Delay(10);

    display_write((uint8_t*) "init", 4);
}







