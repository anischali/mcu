/*
 * spi_slave.h
 *
 * Created: 11/11/2022 3:45:36 PM
 *  Author: anicha1
 */ 
#ifndef _SPI_H_
#define _SPI_H_


#include <stdbool.h>


#define SPI_BAUDRATE 1000000


 void spi_initialize(bool master);
 void spi_write_bytes(uint8_t *tx_data, size_t length);
 
 
 #endif