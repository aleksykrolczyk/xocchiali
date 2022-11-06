//
// Created by Aleksy Krolczyk on 06/11/2022.
//


#ifndef XOCCHIALI_BLE_UTIL_H
#define XOCCHIALI_BLE_UTIL_H

#include <esp_gatt_defs.h>
#include "stdio.h"
#include "driver/touch_pad.h"

#define PLAY_BUTTON TOUCH_PAD_NUM8
#define TOUCH_THRESH_NO_USE   (0)

#define GATTS_DEMO_CHAR_VAL_LEN_MAX 500
#define PREPARE_BUF_MAX_SIZE        1024
#define CHAR_DECLARATION_SIZE       (sizeof(uint8_t))

#define GATTS_NUM_HANDLE_TEST_A     4

static const uint16_t GATTS_SERVICE_PLAY_UUID = 0x00FF;
static const uint16_t GATTS_CHAR_BUTTON_UUID  = 0xFF01;
static const uint16_t GATTS_CHAR_LED_UUID     = 0xFF02;

#define DEVICE_NAME "Phone Killer v0.1"

void wait(int duration_milliseconds);
void configure_play_button(uint8_t);
uint16_t touchpad_value(uint8_t);

/* Service */

static const uint16_t primary_service_uuid         = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid   = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
static const uint8_t char_prop_read                =  ESP_GATT_CHAR_PROP_BIT_READ;
static const uint8_t char_prop_write               = ESP_GATT_CHAR_PROP_BIT_WRITE;
static const uint8_t char_prop_read_write_notify   = ESP_GATT_CHAR_PROP_BIT_WRITE | ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY;
static const uint8_t heart_measurement_ccc[2]      = {0x00, 0x00};
static const uint8_t char_value[4]                 = {0x11, 0x22, 0x33, 0x44};

/* Attributes State Machine */
enum {
    IDX_SVC,
    IDX_CHARACTERISTIC_BUTTON,
    IDX_CHARACTERISTIC_VALUE_BUTTON,

    IDX_CHARACTERISTIC_LED,
    IDX_CHARACTERISTIC_VALUE_LED,

    GATT_DB_LAST_INDEX,
};

static const esp_gatts_attr_db_t GATT_DB[GATT_DB_LAST_INDEX] = {
        [IDX_SVC] = {
                .attr_control = {ESP_GATT_AUTO_RSP},
                .att_desc = {
                    .uuid_length = ESP_UUID_LEN_16,
                    .uuid_p = (uint8_t *)&primary_service_uuid,
                    .perm = ESP_GATT_PERM_READ,
                    .max_length = sizeof(uint16_t),
                    .length = sizeof(GATTS_SERVICE_PLAY_UUID),
                    .value = (uint8_t *)&GATTS_SERVICE_PLAY_UUID,
                }
        },

        // START BUTTON

        [IDX_CHARACTERISTIC_BUTTON] = {
                .attr_control = { ESP_GATT_AUTO_RSP },
                .att_desc = {
                    .uuid_length = ESP_UUID_LEN_16,
                    .uuid_p = (uint8_t *) &character_declaration_uuid,
                    .perm = ESP_GATT_PERM_READ,
                    .max_length = CHAR_DECLARATION_SIZE,
                    .length = CHAR_DECLARATION_SIZE,
                    .value = (uint8_t *) &char_prop_read_write_notify
                },
        },

        [IDX_CHARACTERISTIC_VALUE_BUTTON] = {
                .attr_control = { ESP_GATT_AUTO_RSP },
                .att_desc = {
                    .uuid_length = ESP_UUID_LEN_16,
                    .uuid_p = (uint8_t * ) &GATTS_CHAR_BUTTON_UUID,
                    .perm = ESP_GATT_PERM_READ,  // | ESP_GATT_PERM_WRITE,
                    .max_length = GATTS_DEMO_CHAR_VAL_LEN_MAX,
                    .length = sizeof(char_value),
                    .value = (uint8_t *) &char_value,
                },
        },

        //  END BUTTON
        //  START LED

        [IDX_CHARACTERISTIC_LED] = {
                .attr_control = { ESP_GATT_AUTO_RSP },
                .att_desc = {
                        .uuid_length = ESP_UUID_LEN_16,
                        .uuid_p = (uint8_t *) &character_declaration_uuid,
                        .perm = ESP_GATT_PERM_READ,
                        .max_length = CHAR_DECLARATION_SIZE,
                        .length = CHAR_DECLARATION_SIZE,
                        .value = (uint8_t *) &char_prop_read_write_notify
                },
        },

        [IDX_CHARACTERISTIC_VALUE_LED] = {
                .attr_control = { ESP_GATT_AUTO_RSP },
                .att_desc = {
                        .uuid_length = ESP_UUID_LEN_16,
                        .uuid_p = (uint8_t * ) &GATTS_CHAR_LED_UUID,
                        .perm =  ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
                        .max_length = GATTS_DEMO_CHAR_VAL_LEN_MAX,
                        .length = sizeof(char_value),
                        .value = (uint8_t *) &char_value,
                },
        },
        // END LED
};




#endif //XOCCHIALI_BLE_UTIL_H



