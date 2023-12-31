/* board.h - Board-specific hooks */

/*
 * SPDX-FileCopyrightText: 2017 Intel Corporation
 * SPDX-FileContributor: 2018-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "driver/gpio.h"
#include "esp_ble_mesh_defs.h"

#if defined(CONFIG_BLE_MESH_ESP_WROOM_32)
#define BUTTON_TOP_CENTER   GPIO_NUM_13
#define BUTTON_LEFT_TOP     GPIO_NUM_33
#define BUTTON_LEFT_CENTER  GPIO_NUM_26
#define BUTTON_LEFT_BOTTOM  GPIO_NUM_14
#define BUTTON_RIGHT_TOP    GPIO_NUM_27
#define BUTTON_RIGHT_CENTER GPIO_NUM_19
#define BUTTON_RIGHT_BOTTOM GPIO_NUM_21

#define RELAY_1 GPIO_NUM_26
#define RELAY_2 GPIO_NUM_25
#define RELAY_3 GPIO_NUM_33
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#define RELAY_7 GPIO_NUM_22
#elif defined(CONFIG_BLE_MESH_ESP_WROVER)
#define BUTTON_TOP_CENTER   GPIO_NUM_13
#define BUTTON_LEFT_TOP     GPIO_NUM_33
#define BUTTON_LEFT_CENTER  GPIO_NUM_26
#define BUTTON_LEFT_BOTTOM  GPIO_NUM_14
#define BUTTON_RIGHT_TOP    GPIO_NUM_27
#define BUTTON_RIGHT_CENTER GPIO_NUM_19
#define BUTTON_RIGHT_BOTTOM GPIO_NUM_21

#define RELAY_1 GPIO_NUM_26
#define RELAY_2 GPIO_NUM_25
#define RELAY_3 GPIO_NUM_33
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#define RELAY_7 GPIO_NUM_22
#elif defined(CONFIG_BLE_MESH_ESP32C3_DEV)
#define BUTTON_TOP_CENTER   GPIO_NUM_13
#define BUTTON_LEFT_TOP     GPIO_NUM_33
#define BUTTON_LEFT_CENTER  GPIO_NUM_26
#define BUTTON_LEFT_BOTTOM  GPIO_NUM_14
#define BUTTON_RIGHT_TOP    GPIO_NUM_27
#define BUTTON_RIGHT_CENTER GPIO_NUM_19
#define BUTTON_RIGHT_BOTTOM GPIO_NUM_21

#define RELAY_1 GPIO_NUM_26
#define RELAY_2 GPIO_NUM_25
#define RELAY_3 GPIO_NUM_33
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#define RELAY_7 GPIO_NUM_22
#elif defined(CONFIG_BLE_MESH_ESP32S3_DEV)
#define BUTTON_TOP_CENTER   GPIO_NUM_13
#define BUTTON_LEFT_TOP     GPIO_NUM_33
#define BUTTON_LEFT_CENTER  GPIO_NUM_26
#define BUTTON_LEFT_BOTTOM  GPIO_NUM_14
#define BUTTON_RIGHT_TOP    GPIO_NUM_27
#define BUTTON_RIGHT_CENTER GPIO_NUM_19
#define BUTTON_RIGHT_BOTTOM GPIO_NUM_21

#define RELAY_1 GPIO_NUM_26
#define RELAY_2 GPIO_NUM_25
#define RELAY_3 GPIO_NUM_33
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#define RELAY_7 GPIO_NUM_22
#elif defined(CONFIG_BLE_MESH_ESP32C6_DEV)
#define BUTTON_TOP_CENTER   GPIO_NUM_13
#define BUTTON_LEFT_TOP     GPIO_NUM_33
#define BUTTON_LEFT_CENTER  GPIO_NUM_26
#define BUTTON_LEFT_BOTTOM  GPIO_NUM_14
#define BUTTON_RIGHT_TOP    GPIO_NUM_27
#define BUTTON_RIGHT_CENTER GPIO_NUM_19
#define BUTTON_RIGHT_BOTTOM GPIO_NUM_21

#define RELAY_1 GPIO_NUM_26
#define RELAY_2 GPIO_NUM_25
#define RELAY_3 GPIO_NUM_33
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#define RELAY_7 GPIO_NUM_22
#elif defined(CONFIG_BLE_MESH_ESP32H2_DEV)
#define BUTTON_TOP_CENTER   GPIO_NUM_13
#define BUTTON_LEFT_TOP     GPIO_NUM_33
#define BUTTON_LEFT_CENTER  GPIO_NUM_26
#define BUTTON_LEFT_BOTTOM  GPIO_NUM_14
#define BUTTON_RIGHT_TOP    GPIO_NUM_27
#define BUTTON_RIGHT_CENTER GPIO_NUM_19
#define BUTTON_RIGHT_BOTTOM GPIO_NUM_21

#define RELAY_1 GPIO_NUM_26
#define RELAY_2 GPIO_NUM_25
#define RELAY_3 GPIO_NUM_33
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#define RELAY_7 GPIO_NUM_22
#endif

#define STATE_ON  1
#define STATE_OFF 0

struct _relay_state {
    uint8_t current;
    uint8_t previous;
    uint8_t pin;
    char *name;
    uint16_t address;
};

struct _gpio_btn_state {
    uint8_t pin;
    char *msg;
    uint16_t address;
};

void board_relay_operation(uint8_t pin, uint8_t onoff);
void toggle_board_relay_operation(uint8_t pin);
void set_gpio_onoff(uint8_t pin, uint8_t onoff);
bool get_gpio_onoff(uint8_t pin);

void set_self_led_on(uint8_t onoff);
bool is_self_led_on();
void board_init(void);
#endif
