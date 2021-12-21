/*
 * clock.c
 *
 *  Created on: Dec 21, 2021
 *      Author: Dell
 */

#include "main.h"
#include "rtc.h"


static RTC_TimeTypeDef time;

/**
 * @brief start the RTC clock
 */
void start_clock (uint8_t hours, uint8_t minutes, uint8_t seconds) {
    time.Hours = hours;
    time.Minutes = minutes;
    time.Seconds = seconds;

    HAL_RTC_SetDate(&hrtc, NULL, 0);
    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
}

/**
 * @brief Get the current RTC time
 * @return Pointer to the time struct
 */
RTC_TimeTypeDef *get_time () {
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    return &time;
}
