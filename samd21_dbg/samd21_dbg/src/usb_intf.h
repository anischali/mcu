/*
 * usb_intf.h
 *
 * Created: 2/20/2023 8:02:37 PM
 *  Author: anicha1
 */ 


#ifndef USB_INTF_H_
#define USB_INTF_H_



void init_usb_intf(void);
void usb_intf_disable(void);
bool usb_intf_enable(void);
bool usb_intf_setup_out_received(void);
bool usb_intf_setup_in_received(void);
void usb_intf_suspend_action(void);
void usb_intf_resume_action(void);

#endif /* USB_INTF_H_ */