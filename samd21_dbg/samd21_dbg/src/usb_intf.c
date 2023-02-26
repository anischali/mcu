/*
 * usb_intf.c
 *
 * Created: 2/20/2023 8:02:50 PM
 *  Author: anicha1
 */ 

#include <asf.h>
#include "usb_intf.h"


static volatile bool usb_intf_b_vendor_enable = false;

COMPILER_WORD_ALIGNED
static uint8_t pipe[UDI_VENDOR_EPS_SIZE_BULK_FS];


void usb_intf_bulk_out_received(udd_ep_status_t status,
								iram_size_t nb_transfered,
								udd_ep_id_t ep);
void usb_intf_bulk_in_received(udd_ep_status_t status,
								iram_size_t nb_transfered, 
								udd_ep_id_t ep);

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
	usb_intf_bulk_in_received(UDD_EP_TRANSFER_OK, 0, 0);
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


void terminate_transaction(udd_ep_status_t status,
									iram_size_t nb_transfered, udd_ep_id_t ep)
{
	UNUSED(ep);
	if (UDD_EP_TRANSFER_OK != status)
	{
		return; // Transfer aborted, then stop loopback
	}

//	if (nb_transfered % UDI_VENDOR_EPS_SIZE_BULK_FS == 0)
			/*udi_vendor_bulk_in_run(NULL, 0, NULL)*/;
		
	memset(&pipe[0], 0x0, sizeof(pipe));
	/*udi_vendor_bulk_out_run(
			&pipe[0],
			sizeof(pipe),
			usb_intf_bulk_out_received);*/
}

void usb_intf_bulk_in_received(udd_ep_status_t status,
								iram_size_t nb_transfered, 
								udd_ep_id_t ep)
{
	UNUSED(nb_transfered);
	UNUSED(ep);
	if (UDD_EP_TRANSFER_OK != status)
	{
		return; // Transfer aborted, then stop loopback
	}

	/*udi_vendor_bulk_out_run(
	pipe,
	sizeof(pipe),
	usb_intf_bulk_out_received);*/
}


void usb_intf_bulk_out_received(udd_ep_status_t status,
									iram_size_t nb_transfered, 
									udd_ep_id_t ep)
{
	long px_higher_priority_task_woken = 0;

	UNUSED(ep);
	if (UDD_EP_TRANSFER_OK != status)
	{
		return; // Transfer aborted, then stop loopback
	}

	terminate_transaction(UDD_EP_TRANSFER_OK, 0, 0);
}