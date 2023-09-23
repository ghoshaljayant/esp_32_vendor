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
#define LED_BLUE GPIO_NUM_2
#define IN1_YELLOW GPIO_NUM_16
#define IN2_ORANGE GPIO_NUM_4

#elif defined(CONFIG_BLE_MESH_ESP_WROVER)
#define LED_BLUE GPIO_NUM_0
#define IN1_YELLOW GPIO_NUM_16
#define IN2_ORANGE GPIO_NUM_4

#elif defined(CONFIG_BLE_MESH_ESP32C3_DEV)
#define LED_BLUE GPIO_NUM_8
#define IN1_YELLOW GPIO_NUM_16
#define IN2_ORANGE GPIO_NUM_4

#elif defined(CONFIG_BLE_MESH_ESP32S3_DEV)
#define LED_BLUE GPIO_NUM_47
#define IN1_YELLOW GPIO_NUM_16
#define IN2_ORANGE GPIO_NUM_4

#else
#define LED_BLUE GPIO_NUM_2
#define IN1_YELLOW GPIO_NUM_16
#define IN2_ORANGE GPIO_NUM_4
#endif

#define GPIO_SET  1
#define GPIO_UNSET 0

struct _GPIO_state {
    uint8_t current;
    uint8_t previous;
    uint8_t pin;
    char *name;
};

void gpio_operation(uint8_t pin, uint8_t onoff);
int get_gpio_status(uint8_t pin);
void board_init(void);

#endif
