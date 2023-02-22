/*
 * usb_intf.c
 *
 * Created: 2/20/2023 8:02:50 PM
 *  Author: anicha1
 */ 

#include <asf.h>
#include "usb_intf.h"
#include "conf_usb.h"


static volatile bool usb_intf_b_vendor_enable = false;

void usb_intf_sof_action(void)
{
	if (!usb_intf_b_vendor_enable)
		return;
}

void usb_intf_suspend_action(void)
{
	printf("usb: suspending...\n\r");
}


void usb_intf_resume_action(void)
{
	printf("usb: resuming...\n\r");
}



void init_usb_intf(void)
{
	udc_start();
	printf("usb: start...\n\r");
}


bool usb_intf_enable(void)
{
	usb_intf_b_vendor_enable = true;
#if UDI_VENDOR_EPS_SIZE_BULK_HS

#endif
	return true;
}


void usb_intf_disable(void)
{
	usb_intf_b_vendor_enable = false;
}
bool usb_intf_setup_out_received(void)
{
	return true;
}


bool usb_intf_setup_in_received(void)
{
	return true;
}
