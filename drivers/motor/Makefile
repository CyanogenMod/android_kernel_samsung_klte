#
#  makefile for tspdrv kernel module
#

obj-$(CONFIG_VIBETONZ) += vibrator.o
obj-$(CONFIG_MOTOR_DRV_MAX77803)	+= max77803_haptic.o
obj-$(CONFIG_MOTOR_DRV_MAX77804K)	+= max77804k_haptic.o
obj-$(CONFIG_MOTOR_DRV_MAX77828)	+= max77828_haptic.o
obj-$(CONFIG_MOTOR_DRV_MAX77888)	+= max77888_haptic.o
obj-$(CONFIG_MOTOR_DRV_ISA1400)		+= isa1400_vibrator.o
obj-$(CONFIG_MOTOR_DRV_TSP5000)		+= tspdrv_TSP5000.o
obj-$(CONFIG_HAPTIC_ISA1200)            += tspdrv_isa1200.o
obj-$(CONFIG_DRV2604_VIBRATOR)		+= tspdrv_drv2604.o

vibrator-objs +=tspdrv.o

# Makefile for Vibrator controlled by PMIC Regulator.
obj-$(CONFIG_MSM_VIBRATOR) += msm_vibrator.o

# Makefile for Vibrator controlled by SUB PMIC Regulator.
obj-$(CONFIG_MAX77826_VIBRATOR) += max77826_vibrator.o
