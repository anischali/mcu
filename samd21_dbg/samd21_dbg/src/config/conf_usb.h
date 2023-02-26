/**
 * \file
 *
 * \brief USB configuration file
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _CONF_USB_H_
#define _CONF_USB_H_

#include "compiler.h"

#warning You must refill the following definitions with a correct values

/**
 * USB Device Configuration
 * @{
 */

//! Device definition (mandatory)
#define  USB_DEVICE_VENDOR_ID             USB_VID_ATMEL
#define  USB_DEVICE_PRODUCT_ID            USB_PID_ATMEL_ASF_CDC
#define  USB_DEVICE_MAJOR_VERSION         1
#define  USB_DEVICE_MINOR_VERSION         0
#define  USB_DEVICE_POWER                 150 // Consumption on VBUS line (mA)
#define  USB_DEVICE_ATTR                  \
		(USB_CONFIG_ATTR_SELF_POWERED)
// (USB_CONFIG_ATTR_BUS_POWERED)
// (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_SELF_POWERED)
// (USB_CONFIG_ATTR_REMOTE_WAKEUP|USB_CONFIG_ATTR_BUS_POWERED)

//! USB Device string definitions (Optional)
// #define  USB_DEVICE_MANUFACTURE_NAME      "Manufacture name"
// #define  USB_DEVICE_PRODUCT_NAME          "Product name"
// #define  USB_DEVICE_SERIAL_NAME           "12...EF" // Disk SN for MSC

/**
 * Device speeds support
 * @{
 */
//! To define a Low speed device
//#define  USB_DEVICE_LOW_SPEED

//! To authorize the High speed
#if (UC3A3||UC3A4)
//#define  USB_DEVICE_HS_SUPPORT
#endif
//@}

/**
 * USB Device Callbacks definitions (Optional)
 * @{
 */
// #define  UDC_VBUS_EVENT(b_vbus_high)      user_callback_vbus_action(b_vbus_high)
// extern void user_callback_vbus_action(bool b_vbus_high);
// #define  UDC_SOF_EVENT()                  user_callback_sof_action()
// extern void user_callback_sof_action(void);
// #define  UDC_SUSPEND_EVENT()              user_callback_suspend_action()
// extern void user_callback_suspend_action(void);
// #define  UDC_RESUME_EVENT()               user_callback_resume_action()
// extern void user_callback_resume_action(void);
//! Mandatory when USB_DEVICE_ATTR authorizes remote wakeup feature
// #define  UDC_REMOTEWAKEUP_ENABLE()        user_callback_remotewakeup_enable()
// extern void user_callback_remotewakeup_enable(void);
// #define  UDC_REMOTEWAKEUP_DISABLE()       user_callback_remotewakeup_disable()
// extern void user_callback_remotewakeup_disable(void);
//! When a extra string descriptor must be supported
//! other than manufacturer, product and serial string
// #define  UDC_GET_EXTRA_STRING()
//@}

/**
 * USB Device low level configuration
 * When only one interface is used, these configurations are defined by the class module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Control endpoint size
#define  USB_DEVICE_EP_CTRL_SIZE       64

//! Number of interfaces for this device
#define  USB_DEVICE_NB_INTERFACE       2 // 1 or more

//! Total endpoint used by all interfaces
//! Note:
//! It is possible to define an IN and OUT endpoints with the same number on XMEGA product only
//! E.g. MSC class can be have IN endpoint 0x81 and OUT endpoint 0x01
#define  USB_DEVICE_MAX_EP             3 // 0 to max endpoint requested by interfaces
//@}

//@}


/**
 * USB Interface Configuration
 * @{
 */

/**
 * Configuration of CDC interface (if used)
 * @{
 */

//! Number of communication port used
#define  UDI_CDC_PORT_NB 1

//! Interface callback definition

