//
// Created by Aleksy Krolczyk on 06/11/2022.
//


#ifndef XOCCHIALI_BLE_UTIL_H
#define XOCCHIALI_BLE_UTIL_H

#include "stdio.h"
#include "driver/touch_pad.h"

#define PLAY_BUTTON TOUCH_PAD_NUM8
#define TOUCH_THRESH_NO_USE   (0)


void wait(int duration_milliseconds);
void configure_play_button(uint8_t);
uint16_t touchpad_value(uint8_t);

#endif //XOCCHIALI_BLE_UTIL_H



