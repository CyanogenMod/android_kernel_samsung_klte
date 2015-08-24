/* Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __FPRINT_SECURE_H
#define __FPRINT_SECURE_H

#if defined(CONFIG_SEC_K_PROJECT) || defined(CONFIG_SEC_KACTIVE_PROJECT)
#ifdef CONFIG_SEC_FACTORY
#undef ENABLE_SENSORS_FPRINT_SECURE
#else
#define ENABLE_SENSORS_FPRINT_SECURE
#endif /* CONFIG_SEC_FACTORY */
#endif /* CONFIG_SEC_K_PROJECT */

#define SPI5_GPIO_CS 25

#endif /* __FPRINT_SECURE_H */
