/*
 * pwm_controller.h
 *
 * Created: 11/27/2022 9:32:03 AM
 *  Author: anicha1
 */ 


#ifndef PWM_CONTROLLER_H_
#define PWM_CONTROLLER_H_
#include <asf.h>

struct pwm_port_t
{
	uint8_t index;
	uint32_t hw;
	uint32_t pin;
	uint32_t pinmux;
	uint32_t duty_cycle;
	struct tcc_module module;
};

void pwm_controller_init(void);




#endif /* PWM_CONTROLLER_H_ */