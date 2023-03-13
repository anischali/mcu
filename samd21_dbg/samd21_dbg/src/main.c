/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <stdint.h>
#include "console.h"
#include "usb_cdc.h"
#include "spi.h"
#include "gyro_st_lsm6dsl.h"
#include "pwm_controller.h"

uint8_t msg[] = "Hello World !\n\r";

int main (void)
{
	system_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	console_init();
//	init_usb_cdc();
	spi_initialize(true);
	spi_write_bytes(msg, sizeof(msg));
	pwm_controller_init();
	/* Insert application code here, after the board has been initialized. */
	uint32_t freq = system_gclk_chan_get_hz(USB_GCLK_ID);
	gyro_st_lsm6dsl_init();
	while(1)
	{
	}
}
