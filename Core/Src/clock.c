/**
  ******************************************************************************
  * @file    clock.c
  * @brief   This file provides code for starting and getting the rtc time
  * @author William Asp
  ******************************************************************************
  */

#include "main.h"
#include "rtc.h"


/**
 * @brief start the RTC clock
 * @param[in] hours Sets the clock hours
 * @param[in] minutes Sets the clock minuts
 * @param[in] seconds Sets the clock seconds
 */
void start_clock (uint8_t hours, uint8_t minutes, uint8_t seconds) {
    RTC_TimeTypeDef time = {0};
    time.Hours = hours;
    time.Minutes = minutes;
    time.Seconds = seconds;

    /* date has to be set to start the clock */
    HAL_RTC_SetDate(&hrtc, NULL, 0);
    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
}

/**
 * @brief Get the current RTC time
 * @param[out] time The current time
 * @retval time Updated struct with current time
 */
void get_time (RTC_TimeTypeDef *time) {
    HAL_RTC_GetTime(&hrtc, time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, NULL, RTC_FORMAT_BIN);

    /* sad but the RTC started counting beyond :( */
//    if (time->Hours > 23) {
//        start_clock(0, 0, 0);
//        time->Hours = 0;
//        time->Minutes = 0;
//        time->Seconds = 0;
//    }
}
