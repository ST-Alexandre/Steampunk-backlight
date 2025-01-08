/*
 * Project: Steampunk Backlit Panel
 * File name: system_config.h
 * Description: Provides the interface for system configuration functions.
 *
 * Author: [Your Name]
 * Date: [Current Date]
 * MCU: STM32F756ZG
 * Board: Nucleo-F756
 * IDE: STM32CubeIDE
 */

#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

void SystemClock_Config(void);
void GPIO_Init(void);
void PWM_Init(void);
void ADC_Init(void);
void Error_Handler(int error_code);

#endif // SYSTEM_CONFIG_H
