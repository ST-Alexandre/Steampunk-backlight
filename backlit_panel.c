/*
 * Project: Steampunk Backlit Panel
 * File name: backlit_panel.c
 * Description: Handles the functionality of the backlit panel, including brightness control,
 *              flicker effects, and brightness adjustments based on external conditions.
 *
 * Author: [Your Name]
 * Date: [Current Date]
 * MCU: STM32F756ZG
 * Board: Nucleo-F756
 * IDE: STM32CubeIDE
 */

#include "backlit_panel.h"
#include "stm32f7xx_hal.h"
#include "system_config.h"
#include "config.h"
#include <stdlib.h> // For rand() and srand()
#include <stdio.h>  // For printf()

static uint8_t brightness = MAX_BRIGHTNESS;
static uint8_t target_brightness = MAX_BRIGHTNESS;
static uint8_t is_on = 1; // Assume the panel is on by default
static uint32_t flicker_start_time = 0;
static const uint32_t FLICKER_DURATION = 2000; // Flicker duration in milliseconds
static const uint32_t FLICKER_INTERVAL = 100; // Flicker interval in milliseconds

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2; // Declare htim2 as external

void BacklitPanel_Init(void) {
    // Initialize LDR and flip switch GPIOs here
    HAL_ADC_Start(&hadc1);
    srand(HAL_GetTick()); // Seed the random number generator
}

void BacklitPanel_Update(void) {
    static uint32_t last_debounce_time = 0;
    uint32_t current_time = HAL_GetTick();

    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET && (current_time - last_debounce_time > DEBOUNCE_TIME)) {
        is_on = !is_on;
        last_debounce_time = current_time;
        if (is_on) {
            flicker_start_time = current_time; // Start flickering
        } else {
            brightness = MIN_BRIGHTNESS; // Turn off immediately
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, brightness);
            return;
        }
    }

    if (is_on) {
        // Flicker effect for the first 2 seconds
        if (current_time - flicker_start_time < FLICKER_DURATION) {
            if ((current_time - flicker_start_time) % FLICKER_INTERVAL < FLICKER_INTERVAL / 2) {
                brightness = rand() % (MAX_BRIGHTNESS + 1); // Random brightness level
            } else {
                brightness = MIN_BRIGHTNESS;
            }
        } else {
            // Read LDR value and calculate target brightness
            if (HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY) != HAL_OK) {
                // Error in ADC conversion, handle it appropriately
                printf("Error: ADC conversion failed\n");
                Error_Handler(1); // Return error number 1
            } else {
                uint32_t adc_value = HAL_ADC_GetValue(&hadc1);
                target_brightness = (adc_value / 4095.0) * MAX_BRIGHTNESS;

                // Gradually adjust brightness towards the target brightness
                if (brightness < target_brightness) {
                    brightness = (brightness < target_brightness - BRIGHTNESS_STEP) ? brightness + BRIGHTNESS_STEP : target_brightness;
                } else if (brightness > target_brightness) {
                    brightness = (brightness > target_brightness + BRIGHTNESS_STEP) ? brightness - BRIGHTNESS_STEP : target_brightness;
                }
            }
        }
    }

    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, brightness);
}

void Error_Handler(int error_code) {
    printf("Error Code: %d\n", error_code);
    while (1) {
        // Infinite loop to catch errors
    }
}
