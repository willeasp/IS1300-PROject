/*
 * clock.c
 *
 *  Created on: Dec 21, 2021
 *      Author: Dell
 */

#include "main.h"
#include "rtc.h"


/**
 * @brief start the RTC clock
 */
void start_clock (uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_TimeTypeDef time;
    time.Hours = hours;
    time.Minutes = minutes;
    time.Seconds = seconds;

    /* date has to be set to start the clock */
    HAL_RTC_SetDate(&hrtc, NULL, 0);
    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
}

/**
 * @brief Get the current RTC time
 * @return Pointer to the time struct
 */
void get_time (RTC_TimeTypeDef *time) {
    HAL_RTC_GetTime(&hrtc, time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, NULL, RTC_FORMAT_BIN);

    /* sad but the RTC started counting beyond :( */
    if (time->Hours > 23) {
        time->Hours = 0;
        time->Minutes = 0;
        time->Seconds = 0;
        HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BIN);
    }
}
