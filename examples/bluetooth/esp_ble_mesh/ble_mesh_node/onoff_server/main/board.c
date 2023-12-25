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
#include "iot_button.h"


#define TAG "BOARD"

#define BUTTON_IO_NUM           0
#define BUTTON_ACTIVE_LEVEL     0

extern void relay_onoff_set(uint8_t pin, uint8_t onoff);

struct _relay_state relay_state[CONFIG_GPIO_RELAY_COUNT] = {
    { STATE_OFF, STATE_OFF, RELAY_1, "relay1"   },
    { STATE_OFF, STATE_OFF, RELAY_2, "relay2"   },
    { STATE_OFF, STATE_OFF, RELAY_3, "relay3"   },
    { STATE_OFF, STATE_OFF, RELAY_4, "relay4"   },
    { STATE_OFF, STATE_OFF, RELAY_5, "relay5"   },
    { STATE_OFF, STATE_OFF, RELAY_6, "relay6"   },
};


void board_relay_operation(uint8_t pin, uint8_t onoff)
{
    for (int i = 0; i < CONFIG_GPIO_RELAY_COUNT; ++i) {
        if (relay_state[i].pin != pin) {
            continue;
        }
        if (onoff == relay_state[i].current) {
            ESP_LOGW(TAG, "realy %s is already %s",
                     relay_state[i].name, (onoff ? "on" : "off"));
            return;
        }
        ESP_LOGI(TAG, "changing state of %s to %s",
                    relay_state[i].name, (onoff ? "on" : "off"));
        gpio_set_level(pin, onoff);
        relay_state[i].current = onoff;
        relay_state[i].previous = (onoff == STATE_ON ? STATE_OFF : STATE_ON);
        return;
    }

    ESP_LOGE(TAG, "relay is not found!");
}

void toggle_board_relay_operation(uint8_t pin)
{
    for (int i = 0; i < CONFIG_GPIO_RELAY_COUNT; ++i) {
        if (relay_state[i].pin != pin) {
            continue;
        }
        if (relay_state[i].current == STATE_ON) {
            board_relay_operation(pin, STATE_OFF);
            return;
        }else{
            board_relay_operation(pin, STATE_ON);
        }
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

static void button_tap_cb(void* arg)
{
    ESP_LOGI(TAG, "tap cb (%s)", (char *)arg);

    for(int i =0; i < CONFIG_GPIO_RELAY_COUNT; ++i){
        toggle_board_relay_operation(relay_state[i].pin);
    }
}


static void board_relay_init(void)
{
    for (int i = 0; i < CONFIG_GPIO_RELAY_COUNT; i++) {
        ESP_LOGI(TAG, "%s : Initializing gpio relay for pin no: 0x%02x", __func__, relay_state[i].pin);
        gpio_reset_pin(relay_state[i].pin);
        gpio_set_direction(relay_state[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(relay_state[i].pin, STATE_OFF);
        relay_state[i].previous = STATE_OFF;
    }
}

static void board_button_init(void)
{
    button_handle_t btn_handle = iot_button_create(BUTTON_IO_NUM, BUTTON_ACTIVE_LEVEL);
    if (btn_handle) {
        iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb, "RELEASE");
    }
}


static void board_led_init(void)
{
    board_button_init();
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
}

void board_init(void)
{
    board_relay_init();
    board_led_init();
}
