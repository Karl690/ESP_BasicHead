#include <Pheonix/configure.h>
#include "main.h"
#ifdef USE_LCD
#ifdef ST7789

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_heap_caps.h"
#include "nvs_flash.h"
esp_lcd_panel_handle_t		panel_handle = NULL;
esp_lcd_panel_io_handle_t io_handle = NULL;
void ST7789_Init()
{
	gpio_set_direction(PIN_LCD_RD, GPIO_MODE_OUTPUT);
	gpio_set_level(PIN_LCD_RD, 1); //blink the backlight
	esp_lcd_i80_bus_handle_t i80_bus = NULL;
	esp_lcd_i80_bus_config_t bus_config = {
		.dc_gpio_num = PIN_LCD_DC,
		.wr_gpio_num = PIN_LCD_WR,
		.clk_src = LCD_CLK_SRC_PLL160M,
		.data_gpio_nums = {
		PIN_LCD_D0,
		PIN_LCD_D1,
		PIN_LCD_D2,
		PIN_LCD_D3,
		PIN_LCD_D4,
		PIN_LCD_D5,
		PIN_LCD_D6,
		PIN_LCD_D7,
	},
		.bus_width = 8,
		.max_transfer_bytes = LCD_WIDTH* LCD_HEIGHT * sizeof(uint16_t),
	};
	esp_lcd_new_i80_bus(&bus_config, &i80_bus);

	esp_lcd_panel_io_i80_config_t io_config = {
		.cs_gpio_num = PIN_LCD_CS,
		.pclk_hz = (16 * 1000 * 1000),
		.trans_queue_depth = 20,
		//.on_color_trans_done = example_notify_lvgl_flush_ready,
		//.user_ctx = &disp_drv,
		.lcd_cmd_bits = 8,
		.lcd_param_bits = 8,
		.dc_levels = {
		.dc_idle_level = 0,
		.dc_cmd_level = 0,
		.dc_dummy_level = 0,
		.dc_data_level = 1,
	},
	};
	ESP_ERROR_CHECK(esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle));
	//esp_lcd_panel_handle_t panel_handle = NULL;
	esp_lcd_panel_dev_config_t panel_config = {
		.reset_gpio_num = PIN_LCD_RES,
		.color_space = ESP_LCD_COLOR_SPACE_RGB,
		.bits_per_pixel = 16,
	};
	esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle);
	esp_lcd_panel_reset(panel_handle);
	esp_lcd_panel_init(panel_handle);

	esp_lcd_panel_invert_color(panel_handle, true);

	esp_lcd_panel_swap_xy(panel_handle, true);
	esp_lcd_panel_mirror(panel_handle, false, true);
	// the gap is LCD panel specific, even panels with the same driver IC, can
	// have different gap value
	esp_lcd_panel_set_gap(panel_handle, 0, 35);
	
	//esp_lcd_panel_disp_on_off(panel_handle, true);
	gpio_set_direction(PIN_LCD_BL, GPIO_MODE_OUTPUT);
	gpio_set_level(PIN_LCD_BL, 1); //blink the backlight
	esp_lcd_panel_disp_on_off(panel_handle, true);
}

void Init_Display()
{
	ST7789_Init();
}

void FillRGBRect(int16_t x, int16_t y, int w, int h, uint16_t* buf)
{
	esp_lcd_panel_draw_bitmap(panel_handle, x, y, x + w, y + h, buf);
}
#endif
#endif