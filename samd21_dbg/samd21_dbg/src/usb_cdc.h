/*
 * usb_intf.h
 *
 * Created: 2/20/2023 8:02:37 PM
 *  Author: anicha1
 */ 


#ifndef USB_INTF_H_
#define USB_INTF_H_
#include <asf.h>


void init_usb_cdc(void);
bool usb_cdc_enable(uint8_t port);
void usb_cdc_disable(uint8_t port);


#endif /* USB_INTF_H_ */