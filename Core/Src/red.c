/*
 * red.c
 *
 *  Created on: Dec 22, 2021
 *      Author: Dell
 */


#include "main.h"
#include "tim.h"
#include "uart.h"
#include "string.h"

#define CHANNEL TIM_CHANNEL_2

/**
 * @brief Change the PWM pulse width of the red background light
 * @param[in] brightness The brightness of the backlight
 */
void set_brightness (double brightness) {
    brightness *= brightness * brightness;
    uint16_t pulse = (uint16_t) (brightness * (double)0xFFFF);
    __HAL_TIM_SET_COMPARE(&htim3, CHANNEL, pulse);
}
