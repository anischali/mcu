/*
 * gyro.h
 *
 * Created: 2/20/2023 7:50:05 PM
 *  Author: anicha1
 */ 


#ifndef GYRO_ST_LSM6DSL_H_
#define GYRO_ST_LSM6DSL_H_
#include <asf.h>

struct data_t
{
	uint16_t x;
	uint16_t y;
	uint16_t z;	
};


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


#define CTRL1_XL_POWERDOWN_MASK		0x0F
#define CTRL1_XL_REG				0x10
#define CTRL1_XL_SET_208HZ_MODE		0x50
#define CTRL1_XL_SET_LPF_FILTER		0x02
#define CTRL6_C_REG					0x15
#define CTRL6_C_NORMAL_MODE			0x10
#define CTRL6_C_MUST_SET_BIT		0xFB

#define CTRL2_G_POWERDOWN_MASK		0x0F
#define CTRL2_G_MUST_SET_BIT		0xFE
#define CTRL2_G_REG					0x11
#define CTRL7_G_REG					0x16
#define CTRL2_G_SET_208HZ_MODE		0x50
#define CTRL7_G_NORMAL_MODE			0x80
#define CTRL7_G_MUST_SET_BIT		0xF4

#define CTRL8_XL_REG				0x17
#define CTRL8_XL_MUST_SET_BIT		0xFD
#define CTRL8_XL_SET_COMPOSITE_FILTER 0x08

#define CTRL3_C_REG					0x12
#define CTRL3_C_BDU_ACTIVE_LOW		0x64

#define INT2_CTRL_REG				0x0E
#define INT2_ON_GYRO_RDY			0x02

#define INT1_CTRL_REG				0x0D
#define INT1_ON_XL_RDY				0x01


#define OUTX_L_G_REG				0x22
#define OUTX_H_G_REG				0x23
#define OUTY_L_G_REG				0x24
#define OUTY_H_G_REG				0x25
#define OUTZ_L_G_REG				0x26
#define OUTZ_H_G_REG				0x27


#define OUTX_L_XL_REG				0x28
#define OUTX_H_XL_REG				0x29
#define OUTY_L_XL_REG				0x2A
#define OUTY_H_XL_REG				0x2B
#define OUTZ_L_XL_REG				0x2C
#define OUTZ_H_XL_REG				0x2D

#define WHO_AM_I_REG				0x0F 


void gyro_st_lsm6dsl_init(void);


#endif /* GYRO_H_ */