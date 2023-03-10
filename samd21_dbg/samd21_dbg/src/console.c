/*
 * console.c
 *
 * Created: 11/11/2022 3:44:20 PM
 *  Author: anicha1
 */ 
 #include <asf.h>
 #include "console.h"


static struct usart_module module;


 static void console_hardware_init(void)
 {
	struct usart_config cfg;

	usart_get_config_defaults(&cfg);

	cfg.baudrate = 112500;
	cfg.pinmux_pad0 = PINMUX_UNUSED;
	cfg.pinmux_pad1 = PINMUX_UNUSED;
	cfg.pinmux_pad2 = PINMUX_PA10C_SERCOM0_PAD2;
	cfg.pinmux_pad3 = PINMUX_PA11C_SERCOM0_PAD3;
	cfg.mux_setting = USART_RX_2_TX_2_XCK_3;
	cfg.character_size = USART_CHARACTER_SIZE_8BIT;
	cfg.parity = USART_PARITY_NONE;
	cfg.stopbits = USART_STOPBITS_1;

	stdio_serial_init(&module, SERCOM0, &cfg);

	usart_enable(&module);
 }


 void console_init(void)
 {
	console_hardware_init();
	printf("Hello world !!!\n\r");
 }