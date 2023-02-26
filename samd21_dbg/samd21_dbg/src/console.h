/*
 * console.h
 *
 * Created: 11/11/2022 3:44:36 PM
 *  Author: anicha1
 */ 


 
 void uart_close(uint8_t port);
 void uart_open(uint8_t port);
 void uart_config(uint8_t port, usb_cdc_line_coding_t *cfg);
 void uart_rx_notify(uint8_t port);