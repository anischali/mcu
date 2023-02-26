/*
 * gyro.c
 *
 * Created: 2/20/2023 7:49:48 PM
 *  Author: anicha1
 */ 
#include "gyro_st_lsm6dsl.h"
#include <i2c_master.h>

static struct i2c_master_module module = {0};
static struct i2c_master_packet pkt = {0};



static enum status_code i2c_master_read(
		struct i2c_master_module *const m,
		struct i2c_master_packet *const packet, 
		bool nack, bool stop)
{
	/* Sanity check */
	Assert(m);
	Assert(m->hw);
	Assert(packet);

	m->send_stop = nack;
	m->send_nack = stop;

	return i2c_master_read_packet(m, packet);
}


static enum status_code i2c_master_write(
		struct i2c_master_module *const m,
		struct i2c_master_packet *const packet, 
		bool nack, bool stop)
{
	/* Sanity check */
	Assert(m);
	Assert(m->hw);
	Assert(packet);

	m->send_stop = stop;
	m->send_nack = nack;

	return i2c_master_write_packet(m, packet);
}



static uint8_t gyro_st_lsm6dsl_read_addr(uint8_t address)
{
	uint8_t val = 0;
	
	I2C_PACKET_PREPARE(&pkt, &address, 1);
	i2c_master_write(&module, &pkt, false, false);
	I2C_PACKET_PREPARE(&pkt, &val, 1);
	i2c_master_read(&module, &pkt, true, true);
	
	return val;
}


static void gyro_st_lsm6dsl_write_byte(uint8_t address, uint8_t value)
{
	uint8_t data[2] = {address, value};
	I2C_PACKET_PREPARE(&pkt, &data, 2);
	i2c_master_write(&module, &pkt, false, true);
}


static void gyro_st_lsm6dsl_read_bytes(uint8_t address, uint8_t *values, size_t length)
{	
	I2C_PACKET_PREPARE(&pkt, &address, 1);
	i2c_master_write(&module, &pkt, false, false);
	I2C_PACKET_PREPARE(&pkt, &values[0], length);
	i2c_master_read(&module, &pkt, true, true);
}


static void gyro_st_lsm6dsl_hardware_init(void)
{
    struct i2c_master_config cfg;
	
	i2c_master_get_config_defaults(&cfg);
	
	cfg.pinmux_pad0 = GYRO_LSM6DSL_SDA_PINMUX_PAD0;
	cfg.pinmux_pad1 = GYRO_LSM6DSL_SCL_PINMUX_PAD1;
	cfg.baud_rate = I2C_MASTER_BAUD_RATE_100KHZ;
	
	i2c_master_init(&module, SERCOM2, &cfg);
	i2c_master_enable(&module);
}


static void gyro_st_lsm6dsl_setup(void)
{
	
}


static void gyro_st_lsm6dsl_interrupt_xl(void)
{
	
}

static void gyro_st_lsm6dsl_interrupt_g(void)
{
	
}

static void gyro_st_lsm6dsl_interrupts_init(void)
{
	struct extint_chan_conf cfg = {0}; 
	
	extint_chan_get_config_defaults(&cfg);
	
	cfg.gpio_pin = GYRO_LSM6DSL_XL_INT1_PIN;
	cfg.gpio_pin_mux = GYRO_LSM6DSL_XL_INT1_PINMUX;
	cfg.filter_input_signal = true;
	cfg.detection_criteria = EXTINT_DETECT_HIGH;
	cfg.wake_if_sleeping = true;
	
	extint_chan_set_config(GYRO_LSM6DSL_XL_INT1_LINE, &cfg);
	
	cfg.gpio_pin = GYRO_LSM6DSL_G_INT2_PIN;
	cfg.gpio_pin_mux = GYRO_LSM6DSL_G_INT2_PINMUX;
	cfg.filter_input_signal = true;
	cfg.detection_criteria = EXTINT_DETECT_HIGH;
	cfg.wake_if_sleeping = true;
	
	extint_chan_set_config(GYRO_LSM6DSL_G_INT2_LINE, &cfg);
	
	extint_chan_clear_detected(GYRO_LSM6DSL_XL_INT1_LINE);
	extint_register_callback(gyro_st_lsm6dsl_interrupt_xl, GYRO_LSM6DSL_XL_INT1_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(GYRO_LSM6DSL_XL_INT1_LINE, EXTINT_CALLBACK_TYPE_DETECT);

	extint_chan_clear_detected(GYRO_LSM6DSL_G_INT2_LINE);
	extint_register_callback(gyro_st_lsm6dsl_interrupt_g, GYRO_LSM6DSL_G_INT2_LINE, EXTINT_CALLBACK_TYPE_DETECT);
	extint_chan_enable_callback(GYRO_LSM6DSL_G_INT2_LINE, EXTINT_CALLBACK_TYPE_DETECT);	
}



void gyro_st_lsm6dsl_init(void)
{
	gyro_st_lsm6dsl_hardware_init();
	gyro_st_lsm6dsl_setup();
	gyro_st_lsm6dsl_interrupts_init();
}