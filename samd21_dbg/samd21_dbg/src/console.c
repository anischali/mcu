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

	cfg.baudrate = 115200;
	cfg.pinmux_pad0 = PINMUX_PA22D_SERCOM5_PAD0;
	cfg.pinmux_pad1 = PINMUX_PA23D_SERCOM5_PAD1;
	cfg.pinmux_pad2 = PINMUX_UNUSED;
	cfg.pinmux_pad3 = PINMUX_UNUSED;
	cfg.mux_setting = USART_RX_1_TX_0_XCK_1;

	stdio_serial_init(&module, SERCOM5, &cfg);

	usart_enable(&module);
 }


 void console_init(void)
 {
	console_hardware_init();
	printf("Serial console init !!!\n\r");
 }