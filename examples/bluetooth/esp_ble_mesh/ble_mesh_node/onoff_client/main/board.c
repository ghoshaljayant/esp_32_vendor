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

#include "iot_button.h"
#include "board.h"

#define TAG "BOARD"

#define BUTTON_IO_NUM           0
#define BUTTON_ACTIVE_LEVEL     0

extern void example_ble_mesh_send_gen_onoff_set(void);

struct _relay_state relay_state[3] = {
    { STATE_OFF, STATE_OFF, RELAY_1, "red"   },
    { STATE_OFF, STATE_OFF, RELAY_2, "green" },
    { STATE_OFF, STATE_OFF, RELAY_3, "blue"  },
};

void board_relay_operation(uint8_t pin, uint8_t onoff)
{
    for (int i = 0; i < ARRAY_SIZE(relay_state); i++) {
        if (relay_state[i].pin != pin) {
            continue;
        }
        if (onoff == relay_state[i].previous) {
            ESP_LOGW(TAG, "led %s is already %s",
                relay_state[i].name, (onoff ? "on" : "off"));
            return;
        }
        gpio_set_level(pin, onoff);
        relay_state[i].previous = onoff;
        return;
    }
    ESP_LOGE(TAG, "LED is not found!");
}

static void board_relay_init(void)
{
    for (int i = 0; i < ARRAY_SIZE(relay_state); i++) {
        gpio_reset_pin(relay_state[i].pin);
        gpio_set_direction(relay_state[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(relay_state[i].pin, STATE_OFF);
        relay_state[i].previous = STATE_OFF;
    }
}

static void button_tap_cb(void* arg)
{
    ESP_LOGI(TAG, "tap cb (%s)", (char *)arg);

    example_ble_mesh_send_gen_onoff_set();
}

static void board_button_init(void)
{
    button_handle_t btn_handle = iot_button_create(BUTTON_IO_NUM, BUTTON_ACTIVE_LEVEL);
    if (btn_handle) {
        iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb, "RELEASE");
    }
}

void board_init(void)
{
    board_relay_init();
    board_button_init();
}
