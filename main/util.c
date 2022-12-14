//
// Created by Aleksy Krolczyk on 06/11/2022.
//

#include "util.h"

#include <driver/touch_sensor_common.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/touch_pad.h"
#include "esp_log.h"
#include "sdkconfig.h"

static uint16_t touch_value;

void wait(int duration_milliseconds) {
    vTaskDelay(duration_milliseconds / portTICK_PERIOD_MS);
}

void configure_play_button(uint8_t touch_num) {
    touch_pad_init();
    touch_pad_config(touch_num, TOUCH_THRESH_NO_USE);
}

uint16_t touchpad_value(uint8_t touch_num) {
    touch_pad_read(touch_num, &touch_value);
    return touch_value;
}

void configure_led(uint8_t led_num) {
    gpio_reset_pin(led_num);
    gpio_set_direction(led_num, GPIO_MODE_OUTPUT);
}

void set_led_state(uint8_t led_num, uint8_t led_state) {
    gpio_set_level(led_num, led_state);
}