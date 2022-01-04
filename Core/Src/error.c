/**
  ******************************************************************************
  * @file    error.c
  * @brief   This file provides code for handling errors when they appear
  * @author William Asp
  ******************************************************************************
  */

#include "main.h"

/**
 * @brief Show that an error has occured by turning on LD2
 *
 * This function only turns on LD2 then runs in a while loop.
 */
void handle_error () {
    __disable_irq();
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    while (1)
    {
    }
}
