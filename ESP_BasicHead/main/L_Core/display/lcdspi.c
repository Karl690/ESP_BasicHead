#include "K_Core/configure.h"
#if defined(BOARD_T_DISPLAY) || defined(BOARD_103012) 

#include <string.h>

#include "lcdspi.h"

#ifdef BOARD_T_DISPLAY
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_heap_caps.h"

esp_lcd_panel_handle_t		panel_handle = NULL;
esp_lcd_panel_io_handle_t io_handle = NULL;
#else

spi_device_handle_t handle = NULL;
#endif
SPI_LCD_HandleTypeDef LCDHandler;

void SetupMyLCD() 
{
	LCDHandler.RST_Pin = PIN_LCD_RST;
	LCDHandler.MOSI_Pin = PIN_LCD_MOSI;
	LCDHandler.SCK_Pin = PIN_LCD_SCK;
	LCDHandler.CS_Pin = PIN_LCD_CS;
	LCDHandler.RS_Pin = PIN_LCD_RS;
	LCDHandler.SpiFrequency = SPI_MASTER_FREQ_20M;
	
#ifndef BOARD_T_DISPLAY
	esp_err_t ret;
	gpio_reset_pin(LCDHandler.CS_Pin);
	gpio_set_direction(LCDHandler.CS_Pin, GPIO_MODE_OUTPUT);
	gpio_set_level(LCDHandler.CS_Pin, 0);
	
	gpio_reset_pin(LCDHandler.RS_Pin);
	gpio_set_direction(LCDHandler.RS_Pin, GPIO_MODE_OUTPUT);
	gpio_set_level(LCDHandler.RS_Pin, 0);
	
	gpio_reset_pin(LCDHandler.RST_Pin);
	gpio_set_direction(LCDHandler.RST_Pin, GPIO_MODE_OUTPUT);
	gpio_set_level(LCDHandler.RST_Pin, 1);
	vTaskDelay(100);
	gpio_set_level(LCDHandler.RST_Pin, 0);
	vTaskDelay(100);
	gpio_set_level(LCDHandler.RST_Pin, 1);
	vTaskDelay(100);

	spi_bus_config_t buscfg = {
		.mosi_io_num = LCDHandler.MOSI_Pin,
		.miso_io_num = -1,
		.sclk_io_num = LCDHandler.SCK_Pin,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1,
		.max_transfer_sz = 0,
		.flags = 0
	};

	ret = spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
	
	spi_device_interface_config_t devcfg;
	memset(&devcfg, 0, sizeof(devcfg));
	devcfg.clock_speed_hz = LCDHandler.SpiFrequency;
	devcfg.queue_size = 7;
	devcfg.mode = 2;
	devcfg.flags = SPI_DEVICE_NO_DUMMY;

	if (LCDHandler.CS_Pin >= 0) {
		devcfg.spics_io_num = LCDHandler.CS_Pin;
	}
	else {
		devcfg.spics_io_num = -1;
	}
	
	ret = spi_bus_add_device(SPI2_HOST, &devcfg, &handle);
	LCDHandler.Handle = handle;
	assert(ret == ESP_OK);
#else 
	gpio_set_direction(PIN_LCD_RS, GPIO_MODE_OUTPUT);
	gpio_set_level(PIN_LCD_RS, 1); //blink the backlight
	esp_lcd_i80_bus_handle_t i80_bus = NULL;
	esp_lcd_i80_bus_config_t bus_config = {
		.dc_gpio_num = PIN_LCD_SCK,
		.wr_gpio_num = PIN_LCD_MOSI,
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
		.reset_gpio_num = PIN_LCD_RST,
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
	LCDHandler.Handle = panel_handle;
#endif
}

bool lcd_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength)
{
	spi_transaction_t SPITransaction;
	esp_err_t ret;

	if (DataLength > 0) {
		memset(&SPITransaction, 0, sizeof(spi_transaction_t));
		SPITransaction.length = DataLength * 8;
		SPITransaction.tx_buffer = Data;
		ret = spi_device_transmit(SPIHandle, &SPITransaction);
		assert(ret == ESP_OK); 
	}

	return true;
}
#endif