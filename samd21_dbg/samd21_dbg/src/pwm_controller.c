/*
 * pwm_interface.c
 *
 * Created: 11/27/2022 9:30:24 AM
 *  Author: anicha1
 */ 
#include <asf.h>
#include "pwm_controller.h"

static struct tcc_module tcc_instance;
static uint32_t duty_cycle = 0x7FFF;


static void pwm_controller_hardware_init(void);
static void tcc_callback_evt(struct tcc_module *const module);

static void pwm_controller_hardware_init(void)
{
	struct tcc_config cfg;
	
	tcc_get_config_defaults(&cfg, TCC0);
	
	cfg.counter.period = 0xffff;
	cfg.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
	cfg.compare.match[2] = duty_cycle & 0xffff;
	cfg.pins.enable_wave_out_pin[2] = true;
	cfg.pins.wave_out_pin[2] = PIN_PA18F_TCC0_WO2;
	cfg.pins.wave_out_pin_mux[2] = PINMUX_PA18F_TCC0_WO2;

	
	tcc_init(&tcc_instance, TCC0, &cfg);
	tcc_enable(&tcc_instance);
}


static void tcc_callback_evt(struct tcc_module *const module)
{
	duty_cycle = (duty_cycle + 0xff) & 0xffff; 
	tcc_set_compare_value(&tcc_instance, 2, duty_cycle);
}

void pwm_controller_init(void)
{
	pwm_controller_hardware_init();
	
	tcc_register_callback(&tcc_instance, tcc_callback_evt, TCC_CALLBACK_COUNTER_EVENT);
	tcc_enable_callback(&tcc_instance, TCC_CALLBACK_COUNTER_EVENT);
}
