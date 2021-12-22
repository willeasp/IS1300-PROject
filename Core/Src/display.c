/*
 * display.c
 *
 *  Created on: Dec 19, 2021
 *      Author: Dell
 */
#include "main.h"
#include "spi.h"
#include "error.h"
#include "red.h"


GPIO_TypeDef* ports[] = {Disp_White_GPIO_Port, Disp_Green_GPIO_Port};
uint16_t pins[] = {Disp_White_Pin, Disp_Green_Pin};

/**
 * @brief Perform a hardware reset on the display
 */
void hardware_reset () {
    HAL_Delay(5);
    HAL_GPIO_WritePin(Disp_Reset_GPIO_Port, Disp_Reset_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(Disp_Reset_GPIO_Port, Disp_Reset_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
}


/**
 * @brief Test all backlight colors
 */
void test_backlight () {
    // TODO add red pwm
    for (int i = 0; i < 3; ++i) {
        if (i != 2) {
            HAL_GPIO_WritePin(ports[i], pins[i], GPIO_PIN_SET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(ports[i], pins[i], GPIO_PIN_RESET);
        } else {
            set_brightness(1.0);
            HAL_Delay(200);
            set_brightness(0.0);
        }
    }
}


/**
 * @brief Set a backlight color
 */
void set_backlight (uint8_t color, GPIO_PinState state) {
    HAL_GPIO_WritePin(ports[color], pins[color], state);
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
int display_write (char *characters, uint16_t length) {
    return display_transmit(0b01011111, (uint8_t*)characters, length);
}

uint8_t rows[] = {0b10000000, 0b10100000, 0b11000000, 0b11100000};
/**
 * @brief Set the cursor on the display
 * @param row The row to write to
 */
int set_row (uint8_t row) {
    /* the address range of DDARM is 00H-13H, 20H-33H, 40H53H, 60H-73H */
    return display_send_instruction(&rows[row], 1);
}

/**
 * @brief Write text to a specific row on the display
 * @param characters The characters to write
 * @param length The number of characters
 * @param row The row to write to
 */
int display_write_row (char *characters, uint16_t length, uint8_t row) {
    set_row(row);
    return display_write(characters, length);
}

/**
 * @brief Clears the display
 */
int clear_display () {
    uint8_t ins = 0x01;
    return display_send_instruction(&ins, 1);
}

/**
 * @brief Initialise the display
 */
void init_display () {
    hardware_reset();

    test_backlight();
//    init_backlight();

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
        0x0C,       // display on
    };

    if (display_send_instruction(instructions, ins_length))
        handle_error();

    HAL_Delay(5);

    for (int i = 0; i < 4; ++i) {
        set_row(i);
        display_write("0123456789", 10);
    }

    HAL_Delay(500);

    clear_display();

    HAL_Delay(10);
}







