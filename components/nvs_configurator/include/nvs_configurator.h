#ifndef __NVS_CONFIGURATOR_H
#define __NVS_CONFIGURATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "esp_system.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

uint16_t getuint16_val(char* NVS_KEY, uint16_t default_value);
uint16_t getuint8_val(char* NVS_KEY, uint8_t default_value);
uint16_t getint_val(char* NVS_KEY, int default_value);
uint16_t getbool_val(char* NVS_KEY, bool default_value);

#ifdef __cplusplus
}
#endif

#endif /* __NVS_CONFIGURATOR_H */
