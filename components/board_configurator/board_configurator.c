/* board.c - Board-specific hooks */

/*
 * SPDX-FileCopyrightText: 2017 Intel Corporation
 * SPDX-FileContributor: 2018-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>


#include "esp_log.h"

#include "iot_button.h"
#include "board_configurator.h"

#define TAG "BOARD_CONFIGURATOR"

#define BUTTON_IO_NUM           0
#define BUTTON_ACTIVE_LEVEL     0

extern void board_configurator_relay_send_gen_onoff_set(uint8_t pin, uint8_t onoff);
extern void board_configurator_ble_mesh_send_gen_onoff_set(uint16_t address);

struct _relay_state relay_state[8] = {
    { STATE_OFF, STATE_OFF, RELAY_1, "relay1", 0xC006   },
    { STATE_OFF, STATE_OFF, RELAY_2, "relay2", 0xC001   },
    { STATE_OFF, STATE_OFF, RELAY_3, "relay3", 0xC002   },
    { STATE_OFF, STATE_OFF, RELAY_4, "relay4", 0xC003   },
    { STATE_OFF, STATE_OFF, RELAY_5, "relay5", 0xC004   },
    { STATE_OFF, STATE_OFF, RELAY_6, "relay6", 0xC005   },
    { STATE_OFF, STATE_OFF, RELAY_7, "relayALL", 0xC000   },
};

struct _gpio_btn_state btn_GPIO_Array[8] = {
    { BUTTON_TOP_CENTER,    "BUTTON_TOP_CENTER",     0xC000},
    { BUTTON_LEFT_TOP,      "BUTTON_LEFT_TOP",       0xC006},
    { BUTTON_LEFT_CENTER,   "BUTTON_LEFT_CENTER",    0xC005},
    { BUTTON_LEFT_BOTTOM,   "BUTTON_LEFT_BOTTOM",    0xC004},
    { BUTTON_RIGHT_TOP,     "BUTTON_RIGHT_TOP",      0xC003},
    { BUTTON_RIGHT_CENTER,  "BUTTON_RIGHT_CENTER",   0xC002},
    { BUTTON_RIGHT_BOTTOM,  "BUTTON_RIGHT_BOTTOM",   0xC001},
};

struct _gpio_btn_state btn_board_inbuilt  = { BUTTON_INBUILT_BOARD,    "BOARD_BUTTON",     0xC001};

void board_relay_operation(uint8_t pin, uint8_t onoff)
{
    for (int i = 0; i < 8; ++i) {
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
    for (int i = 0; i < 8; ++i) {
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

static void button_tap_cb(void* arg)
{
    ESP_LOGI(TAG, "tap cb %s", (char *)btn_GPIO_Array[(int)arg].msg);

    int index = (int)arg;

    if(index != -1){
        board_configurator_ble_mesh_send_gen_onoff_set(btn_GPIO_Array[(int)arg].address);
    }else{
        board_configurator_ble_mesh_send_gen_onoff_set(btn_board_inbuilt.address);
    }
}

void board_relay_init(void)
{
    for (int i = 0; i < 8; i++) {
        ESP_LOGI(TAG, "%s : Initializing gpio relay for pin no: 0x%02x", __func__, relay_state[i].pin);
        gpio_reset_pin(relay_state[i].pin);
        gpio_set_direction(relay_state[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(relay_state[i].pin, STATE_OFF);
        relay_state[i].previous = STATE_OFF;
    }
}

void board_button_init(void)
{
    size_t array_length = 7;
    for(int index=0; index < array_length; ++index){
        button_handle_t btn_handle = iot_button_create(btn_GPIO_Array[index].pin, BUTTON_ACTIVE_LEVEL);
        if (btn_handle) {
            iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb, index);
        }
    }
}

static void board_self_button_init(void)
{
    button_handle_t btn_handle = iot_button_create(btn_board_inbuilt.pin, BUTTON_ACTIVE_LEVEL);
    if (btn_handle) {
        iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb, -1);
    }
}

static void board_self_led_init(void)
{    
    gpio_reset_pin(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
}

void board_init(void)
{
    board_self_button_init();
    board_self_led_init();
}
