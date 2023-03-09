#! /usr/bin/env python3

from os import strerror
from select import select
import usb.core
import usb.util
import usb.control
import threading
#import sys



class device(object):
    def __init__(self, id_vendor, id_product) -> None:
        #print ("idVendor: {} idProduct: {}".format(hex(id_vendor), hex(id_product)))
        self.dev = usb.core.find(idVendor=id_vendor, idProduct=id_product)
        if self.dev is None:
            err = "Device (idVendor: {} idProduct: {}) not found !!!".format(hex(id_vendor), hex(id_product))
            raise ValueError(err)

        self.current_cfg = self.dev.get_active_configuration()
        self.interface = self.current_cfg[1,0]
        
        if self.dev.is_kernel_driver_active(self.interface.bInterfaceNumber):
            self.dev.detach_kernel_driver(self.interface.bInterfaceNumber)
        
        self.dev.set_configuration(1)
        self.dev.set_interface_altsetting(1, 0)
        
        usb.util.claim_interface(self.dev, self.interface)
        self.ep_out = usb.util.find_descriptor(
            self.interface, custom_match = \
            lambda e: \
                usb.util.endpoint_direction(e.bEndpointAddress) == \
                usb.util.ENDPOINT_OUT and e.bmAttributes == usb.util.ENDPOINT_TYPE_BULK) 

        self.ep_in = usb.util.find_descriptor(
            self.interface, custom_match = \
            lambda e: \
                usb.util.endpoint_direction(e.bEndpointAddress) == \
                usb.util.ENDPOINT_IN and e.bmAttributes == usb.util.ENDPOINT_TYPE_BULK)


        self.ep_int_in = usb.util.find_descriptor(
            self.interface, custom_match = \
            lambda e: \
                usb.util.endpoint_direction(e.bEndpointAddress) == \
                usb.util.ENDPOINT_IN and e.bmAttributes == usb.util.ENDPOINT_TYPE_INTR)

        
    def display_active_endpoints(self):
        print("ep_out: \n{}".format(self.ep_out))
        print("ep_in: \n{}".format(self.ep_in))

    def ctrl_transfer(self, bmRequestType, bRequest, wValue=0, wIndex=0,
            data_or_wLength = None, timeout = None):

        return self.dev.ctrl_transfer(bmRequestType, bRequest, wValue, wIndex,
            data_or_wLength, timeout)

    def send_bulk(self, data, _timeout=0):
        return self.ep_out.write(bytes(data), timeout=_timeout)


    def receive_bulk(self, size, _timeout=0):
        buffer = usb.util.create_buffer(size)
        ret = self.ep_in.read(buffer, timeout=_timeout)
        if ret <= 0:
            raise ValueError("Error when reiceiving data errno({})\n{}".format(ret, strerror(ret)))
        
        return buffer[0:ret]

    def receive_interrupt(self):
        buffer = usb.util.create_buffer(64)
        try:
            ret = self.ep_int_in.read(buffer)
            if ret <= 0:
                raise ValueError("Error when reiceiving data errno({})\n{}".format(ret, strerror(ret)))
        except:
            pass

        return buffer[0:ret]

    def activate_interrupt(self, callback):
        
        def thread_call():
            while True:
                try:
                    int_data = self.receive_interrupt()
                    if int_data != None and len(int_data) > 0:
                        callback(int_data)
                except:
                    return

        self.int_thread = threading.Thread(target=thread_call, args=(), daemon=True)
        self.int_thread.start()

    def stop_interrupts(self):
        try:
            self.int_thread.join(1)
        except:
            return
    

    def activate_bulk_continous_reader(self, callback):
        
        def thread_call():
            while True:
                try:
                    blk_data = self.receive_bulk(512)
                    if blk_data != None and len(blk_data) > 0:
                        callback(blk_data)
                except:
                    return

        self.int_thread = threading.Thread(target=thread_call, args=(), daemon=True)
        self.int_thread.start()

    def stop_bulk_continous_reader(self):
        try:
            self.int_thread.join(1)
        except:
            return