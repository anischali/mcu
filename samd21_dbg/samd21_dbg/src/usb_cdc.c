/*
 * usb_cdc.c
 *
 * Created: 2/20/2023 8:02:50 PM
 *  Author: anicha1
 */ 

#include <asf.h>
#include "usb_cdc.h"
#include "conf_usb.h"



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

void init_usb_cdc(void)
{
	stdio_usb_init();
	if (!udc_include_vbus_monitoring()) {
		// VBUS monitoring is not available on this product
		// thereby VBUS has to be considered as present
		vbus_event (true);
	} 
	printf("usb: start...\n\r");
}


bool usb_cdc_enable(uint8_t port)
{

	return true;
}


void usb_cdc_disable(uint8_t port)
{
}

void usb_cdc_rx_notify(uint8_t port)
{

}

void usb_cdc_tx_empty_notify(uint8_t port)
{

}

void usb_cdc_set_coding_ext(uint8_t port)
{

}

void usb_cdc_set_dtr_ext(uint8_t port)
{

}


void usb_cdc_set_rts_ext(uint8_t port)
{

}