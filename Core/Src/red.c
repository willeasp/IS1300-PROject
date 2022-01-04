/**
  ******************************************************************************
  * @file    red.c
  * @brief   This file provides code for controlling the brightness of the red
  * backlight.
  * @author William Asp
  ******************************************************************************
  */


#include "main.h"
#include "tim.h"
#include "uart.h"
#include "string.h"

/**
 * @brief The timer channel that is the PWM control
 */
#define CHANNEL TIM_CHANNEL_2

/**
 * @brief Change the PWM pulse width of the red background light
 * @param[in] brightness The brightness of the backlight from 0 to 1
 */
void set_brightness (double brightness) {
    brightness *= brightness * brightness;  // brightness^3
    uint16_t pulse = (uint16_t) (brightness * (double)0xFFFF);
    __HAL_TIM_SET_COMPARE(&htim3, CHANNEL, pulse);
}
