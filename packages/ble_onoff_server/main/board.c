/* board.c - Board-specific hooks */

/*
 * SPDX-FileCopyrightText: 2017 Intel Corporation
 * SPDX-FileContributor: 2018-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "board.h"

#define TAG "BOARD"

#define BOARD_ENABLE true

struct _GPIO_state gpio_state[3] = {
//    CURR_STATE  PREV_STATE  PIN_NO    PIN_NAME    
    { GPIO_UNSET, GPIO_UNSET, LED_BLUE, "blue_led"   },
    { GPIO_UNSET, GPIO_UNSET, IN1_YELLOW, "relay_in_1"   },
    { GPIO_UNSET, GPIO_UNSET, IN2_ORANGE, "relay_in_2"   },
};

void gpio_operation(uint8_t pin, uint8_t onoff)
{
    #if CONFIG_EXTENDED_PROJECT
    for (int i = 0; i < sizeof(gpio_state); i++) {
        if (gpio_state[i].pin != pin) {
            continue;
        }
        if (onoff == gpio_state[i].current) {
            ESP_LOGW(TAG, "led %s is already %s",
                     gpio_state[i].name, (onoff ? "on" : "off"));
            return;
        }
        gpio_state[i].previous = gpio_state[i].current;
        gpio_set_level(pin, onoff);
        gpio_state[i].current = onoff;
        return;
    }

    ESP_LOGE(TAG, "PIN is not found!");
    #endif // CONFIG_EXTENDED_PROJECT
}

int get_gpio_status(uint8_t pin)
{    
    for (int i = 0; i < sizeof(gpio_state); i++) {
        if (gpio_state[i].pin != pin) {
            continue;
        }
        return gpio_state[i].current;
    }
    return GPIO_UNSET;
}

static void board_led_init(void)
{
    #if CONFIG_EXTENDED_PROJECT
    for (int i = 0; i < 3; i++) {
        gpio_reset_pin(gpio_state[i].pin);
        gpio_set_direction(gpio_state[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(gpio_state[i].pin, GPIO_UNSET);
        gpio_state[i].previous = GPIO_UNSET;
    }
    #endif //CONFIG_EXTENDED_PROJECT
}

void board_init(void)
{
    board_led_init();
}
