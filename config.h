/*
 * Project: Steampunk Backlit Panel
 * File name: config.h
 * Description: Provides configuration parameters for the backlit panel project.
 *
 * Author: [Your Name]
 * Date: [Current Date]
 * MCU: STM32F756ZG
 * Board: Nucleo-F756
 * IDE: STM32CubeIDE
 */

#ifndef CONFIG_H
#define CONFIG_H

// System Clock Configuration
#define HSE_VALUE    25000000U /*!< Value of the External oscillator in Hz */
#define HSE_STARTUP_TIMEOUT    100U   /*!< Time out for HSE start up, in ms */
#define HSI_VALUE    16000000U /*!< Value of the Internal oscillator in Hz*/
#define LSI_VALUE  32000U                  /*!< LSI Typical Value in Hz*/
#define LSE_VALUE  32768U    /*!< Value of the External Low Speed oscillator in Hz */
#define LSE_STARTUP_TIMEOUT    5000U   /*!< Time out for LSE start up, in ms */
#define EXTERNAL_CLOCK_VALUE    12288000U /*!< Value of the Internal oscillator in Hz*/

// System Configuration
#define VDD_VALUE                    3300U /*!< Value of VDD in mv */
#define TICK_INT_PRIORITY            0x0FU /*!< tick interrupt priority */
#define USE_RTOS                     1U
#define PREFETCH_ENABLE              1U /* To enable prefetch */
#define ART_ACCELERATOR_ENABLE       1U /* To enable ART Accelerator */

// Backlit Panel Configuration
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0
#define BRIGHTNESS_STEP 1  // Step size for gradual brightness adjustment
#define DEBOUNCE_TIME 200  // Debounce time in milliseconds

#endif // CONFIG_H