//! Interface callback definition
#define UDC_VBUS_EVENT(b_vbus_high) 			true
#define  UDI_CDC_ENABLE_EXT(port)				usb_cdc_enable(port)
#define  UDI_CDC_DISABLE_EXT(port)				usb_cdc_disable(port)
#define  UDI_CDC_RX_NOTIFY(port)				uart_rx_notify(port)
#define  UDI_CDC_TX_EMPTY_NOTIFY(port)
#define  UDI_CDC_SET_CODING_EXT(port,cfg)		uart_config(port,cfg)
#define  UDI_CDC_SET_DTR_EXT(port,set)
#define  UDI_CDC_SET_RTS_EXT(port,set)

//! Define it when the transfer CDC Device to Host is a low rate (<512000 bauds)
//! to reduce CDC buffers size
#define  UDI_CDC_LOW_RATE

//! Default configuration of communication port
#define  UDI_CDC_DEFAULT_RATE             115200
#define  UDI_CDC_DEFAULT_STOPBITS         CDC_STOP_BITS_1
#define  UDI_CDC_DEFAULT_PARITY           CDC_PAR_NONE
#define  UDI_CDC_DEFAULT_DATABITS         8

/**
 * USB CDC low level configuration
 * In standalone these configurations are defined by the CDC module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoints' numbers used by single or first CDC port
#define  UDI_CDC_DATA_EP_IN_0          (1 | USB_EP_DIR_IN)  // TX
#define  UDI_CDC_DATA_EP_OUT_0         (2 | USB_EP_DIR_OUT) // RX
#define  UDI_CDC_COMM_EP_0             (3 | USB_EP_DIR_IN)  // Notify endpoint

//! Interface numbers used by single or first CDC port
#define  UDI_CDC_COMM_IFACE_NUMBER_0   0
#define  UDI_CDC_DATA_IFACE_NUMBER_0   1
//@}
//@}


#define UDI_COMPOSITE_DESC_T \
   usb_iad_desc_t udi_cdc_iad; \
   udi_cdc_comm_desc_t udi_cdc_comm; \
   udi_cdc_data_desc_t udi_cdc_data; \

#define UDI_COMPOSITE_DESC_FS \
   .udi_cdc_iad               = UDI_CDC_IAD_DESC_0, \
   .udi_cdc_comm              = UDI_CDC_COMM_DESC_0, \
   .udi_cdc_data              = UDI_CDC_DATA_DESC_0_FS, \

#define UDI_COMPOSITE_API \
   &udi_api_cdc_comm,       \
   &udi_api_cdc_data,       \
 
/**
 * Configuration of Class Vendor interface (if used)
 * @{
 */

//! Interface callback definition
//#define  UDI_VENDOR_ENABLE_EXT()          true
//#define  UDI_VENDOR_DISABLE_EXT()
//#define  UDI_VENDOR_SETUP_OUT_RECEIVED()  false
//#define  UDI_VENDOR_SETUP_IN_RECEIVED()   false
/*
 * #define UDI_VENDOR_ENABLE_EXT() my_callback_vendor_enable()
 * extern bool my_callback_vendor_enable(void);
 * #define UDI_VENDOR_DISABLE_EXT() my_callback_vendor_disable()
 * extern void my_callback_vendor_disable(void);
 *
 * #define  UDI_VENDOR_SETUP_OUT_RECEIVED()  my_vendor_setup_out_received()
 * extern bool my_vendor_setup_out_received(void);
 * #define  UDI_VENDOR_SETUP_IN_RECEIVED()   my_vendor_setup_in_received()
 * extern bool my_vendor_setup_in_received(void);
 */

//! endpoints size for full speed
//#define  UDI_VENDOR_EPS_SIZE_INT_FS    64
//#define  UDI_VENDOR_EPS_SIZE_BULK_FS   64
//#define  UDI_VENDOR_EPS_SIZE_ISO_FS   256

