/*
 * sercom_spi_slave.c
 *
 * Created: 11/11/2022 3:45:06 PM
 *  Author: anicha1
 */ 
#include <asf.h>
#include "spi.h"

static struct spi_module module = {0};
static uint8_t rx_data[32];

static void spi_on_recv_callback(struct spi_module *const m)
{
	while (!spi_is_ready_to_read(m))
		delay_cycles_ms(1);

	spi_read_buffer_job(m, rx_data, 32, 0);
	
	printf("%s\n\r", rx_data);
}


static void spi_hardware_init(bool master)
{
	
	struct spi_config cfg;
	
	spi_get_config_defaults(&cfg);

	cfg.pinmux_pad0 = PINMUX_PA16C_SERCOM1_PAD0;
	cfg.pinmux_pad1 = PINMUX_PA17C_SERCOM1_PAD1;
	cfg.pinmux_pad2 = PINMUX_PA18C_SERCOM1_PAD2;
	cfg.pinmux_pad3 = PINMUX_UNUSED;
	cfg.mux_setting = SPI_SIGNAL_MUX_SETTING_I;
	cfg.mode = master ? SPI_MODE_MASTER : SPI_MODE_SLAVE;
	cfg.mode_specific.slave.frame_format = SPI_FRAME_FORMAT_SPI_FRAME;
	cfg.mode_specific.slave.preload_enable = true;
	cfg.transfer_mode = SPI_TRANSFER_MODE_0;
	cfg.master_slave_select_enable = true;
	if (master)
	{
		cfg.mode_specific.master.baudrate = SPI_BAUDRATE;
	}
	
	spi_init(&module, SERCOM1, &cfg);

	spi_enable(&module);
}

void spi_initialize(bool master)
{
	spi_hardware_init(master);
	
	spi_register_callback(&module, spi_on_recv_callback, SPI_CALLBACK_BUFFER_RECEIVED);
	spi_enable_callback(&module, SPI_CALLBACK_BUFFER_RECEIVED);
}


void spi_write_bytes(uint8_t *tx_data, size_t length)
{
	printf("spi: sending a packet of length: %d\n\r", length);
	spi_write_buffer_job(&module, tx_data, length);
	printf("spi: packet sent\n\r");
	
}
