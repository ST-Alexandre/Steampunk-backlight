/*
 * Project: Steampunk Backlit Panel
 * File name: main.c
 * Description: Implements a steampunk-style backlit panel with a flickering effect
 *              simulating a malfunctioning discharge bulb, steady lighting after ignition,
 *              and automatic brightness adjustment based on ambient light conditions.
 *
 * Author: [Your Name]
 * Date: [Current Date]
 * MCU: STM32F756ZG
 * Board: Nucleo-F756
 * IDE: STM32CubeIDE
 *
 * Features:
 * - Flicker effect simulating a discharge bulb malfunction.
 * - Ignition pulse and fade-in effect.
 * - Automatic brightness adjustment using an LDR.
 * - Flip switch for on/off control.
 * - RTOS-based task management.
 */

#include "system_config.h"
#include "backlit_panel.h"
#include "cmsis_os2.h" // Include FreeRTOS header
#include "config.h"
#include <stdio.h>  // For printf()

void StartDefaultTask(void *argument);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    GPIO_Init();
    PWM_Init();
    ADC_Init();
    BacklitPanel_Init();

    // Initialize FreeRTOS
    osKernelInitialize();
    osThreadAttr_t defaultTask_attributes = {
        .name = "defaultTask",
        .stack_size = 128 * 4,
        .priority = (osPriority_t) osPriorityNormal,
    };
    osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
    osKernelStart();

    while (1) {
        // This loop should never be reached
    }
}

void StartDefaultTask(void *argument) {
    while (1) {
        BacklitPanel_Update();
        osDelay(10); // Use osDelay for RTOS-based delay
    }
}
