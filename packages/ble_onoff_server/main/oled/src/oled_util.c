#ifndef _TEXT_C_
#define _TEXT_C_

#include "../include/oled_util.h"
#include "ctype.h"
#include "../include/bt_image.h"
#include "../include/switch_image.h"


/*
 You have to set this config value with menuconfig
 CONFIG_INTERFACE

 for i2c
 CONFIG_MODEL
 CONFIG_SDA_GPIO
 CONFIG_SCL_GPIO
 CONFIG_RESET_GPIO

 for SPI
 CONFIG_CS_GPIO
 CONFIG_DC_GPIO
 CONFIG_RESET_GPIO
*/

#define TAG "SSD1306"
#define OLED_ENABLE true

int animation_reason = 100;


uint8_t inverter(uint8_t val)
{ // this function invert the value
	uint8_t a = (val & 0x01)<<7;
	uint8_t b = (val & 0x02)<<5;
	uint8_t c = (val & 0x04)<<3;
	uint8_t d = (val & 0x08)<<1;
	uint8_t e = (val & 0x10)>>1;
	uint8_t f = (val & 0x20)>>3;
	uint8_t g = (val & 0x40)>>5;
	uint8_t h = (val & 0x80)>>7;

	val = a|b|c|d|e|f|g|h;
	return val;
}

SSD1306_t* registered_oled_device;


void show_image(const uint8_t *image_, int image_size, int page_size)
{	
	uint8_t image[image_size];
	memset(image, 0x00, image_size);

	for(int i =0; i < image_size; ++i){
		image[i] = inverter(image_[i]);
	}
	
	int no_of_pages = image_size / page_size;

	ESP_LOGI(TAG, "show_image 0x%x image_size %d ",image[0], image_size );
	ESP_LOGI(TAG, "show_image 0x%x page_size  %d ",image[0], page_size  );
	ESP_LOGI(TAG, "show_image 0x%x no_of_pages %d",image[0], no_of_pages);

	uint8_t page_img[page_size];
	memset(page_img, 0x00, page_size);

	for(int page_count=0,start_index=0; page_count < no_of_pages; ++page_count, start_index=start_index+page_size){
		memcpy(page_img, image + start_index, page_size);
		ssd1306_display_image(registered_oled_device, page_count, 0, page_img, page_size);
	}
	vTaskDelay(500 / portTICK_PERIOD_MS);
}

void init_animation()
{
	while(1){

		switch(animation_reason){
			case 100:
				show_image(bt_filled,  sizeof(bt_filled), 128);
				show_image(bt_unfilled, sizeof(bt_unfilled),128);
				break;
			case 200:
				show_image(connecting1, sizeof(connecting1), 125);
				show_image(connecting2, sizeof(connecting2), 125);
				break;
			case 300:
				ssd1306_clear_screen(registered_oled_device, false);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				break;
			case ON_ON:
				show_image(on_on, sizeof(on_on), 128);
				break;
			case ON_OFF:
				show_image(on_off, sizeof(on_off), 128);
				break;
			case OFF_ON:
				show_image(off_on, sizeof(off_on), 128);
				break;
			case OFF_OFF:
				show_image(off_off, sizeof(off_off), 128);
				break;
			case -1:
				return;
			default:
				ssd1306_clear_screen(registered_oled_device, false);
				break;
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void set_animation(int reason){
	animation_reason = reason;
}

int number_of_lines = 0;

void oled_init(SSD1306_t* dev_ptr)
{
registered_oled_device = dev_ptr;
#if OLED_ENABLE
#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is i2c");
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(registered_oled_device, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	spi_master_init(registered_oled_device, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
	registered_oled_device->_flip = true;
	ESP_LOGW(TAG, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	ESP_LOGI(TAG, "Panel is 128x64");
	ssd1306_init(registered_oled_device, 128, 64);
#endif // CONFIG_SSD1306_128x64

#if CONFIG_SSD1306_128x32
	ESP_LOGI(TAG, "Panel is 128x32");
	ssd1306_init(registered_oled_device, 128, 32);
#endif // CONFIG_SSD1306_128x32

ssd1306_clear_screen(registered_oled_device, false);
ssd1306_contrast(registered_oled_device, 0xff);

//ESP_LOGI(TAG, "show_image 0x%x bitmap_size: %d",myBitmap[0], sizeof(myBitmap));
//init_animation();

vTaskDelay(3000 / portTICK_PERIOD_MS);

#endif
return;
}


// void send_to_oled(char* text)
// {
// #if OLED_ENABLE
// ESP_LOGI(TAG, "raw_text: %s", text);
// //ssd1306_clear_screen(registered_oled_device, false);
// //ssd1306_contrast(registered_oled_device, 0xff);
// #endif
// return;	
// }

void center_align_wrap_text(char* text, char** lines)
{

	int text_length;
	for (text_length = 0; text[text_length] != '\0'; ++text_length);
	int start_pos = 0;
	int stop_pos = start_pos + 16;
	int line_count = 0;

	while (1)
	{
		int line_end_pos = 0;

		// find position whre line should break.
		for(int i = start_pos; i < stop_pos; ++i)
		{
			if(i >= text_length)
			{
				line_end_pos = i;
				break;
			}

			if(text[i] == ' ')
			{
				line_end_pos = i;
			}
		}

		//copy the line in to lines array
		char line_[16]="";
		int index = 0;
		for (int j = start_pos; j < (start_pos + 16); ++j){
			if(j < line_end_pos){
				line_[index] = text[j];
			}	
			index++;		
		}
		strcpy(lines[line_count], line_);
		ESP_LOGI(TAG,"::::%d   %s",line_count, lines[line_count]);

		//update start position
		start_pos = line_end_pos + 1;
		stop_pos = start_pos + 16;
		if(start_pos > text_length){
			break;
		}else{
			++line_count;
		}
	}

	number_of_lines = line_count + 1;

	ESP_LOGI(TAG, "-------------------");
	for(int l = 0; l < (number_of_lines); l++)
	{
		ESP_LOGI(TAG,"%d   %s",l, lines[l]);
	}
	ESP_LOGI(TAG, "-------------------");

	return;// lines;
}

#endif