//! endpoints size for high speed
//#define  UDI_VENDOR_EPS_SIZE_INT_HS    64
//#define  UDI_VENDOR_EPS_SIZE_BULK_HS  512
//#define  UDI_VENDOR_EPS_SIZE_ISO_HS    64

/**
 * USB Class Vendor low level configuration
 * In standalone these configurations are defined by the Class Vendor module.
 * For composite device, these configuration must be defined here
 * @{
 */
//! Endpoint numbers definition
/*
#define  UDI_VENDOR_EP_INTERRUPT_IN  (1 | USB_EP_DIR_IN)
#define  UDI_VENDOR_EP_INTERRUPT_OUT (2 | USB_EP_DIR_OUT)
#define  UDI_VENDOR_EP_BULK_IN       (3 | USB_EP_DIR_IN)
#define  UDI_VENDOR_EP_BULK_OUT      (4 | USB_EP_DIR_OUT)
#define  UDI_VENDOR_EP_ISO_IN        (5 | USB_EP_DIR_IN)
#define  UDI_VENDOR_EP_ISO_OUT       (6 | USB_EP_DIR_OUT)
*/

//! Interface number
//#define  UDI_VENDOR_IFACE_NUMBER     0
//@}
//@}

//... Eventually add other Interface Configuration

//@}


/**
 * Description of Composite Device
 * @{
 */
//! USB Interfaces descriptor structure
//#define UDI_COMPOSITE_DESC_T

//! USB Interfaces descriptor value for Full Speed
//#define UDI_COMPOSITE_DESC_FS

//! USB Interfaces descriptor value for High Speed
//#define UDI_COMPOSITE_DESC_HS

//! USB Interface APIs
//#define UDI_COMPOSITE_API

/* Example for device with cdc, msc and hid mouse interface
#define UDI_COMPOSITE_DESC_T \
	usb_iad_desc_t udi_cdc_iad; \
	udi_cdc_comm_desc_t udi_cdc_comm; \
	udi_cdc_data_desc_t udi_cdc_data; \
	udi_msc_desc_t udi_msc; \
	udi_hid_mouse_desc_t udi_hid_mouse

//! USB Interfaces descriptor value for Full Speed
#define UDI_COMPOSITE_DESC_FS \
	.udi_cdc_iad               = UDI_CDC_IAD_DESC_0, \
	.udi_cdc_comm              = UDI_CDC_COMM_DESC_0, \
	.udi_cdc_data              = UDI_CDC_DATA_DESC_0_FS, \
	.udi_msc                   = UDI_MSC_DESC_FS, \
	.udi_hid_mouse             = UDI_HID_MOUSE_DESC

//! USB Interfaces descriptor value for High Speed
#define UDI_COMPOSITE_DESC_HS \
	.udi_cdc_iad               = UDI_CDC_IAD_DESC_0, \
	.udi_cdc_comm              = UDI_CDC_COMM_DESC_0, \
	.udi_cdc_data              = UDI_CDC_DATA_DESC_0_HS, \
	.udi_msc                   = UDI_MSC_DESC_HS, \
	.udi_hid_mouse             = UDI_HID_MOUSE_DESC

//! USB Interface APIs
#define UDI_COMPOSITE_API  \
	&udi_api_cdc_comm,       \
	&udi_api_cdc_data,       \
	&udi_api_msc,            \
	&udi_api_hid_mouse
*/

//@}


/**
 * USB Device Driver Configuration
 * @{
 */
//@}

//! The includes of classes and other headers must be done at the end of this file to avoid compile error

/* Example of include for interface
#include "udi_msc.h"
#include "udi_hid_kbd.h"
#include "udi_hid_mouse.h"
#include "udi_cdc.h"
#include "udi_phdc.h"
#include "udi_vendor.h"
*/
/* Declaration of callbacks used by USB
#include "callback_def.h"
*/
#include <udi_cdc.h>
#include <udi_composite_conf.h>
#include "console.h"
#include "usb_cdc.h"
#endif // _CONF_USB_H_
