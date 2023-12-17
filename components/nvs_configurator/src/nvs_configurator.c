#include "nvs_configurator.h"

#define TAG "NVS_CONFIGURATOR"

uint16_t getuint16_val(void)
{
    nvs_handle_t my_handle;
    uint16_t value = 0; // value will default to 0, if not set yet in NVS
    esp_err_t err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err == ESP_OK) {
        // Read
        ESP_LOGI(TAG, "Reading data from NVS ... ");
        
        
        err = nvs_get_u16(my_handle, "NVS_GROUP_ADD", &value);
        switch (err) {
            case ESP_OK:
                ESP_LOGI(TAG, "Done\n");
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                ESP_LOGE(TAG, "The value is not initialized yet!\n");
                value = CONFIG_NVS_GROUP_ADD;
                break;
            default :
                ESP_LOGE(TAG, "Error (%s) reading!\n", esp_err_to_name(err));
                value = CONFIG_NVS_GROUP_ADD;
        }
        // Close
        nvs_close(my_handle);
    } else {
    	ESP_LOGI(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    return value;
}
