/*
 * gyro.h
 *
 * Created: 2/20/2023 7:50:05 PM
 *  Author: anicha1
 */ 


#ifndef GYRO_ST_LSM6DSL_H_
#define GYRO_ST_LSM6DSL_H_
#include <asf.h>

#define GYRO_LSM6DSL_ADDRESS 0x6A

#ifndef PIN_PB09A_EIC_EXTINT_NUM
#define PIN_PB09A_EIC_EXTINT_NUM 9
#endif

#ifndef PIN_PB08A_EIC_EXTINT_NUM
#define PIN_PB08A_EIC_EXTINT_NUM 8
#endif


// SCL and SDA pins
#define GYRO_LSM6DSL_SDA_PINMUX_PAD0 PINMUX_PA08D_SERCOM2_PAD0
#define GYRO_LSM6DSL_SCL_PINMUX_PAD1 PINMUX_PA09D_SERCOM2_PAD1
#define GYRO_LSM6DSL_XL_INT1_PIN PIN_PB09A_EIC_EXTINT9
#define GYRO_LSM6DSL_XL_INT1_PINMUX PINMUX_PB09A_EIC_EXTINT9
#define GYRO_LSM6DSL_XL_INT1_LINE PIN_PB09A_EIC_EXTINT_NUM
#define GYRO_LSM6DSL_G_INT2_PIN PIN_PB08A_EIC_EXTINT8
#define GYRO_LSM6DSL_G_INT2_PINMUX PINMUX_PB08A_EIC_EXTINT8
#define GYRO_LSM6DSL_G_INT2_LINE PIN_PB08A_EIC_EXTINT_NUM

#define I2C_PACKET_PREPARE(p, value, length) \
	memset((p), 0x0, sizeof(struct i2c_master_packet));\
	(p)->address = GYRO_LSM6DSL_ADDRESS;\
	(p)->data = (value);\
	(p)->data_length = length;


#define CTRL1_XL_POWERDOWN_MASK		(0x0F)
#define CTRL1_XL_REG				0x10
#define CTRL1_XL_SET_208HZ_MODE		(0xA0)
#define CTRL6_XL_NORMAL_MODE		(0x10)

#define CTRL2_G_POWERDOWN_MASK		(0x0F)
#define CTRL2_G_MUST_SET_BIT		(0xFE)
#define CTRL2_G_REG					0x11
#define CTRL2_G_SET_208HZ_MODE		(0xA0)
#define CTRL7_G_NORMAL_MODE			(0x80)

#define WHO_AM_I_REG				0x0F 


void gyro_st_lsm6dsl_init(void);


#endif /* GYRO_H_ */