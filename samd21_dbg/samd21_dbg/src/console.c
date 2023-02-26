/*
 * console.c
 *
 * Created: 11/11/2022 3:44:20 PM
 *  Author: anicha1
 */ 
#include <asf.h>
#include "console.h"


/* Structure for USART module connected to EDBG */
struct usart_module usart_module_edbg;

/* Structure for USART parameter configuration */
struct usart_config usart_conf;

/* Data for EDBG communication */
static uint8_t tx_data;
static uint8_t rx_data;

/* USART TX callback flag */
static volatile uint8_t tx_callback_flag = 0;

/**
 * \internal
 * \brief USART interrupt callback function
 *
 * Called by USART driver when transmit is complete.
 *
 * * \param module USART module causing the interrupt (not used)
 */
static void usart_tx_callback(struct usart_module *const module)
{
	tx_callback_flag = 1;
	/* Data ready to be sent */
	if (udi_cdc_is_rx_ready()) {
		tx_data = udi_cdc_getc();
		usart_write_buffer_job(&usart_module_edbg, &tx_data, 1);
	} else {
		/* Fifo empty then Stop UART transmission */
		usart_disable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_TRANSMITTED);
	}
	tx_callback_flag = 0;
}

/**
 * \internal
 * \brief USART interrupt callback function
 *
 * Called by USART driver when receiving is complete.
 *
 * * \param module USART module causing the interrupt (not used)
 */
static void usart_rx_callback(struct usart_module *const module)
{
	/* Transfer UART RX fifo to CDC TX */
	if (!udi_cdc_is_tx_ready()) {
		/* Fifo full */
		udi_cdc_signal_overrun();
	} else {
		udi_cdc_putc(rx_data);
	}

	usart_read_buffer_job(&usart_module_edbg, &rx_data, 1);

	return;
}

void uart_rx_notify(uint8_t port)
{
	UNUSED(port);
	if (!tx_callback_flag) {
		usart_enable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_TRANSMITTED);
		tx_data = udi_cdc_getc();
		usart_write_buffer_job(&usart_module_edbg, &tx_data, 1);
	}
}

void uart_config(uint8_t port, usb_cdc_line_coding_t *cfg)
{
	UNUSED(port);
	/* Configure USART for unit test output */
	usart_get_config_defaults(&usart_conf);
	usart_conf.generator_source = GCLK_GENERATOR_3;

	switch (cfg->bCharFormat) {
	case CDC_STOP_BITS_2:
		usart_conf.stopbits = USART_STOPBITS_2;
		break;

	case CDC_STOP_BITS_1_5:
		usart_conf.stopbits = USART_STOPBITS_1;
		break;

	case CDC_STOP_BITS_1:
	default:
		/* Default stop bit = 1 stop bit */
		usart_conf.stopbits = USART_STOPBITS_1;
		break;
	}

	switch (cfg->bParityType) {
	case CDC_PAR_EVEN:
		usart_conf.parity = USART_PARITY_EVEN;
		break;

	case CDC_PAR_ODD:
		usart_conf.parity = USART_PARITY_ODD;
		break;

	case CDC_PAR_MARK:
		usart_conf.parity = USART_PARITY_NONE;
		break;

	case CDC_PAR_SPACE:
		usart_conf.parity = USART_PARITY_NONE;
		break;

	case CDC_PAR_NONE:
	default:
		usart_conf.parity = USART_PARITY_NONE;
		break;
	}

	switch(cfg->bDataBits) {
	case 5:
		usart_conf.character_size = USART_CHARACTER_SIZE_5BIT;
		break;
	case 6:
		usart_conf.character_size = USART_CHARACTER_SIZE_6BIT;
		break;
	case 7:
		usart_conf.character_size = USART_CHARACTER_SIZE_7BIT;
		break;
	case 8:
	default:
		usart_conf.character_size = USART_CHARACTER_SIZE_8BIT;
		break;
	}

	/* Options for USART. */
	usart_conf.baudrate = LE32_TO_CPU(cfg->dwDTERate);
	usart_conf.pinmux_pad0 = PINMUX_UNUSED;
	usart_conf.pinmux_pad1 = PINMUX_UNUSED;
	usart_conf.pinmux_pad2 = PINMUX_PA10C_SERCOM0_PAD2;
	usart_conf.pinmux_pad3 = PINMUX_PA11C_SERCOM0_PAD3;
	usart_conf.mux_setting = USART_RX_3_TX_2_XCK_3;
	usart_disable(&usart_module_edbg);
	usart_init(&usart_module_edbg, SERCOM0, &usart_conf);
	usart_enable(&usart_module_edbg);

	/* Enable interrupts */
	usart_register_callback(&usart_module_edbg, usart_tx_callback,
			USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_module_edbg, usart_rx_callback,
			USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_module_edbg, USART_CALLBACK_BUFFER_RECEIVED);
	usart_read_buffer_job(&usart_module_edbg, &rx_data, 1);
}

void uart_open(uint8_t port)
{
	UNUSED(port);

	usart_enable(&usart_module_edbg);
}

void uart_close(uint8_t port)
{
	UNUSED(port);
	/* Close RS232 communication */
	usart_disable(&usart_module_edbg);
}
