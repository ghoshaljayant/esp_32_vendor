#include "nvs_configurator.h"

#define TAG "NVS_CONFIGURATOR"

uint16_t getuint16_val(char* NVS_KEY, uint16_t default_value)
{
    nvs_handle_t my_handle;
    uint16_t value = 0; // value will default to 0, if not set yet in NVS
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err == ESP_OK) {
        // Read
        ESP_LOGI(TAG, "Reading data from NVS ... ");
        
        
        err = nvs_get_u16(my_handle, NVS_KEY, &value);
        switch (err) {
            case ESP_OK:
                ESP_LOGI(TAG, "Done\n");
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                value = default_value;
                ESP_LOGE(TAG, "The value is not initialized yet!\n");
                break;
            default :
                value = default_value;
                ESP_LOGE(TAG, "Error (%s) reading!\n", esp_err_to_name(err));
        }
        // Close
        nvs_close(my_handle);
    } else {
        value = default_value;
    	ESP_LOGI(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
    }
    ESP_LOGI(TAG, "value: 0x%04x",value);
    return value;
}

uint8_t getuint8_val(char* NVS_KEY, uint8_t default_value)
{
    nvs_handle_t my_handle;
    uint8_t value = 0; // value will default to 0, if not set yet in NVS
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err == ESP_OK) {
        // Read
        ESP_LOGI(TAG, "Reading data from NVS ... ");
        
        
        err = nvs_get_u8(my_handle, NVS_KEY, &value);
        switch (err) {
            case ESP_OK:
                ESP_LOGI(TAG, "Done\n");
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                value = default_value;
                ESP_LOGE(TAG, "The value is not initialized yet!\n");
                break;
            default :
                value = default_value;
                ESP_LOGE(TAG, "Error (%s) reading!\n", esp_err_to_name(err));
        }
        // Close
        nvs_close(my_handle);
    } else {
        value = default_value;
    	ESP_LOGI(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
    }
    ESP_LOGI(TAG, "value: 0x%02x",value);
    return value;
}

int getint_val(char* NVS_KEY, int default_value)
{
    nvs_handle_t my_handle;
    int value = 0; // value will default to 0, if not set yet in NVS
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err == ESP_OK) {
        // Read
        ESP_LOGI(TAG, "Reading data from NVS ... ");
        
        
        err = nvs_get_i64(my_handle, NVS_KEY, &value);
        switch (err) {
            case ESP_OK:
                ESP_LOGI(TAG, "Done\n");
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                value = default_value;
                ESP_LOGE(TAG, "The value is not initialized yet!\n");
                break;
            default :
                value = default_value;
                ESP_LOGE(TAG, "Error (%s) reading!\n", esp_err_to_name(err));
        }
        // Close
        nvs_close(my_handle);
    } else {
        value = default_value;
    	ESP_LOGI(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
    }
    ESP_LOGI(TAG, "value: %d",value);
    return value;
}