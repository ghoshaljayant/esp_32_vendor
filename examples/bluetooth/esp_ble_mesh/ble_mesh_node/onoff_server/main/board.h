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

#if defined(CONFIG_BLE_MESH_ESP_WROOM_32)
#define RELAY_1 GPIO_NUM_26
#define RELAY_2 GPIO_NUM_25
#define RELAY_3 GPIO_NUM_33
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#elif defined(CONFIG_BLE_MESH_ESP_WROVER)
#define RELAY_1 GPIO_NUM_0
#define RELAY_2 GPIO_NUM_2
#define RELAY_3 GPIO_NUM_4
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#elif defined(CONFIG_BLE_MESH_ESP32C3_DEV)
#define RELAY_1 GPIO_NUM_8
#define RELAY_2 GPIO_NUM_8
#define RELAY_3 GPIO_NUM_8
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#elif defined(CONFIG_BLE_MESH_ESP32S3_DEV)
#define RELAY_1 GPIO_NUM_47
#define RELAY_2 GPIO_NUM_47
#define RELAY_3 GPIO_NUM_47
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#elif defined(CONFIG_BLE_MESH_ESP32C6_DEV)
#define RELAY_1 GPIO_NUM_8
#define RELAY_2 GPIO_NUM_8
#define RELAY_3 GPIO_NUM_8
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#elif defined(CONFIG_BLE_MESH_ESP32H2_DEV)
#define RELAY_1 GPIO_NUM_8
#define RELAY_2 GPIO_NUM_8
#define RELAY_3 GPIO_NUM_8
#define RELAY_4 GPIO_NUM_32
#define RELAY_5 GPIO_NUM_19
#define RELAY_6 GPIO_NUM_21
#endif

#define STATE_ON  1
#define STATE_OFF 0

struct _relay_state {
    uint8_t current;
    uint8_t previous;
    uint8_t pin;
    char *name;
};

void board_relay_operation(uint8_t pin, uint8_t onoff);

void board_init(void);

void set_self_led_on(uint8_t onoff);
bool is_self_led_on();

void set_gpio_onoff(uint8_t pin, uint8_t onoff);
bool get_gpio_onoff(uint8_t pin);

#endif
