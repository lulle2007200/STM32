#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include <stdint.h>
#include "backlight_config.h"

#define CONVERT_RGB(R, G, B) ((B) | ((G) << 8) | ((R) << 16))
#define RGB_GET_RED(RGB) ((RGB & 0xff0000) >> 16)
#define RGB_GET_GREEN(RGB) ((RGB & 0xff00) >> 8)
#define RGB_GET_BLUE(RGB) (RGB & 0xff)


void BacklightInit(void);
void BacklightLEDSetColor(uint8_t pPosX, uint8_t pPosY, uint32_t pColor);
void BacklightSetColor(uint32_t pColor);
void BacklightLEDEnable(uint8_t pPosX, uint8_t pPosY);
void BacklightLEDDisable(uint8_t pPosX, uint8_t pPosY);
void BacklightDisable();
void BacklightEnable();
void BacklightToggle();
void BacklightUpdate();

#endif