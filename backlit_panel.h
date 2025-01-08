/*
 * Project: Steampunk Backlit Panel
 * File name: backlit_panel.h
 * Description: Provides the interface for backlit panel initialization and updates.
 *
 * Author: [Your Name]
 * Date: [Current Date]
 * MCU: STM32F756ZG
 * Board: Nucleo-F756
 * IDE: STM32CubeIDE
 */

#ifndef BACKLIT_PANEL_H
#define BACKLIT_PANEL_H

#include <stdint.h>

void BacklitPanel_Init(void);
void BacklitPanel_Update(void);

#endif // BACKLIT_PANEL_H
