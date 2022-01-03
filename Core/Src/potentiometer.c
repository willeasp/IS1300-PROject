/**
  ******************************************************************************
  * @file    potentiometer.c
  * @brief   This file provides code for reading the potentiometer value
  * @author William Asp
  ******************************************************************************
  */

#include "main.h"
#include "adc.h"

/**
 * @brief Read the potentiometer value
 * @return The value of the potentiometer
 */
uint32_t get_potentiometer_value () {
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1);
    return HAL_ADC_GetValue(&hadc1);
}
