/*
 * sercom_spi_slave.c
 *
 * Created: 11/11/2022 3:45:06 PM
 *  Author: anicha1
 */ 
#include <asf.h>
#include "spi_slave.h"

static struct spi_module module = {0};
static uint8_t rx_data[32];

static void spi_on_recv_callback(struct spi_module *const module)
{
	while (!spi_is_ready_to_read(&module))
		delay_cycles_ms(1);

	spi_read_buffer_job(&module, rx_data, 32, 0);
	
	printf("%s\n\r", rx_data);
}


void spi_slave_hardware_init(void)
{
	
	struct spi_config cfg;
	
	spi_get_config_defaults(&cfg);

	cfg.pinmux_pad0 = PINMUX_PA16C_SERCOM1_PAD0;
	cfg.pinmux_pad1 = PINMUX_PA17C_SERCOM1_PAD1;
	cfg.pinmux_pad2 = PINMUX_PA18C_SERCOM1_PAD2;
	cfg.pinmux_pad3 = PINMUX_PA19C_SERCOM1_PAD3;
	cfg.mux_setting = SPI_SIGNAL_MUX_SETTING_I;
	cfg.mode = SPI_MODE_SLAVE;
	cfg.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
	cfg.mode_specific.slave.preload_enable = true;
	
	spi_init(&module, SERCOM1, &cfg);

	spi_enable(&module);
}

void spi_slave_init(void)
{
	spi_slave_hardware_init();
	
	spi_register_callback(&module, spi_on_recv_callback, SPI_CALLBACK_BUFFER_RECEIVED);
}
