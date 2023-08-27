#ifndef _TEXT_H_
#define _TEXT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"

#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"
#include <pthread.h>

#define ON_ON 401
#define ON_OFF 402
#define OFF_ON 403
#define OFF_OFF 404

void oled_init(SSD1306_t* dev);
void send_to_oled(char* text);
void set_animation(int reason);
void init_animation();
void center_align_wrap_text(char* text, char** lines);

#endif
