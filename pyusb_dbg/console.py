from device import *


def print_callback(data):
    print(data)

dev = device(0x03EB, 0x2404)

dev.activate_interrupt(print_callback)


while True:
    continue