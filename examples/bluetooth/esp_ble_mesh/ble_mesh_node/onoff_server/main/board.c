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

struct _relay_state relay_state[3] = {
    { STATE_OFF, STATE_OFF, RELAY_1, "relay1"   },
    { STATE_OFF, STATE_OFF, RELAY_2, "relay2" },
    { STATE_OFF, STATE_OFF, RELAY_3, "relay3"  },
};

void board_relay_operation(uint8_t pin, uint8_t onoff)
{
    for (int i = 0; i < 3; i++) {
        if (relay_state[i].pin != pin) {
            continue;
        }
        if (onoff == relay_state[i].previous) {
            ESP_LOGW(TAG, "realy %s is already %s",
                     relay_state[i].name, (onoff ? "on" : "off"));
            return;
        }
        ESP_LOGI(TAG, "changing state of %s to %s",
                    relay_state[i].name, (onoff ? "on" : "off"));
        gpio_set_level(pin, onoff);
        relay_state[i].previous = onoff;
        return;
    }

    ESP_LOGE(TAG, "relay is not found!");
}

void set_self_led_on(uint8_t onoff)
{
    ESP_LOGI(TAG, "set_self_led_on 0x%02x", onoff);
    gpio_set_level(GPIO_NUM_2, onoff);
}

bool is_self_led_on()
{
    return gpio_get_level(GPIO_NUM_2) == 1 ? true : false;
}

void set_gpio_onoff(uint8_t pin, uint8_t onoff)
{
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    gpio_set_level(pin, STATE_OFF);
}

bool get_gpio_onoff(uint8_t pin)
{
    return gpio_get_level(pin);
}

static void board_relay_init(void)
{
    int count = CONFIG_GPIO_RELAY_COUNT;
    for (int i = 0; i < count; i++) {
        gpio_reset_pin(relay_state[i].pin);
        gpio_set_direction(relay_state[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(relay_state[i].pin, STATE_OFF);
        relay_state[i].previous = STATE_OFF;
    }
}

static void board_led_init(void)
{
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
}

void board_init(void)
{
    board_relay_init();
    board_led_init();
}
