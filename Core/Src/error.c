/*
 * error.c
 *
 *  Created on: Dec 20, 2021
 *      Author: Dell
 */

#include "main.h"

void handle_error( void ) {
    __disable_irq();
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
    while (1)
    {
    }
}
