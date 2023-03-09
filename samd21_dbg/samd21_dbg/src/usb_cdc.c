/*
 * usb_cdc.c
 *
 * Created: 2/20/2023 8:02:50 PM
 *  Author: anicha1
 */ 

#include <asf.h>
#include "usb_cdc.h"
#include "conf_usb.h"



void vbus_event(uint8_t b_vbus_high) {
	if (b_vbus_high)
	{
		// Connect USB device
		udc_attach();
	}
	else
	{
		// Disconnect USB device
		udc_detach();
	}
} 



void usb_cdc_sof_action(void)
{
		return;
}

void usb_cdc_suspend_action(void)
{
	printf("usb: suspending...\n\r");
}


void usb_cdc_resume_action(void)
{
	printf("usb: resuming...\n\r");
}

void init_usb_cdc(void)
{
	stdio_usb_init();
	printf("usb: start...\n\r");
}


bool usb_cdc_enable(uint8_t port)
{
	stdio_usb_enable();
	//uart_open(port);
	return true;
}


void usb_cdc_disable(uint8_t port)
{
	//uart_close(port);
	stdio_usb_disable();
}

