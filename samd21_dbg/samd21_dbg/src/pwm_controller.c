/*
 * pwm_interface.c
 *
 * Created: 11/27/2022 9:30:24 AM
 *  Author: anicha1
 */ 
#include <asf.h>
#include "pwm_controller.h"

static struct pwm_port_t pwm_ports[4] =
{
	{
		.index = 0,
		.hw = TCC0,
	 	.pin = PIN_PA04E_TCC0_WO0,
	 	.pinmux = PINMUX_PA04E_TCC0_WO0,
	 	.duty_cycle = 0x7FFF
	 },
	{
		.index = 1,
		.hw = TCC0,
	 	.pin = PIN_PA05E_TCC0_WO1,
	 	.pinmux = PINMUX_PA05E_TCC0_WO1,
	 	.duty_cycle = 0x7FFF},
	{
		.index = 0,
		.hw = TCC1,
	 	.pin = PIN_PA06E_TCC1_WO0,
	 	.pinmux = PINMUX_PA06E_TCC1_WO0,
	 	.duty_cycle = 0x7FFF},
	{
		.index = 1,
		.hw = TCC1,
	 	.pin = PIN_PA07E_TCC1_WO1,
	 	.pinmux = PINMUX_PA07E_TCC1_WO1,
	 	.duty_cycle = 0x7FFF
	}
};



static void pwm_controller_hardware_init(struct pwm_port_t *port);
static void pwm_controller_interrupt_init(struct pwm_port_t *port);
static void tcc_callback_evt(struct tcc_module *const module, void *args);

static void pwm_controller_hardware_init(struct pwm_port_t *port)
{
	struct tcc_config cfg;
	
	tcc_get_config_defaults(&cfg, port->hw);
	
	cfg.counter.period = 0xffff;
	cfg.wave.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	cfg.wave.match[port->index] = port->duty_cycle & 0xffff;
	cfg.pins.enable_wave_out_pin[port->index] = true;
	cfg.pins.wave_out_pin[port->index] = port->pin;
	cfg.pins.wave_out_pin_mux[port->index] = port->pinmux;

	
	tcc_init(&port->module, port->hw, &cfg);
	tcc_enable(&port->module);
}


static void tcc_callback_evt(struct tcc_module *const module, void *args)
{
	struct pwm_port_t *port = (struct pwm_port_t *)args;
	port->duty_cycle = (port->duty_cycle + 0xff) & 0xffff; 
	tcc_set_compare_value(&port->module, port->index, port->duty_cycle);
}


static void pwm_controller_interrupt_init(struct pwm_port_t *port)
{
	tcc_register_callback(&port->module, tcc_callback_evt, port, TCC_CALLBACK_COUNTER_EVENT);
	tcc_enable_callback(&port->module, TCC_CALLBACK_COUNTER_EVENT);
}


void pwm_controller_init()
{
	pwm_controller_hardware_init(&pwm_ports[1]);
	pwm_controller_interrupt_init(&pwm_ports[1]);	
}
