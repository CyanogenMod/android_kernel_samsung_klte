/*
 * w1-gpio interface to platform code
 *
 * Copyright (C) 2007 Ville Syrjala <syrjala@sci.fi>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 */
#ifndef _LINUX_W1_GPIO_H
#define _LINUX_W1_GPIO_H

/**
 * struct w1_gpio_platform_data - Platform-dependent data for w1-gpio
 * @pin: GPIO pin to use
 * @is_open_drain: GPIO pin is configured as open drain
 * @slave_speed: 1 is overdrive mode and zero means standard mode.
 */
struct w1_gpio_msm_platform_data {
	unsigned int pin;
	unsigned int is_open_drain:1;
	void (*enable_external_pullup)(int enable);
	unsigned int ext_pullup_enable_pin;
	unsigned int slave_speed;
};

void w1_ds28el15_fail_count(int result);
#endif /* _LINUX_W1_GPIO_H */
