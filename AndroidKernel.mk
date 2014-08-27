#Android makefile to build kernel as a part of Android Build
PERL		= perl

ifeq ($(TARGET_PREBUILT_KERNEL),)

KERNEL_OUT := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ
KERNEL_CONFIG := $(KERNEL_OUT)/.config
ifeq ($(TARGET_KERNEL_APPEND_DTB), true)
TARGET_PREBUILT_INT_KERNEL := $(KERNEL_OUT)/arch/arm/boot/zImage-dtb
else
TARGET_PREBUILT_INT_KERNEL := $(KERNEL_OUT)/arch/arm/boot/zImage
endif
KERNEL_HEADERS_INSTALL := $(KERNEL_OUT)/usr
KERNEL_MODULES_INSTALL := system
KERNEL_MODULES_OUT := $(TARGET_OUT)/lib/modules
KERNEL_IMG=$(KERNEL_OUT)/arch/arm/boot/Image

USE_MODULE ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MODULES=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))

DTS_NAMES ?= $(shell $(PERL) -e 'while (<>) {$$a = $$1 if /CONFIG_ARCH_((?:MSM|QSD|MPQ)[a-zA-Z0-9]+)=y/; $$r = $$1 if /CONFIG_MSM_SOC_REV_(?!NONE)(\w+)=y/; $$arch = $$arch.lc("$$a$$r ") if /CONFIG_ARCH_((?:MSM|QSD|MPQ)[a-zA-Z0-9]+)=y/} print $$arch;' $(KERNEL_CONFIG))
KERNEL_USE_OF ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_USE_OF=y/) { $$of = "y"; break; } } print $$of;' kernel/arch/arm/configs/$(KERNEL_DEFCONFIG))
LOCALE_KOR ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_LOCALE_KOR=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
LOCALE_JPN ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_LOCALE_JPN=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
JS_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_JS_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
LOCALE_CHN_DUOS ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_H3GDUOS=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
K_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_K_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
H_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_H_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
FRESCO_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_FRESCO_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
F_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_F_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MONDRIAN_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_MONDRIAN_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
VIENNA_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_VIENNA_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
LT03_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_LT03_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MILLET3G_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MILLET3G_EUR=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MILLETLTE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MILLETLTE_OPEN=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MILLETLTE_ATT_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MILLETLTE_ATT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MILLETLTE_VZW_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MILLETLTE_VZW=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MILLETWIFI_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_MILLETWIFI_COMMON=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MATISSE3G_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MATISSE3G_OPEN=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MATISSEWIFI_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_MATISSEWIFI_COMMON=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MATISSELTE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MATISSELTE_OPEN=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MATISSELTE_ATT_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MATISSELTE_ATT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
MATISSELTE_VZW_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_MATISSELTE_VZW=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
AFYONLTE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_AFYONLTE_COMMON=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
ATLANTICLTE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_ATLANTICLTE_COMMON=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
ATLANTIC3G_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_ATLANTIC3G_COMMON=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
PICASSO_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_PICASSO_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
V2_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_V2_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
KS01_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_KS01_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
KACTIVE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_KACTIVE_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
HEAT_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_SEC_HEAT_PROJECT=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
BERLUTI3G_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_BERLUTI3G_EUR=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
BERLUTILTE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_BERLUTILTE_EUR=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
HEAT_DYN_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_HEAT_DYN=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
HEAT_AIO_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_HEAT_AIO=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
VICTORLTE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_VICTORLTE=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
FRESCONEOLTE_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_FRESCONEOLTE_CTC=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
KANAS3G_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_KANAS3G=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
KANAS3G_CMCC_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_KANAS3G_CMCC=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
KANAS3G_CTC_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_KANAS3G_CTC=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))
DEGASLTE_SPR_PROJECT ?= $(shell $(PERL) -e '$$of = "n"; while (<>) { if (/CONFIG_MACH_DEGASLTE_SPR=y/) { $$of = "y"; break; } } print $$of;' $(KERNEL_CONFIG))

ifeq "$(KERNEL_USE_OF)" "y"
ifeq "$(K_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974pro/$(DTS_NAME)pro-sec*.dts)
endif
ifeq "$(VIENNA_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-vienna*.dts)
endif
ifeq "$(LT03_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-lt03*.dts)
endif
ifeq "$(MILLET3G_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/$(DTS_NAME)-sec-millet3geur*.dts)
endif
ifeq "$(MILLETLTE_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-milletlte-*.dts)
endif
ifeq "$(MILLETLTE_ATT_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-milletlteatt*.dts)
endif
ifeq "$(MILLETLTE_VZW_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-milletltevzw*.dts)
endif
ifeq "$(MILLETWIFI_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/$(DTS_NAME)-sec-milletwifieur*.dts)
endif
ifeq "$(MATISSE3G_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/$(DTS_NAME)-sec-matisse3g-*.dts)
endif
ifeq "$(MATISSELTE_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-matisselte-*.dts)
endif
ifeq "$(MATISSELTE_ATT_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-matisselteatt*.dts)
endif
ifeq "$(MATISSELTE_VZW_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-matisseltevzw*.dts)
endif
ifeq "$(AFYONLTE_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-afyonlte*.dts)
endif
ifeq "$(ATLANTICLTE_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8928-sec-atlanticlte*.dts)
endif
ifeq "$(ATLANTIC3G_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8228-sec-atlantic3g*.dts)
endif
ifeq "$(BERLUTI3G_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/$(DTS_NAME)-sec-berluti3geur*.dts)
endif
ifeq "$(BERLUTILTE_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-berlutilte*.dts)
endif
ifeq "$(MATISSEWIFI_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8226-sec-matissewifi*.dts)
endif
ifeq "$(KANAS3G_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8610/$(DTS_NAME)-sec-kanas3g*.dts)
endif
ifeq "$(KANAS3G_CMCC_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8610/$(DTS_NAME)-sec-kanas3g-chn-cmcc*.dts)
endif
ifeq "$(KANAS3G_CTC_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8610/$(DTS_NAME)-sec-kanas3g-chn-ctc*.dts)
endif
ifeq "$(VICTORLTE_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/$(DTS_NAME)-sec-victorlte*.dts)
endif
ifeq "$(DEGASLTE_SPR_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8226/msm8926-sec-degasltespr*.dts)
endif
ifeq "$(HEAT_PROJECT)" "y"
	ifeq "$(HEAT_DYN_PROJECT)" "y"
		DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8610/$(DTS_NAME)-sec-heat-dyn*.dts)
	else
		ifeq "$(HEAT_AIO_PROJECT)" "y"
			DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8610/$(DTS_NAME)-sec-heat-aio*.dts)
		else
			DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8610/$(DTS_NAME)-sec-heat-tfnvzw*.dts)
		endif
	endif
endif
$(info printing $(DTS_NAMES))
$(info printing $(DTS_FILES))

ifeq "$(FRESCO_PROJECT)" "y"
	ifeq "$(LOCALE_KOR)" "y"
		DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-frescolltekor*.dts)
	else
		DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-frescolltekor*.dts)
	endif
endif
ifeq "$(H_PROJECT)" "y"
	ifeq "$(LOCALE_JPN)" "y"
		DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/$(DTS_NAME)-sec-hltejpn*.dts)
	else
		ifeq "$(LOCALE_KOR)" "y"
			DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-hltekor*.dts)
		else
			ifeq "$(LOCALE_CHN_DUOS)" "y"
				DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-h3gchnduos*.dts)
			else
				DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-hlte-*.dts)
			endif
		endif
	endif
endif
ifeq "$(F_PROJECT)" "y"
		DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-fltekor*.dts)
endif
ifeq "$(PICASSO_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-picasso*.dts)
endif
ifeq "$(V2_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-v2*.dts)
endif
ifeq "$(KS01_PROJECT)" "y"
	ifeq "$(LOCALE_KOR)" "y"
		DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974/$(DTS_NAME)-sec-ks01lte*.dts)
	endif
endif
ifeq "$(JS_PROJECT)" "y"
	ifeq "$(LOCALE_JPN)" "y"
		DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/$(DTS_NAME)-sec-js01ltejpn*.dts)
	endif
endif
ifeq "$(KACTIVE_PROJECT)" "y"
DTS_FILES = $(wildcard $(TOP)/kernel/arch/arm/boot/dts/msm8974pro/$(DTS_NAME)pro-ac-sec-kactive*.dts)
endif
DTS_FILE = $(lastword $(subst /, ,$(1)))
DTB_FILE = $(addprefix $(KERNEL_OUT)/arch/arm/boot/,$(patsubst %.dts,%.dtb,$(call DTS_FILE,$(1))))
ZIMG_FILE = $(addprefix $(KERNEL_OUT)/arch/arm/boot/,$(patsubst %.dts,%-zImage,$(call DTS_FILE,$(1))))
KERNEL_ZIMG = $(KERNEL_OUT)/arch/arm/boot/zImage
DTC = $(KERNEL_OUT)/scripts/dtc/dtc

define append-dtb
mkdir -p $(KERNEL_OUT)/arch/arm/boot;\
$(foreach DTS_NAME, $(DTS_NAMES), \
   $(foreach d, $(DTS_FILES), \
      $(DTC) -p 1024 -O dtb -o $(call DTB_FILE,$(d)) $(d); \
      cat $(KERNEL_ZIMG) $(call DTB_FILE,$(d)) > $(call ZIMG_FILE,$(d));))
endef
else

define append-dtb
endef
endif

ifeq ($(TARGET_USES_UNCOMPRESSED_KERNEL),true)
$(info Using uncompressed kernel)
TARGET_PREBUILT_KERNEL := $(KERNEL_OUT)/piggy
else
TARGET_PREBUILT_KERNEL := $(TARGET_PREBUILT_INT_KERNEL)
endif

define mv-modules
mdpath=`find $(KERNEL_MODULES_OUT) -type f -name modules.dep`;\
if [ "$$mdpath" != "" ];then\
mpath=`dirname $$mdpath`;\
ko=`find $$mpath/kernel -type f -name *.ko`;\
for i in $$ko; do mv $$i $(KERNEL_MODULES_OUT)/; done;\
fi
endef

define clean-module-folder
mdpath=`find $(KERNEL_MODULES_OUT) -type f -name modules.dep`;\
if [ "$$mdpath" != "" ];then\
mpath=`dirname $$mdpath`; rm -rf $$mpath;\
fi
endef

#Tweak defconfig for FACTORY KERNEL without additional fac_defcofig
define modi-facdefconfig
cp kernel/arch/arm/configs/$(KERNEL_DEFCONFIG) kernel/arch/arm/configs/factory_defconfig
echo -e "\nCONFIG_SEC_FACTORY=y" >> kernel/arch/arm/configs/factory_defconfig
endef

$(KERNEL_OUT):
	mkdir -p $(KERNEL_OUT)

$(KERNEL_CONFIG): $(KERNEL_OUT)
ifeq ($(SEC_FACTORY_BUILD),true)
	$(modi-facdefconfig)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi- VARIANT_DEFCONFIG=$(VARIANT_DEFCONFIG) DEBUG_DEFCONFIG=$(DEBUG_DEFCONFIG) SELINUX_DEFCONFIG=$(SELINUX_DEFCONFIG) SELINUX_LOG_DEFCONFIG=$(SELINUX_LOG_DEFCONFIG) factory_defconfig TIMA_DEFCONFIG=$(TIMA_DEFCONFIG)
else
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi- VARIANT_DEFCONFIG=$(VARIANT_DEFCONFIG) DEBUG_DEFCONFIG=$(DEBUG_DEFCONFIG) SELINUX_DEFCONFIG=$(SELINUX_DEFCONFIG) SELINUX_LOG_DEFCONFIG=$(SELINUX_LOG_DEFCONFIG) $(KERNEL_DEFCONFIG) TIMA_DEFCONFIG=$(TIMA_DEFCONFIG)
endif
$(KERNEL_OUT)/piggy : $(TARGET_PREBUILT_INT_KERNEL)
	$(hide) gunzip -c $(KERNEL_OUT)/arch/arm/boot/compressed/piggy.gzip > $(KERNEL_OUT)/piggy

$(TARGET_PREBUILT_INT_KERNEL): $(KERNEL_OUT) $(KERNEL_CONFIG) $(KERNEL_HEADERS_INSTALL)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi-
ifeq "$(USE_MODULE)" "y"
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi- modules
	$(MAKE) -C kernel O=../$(KERNEL_OUT) INSTALL_MOD_PATH=../../$(KERNEL_MODULES_INSTALL) INSTALL_MOD_STRIP=1 ARCH=arm CROSS_COMPILE=arm-eabi- modules_install
	$(mv-modules)
	$(clean-module-folder)
endif
	$(append-dtb)

$(KERNEL_HEADERS_INSTALL): $(KERNEL_OUT) $(KERNEL_CONFIG)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi- headers_install

kerneltags: $(KERNEL_OUT) $(KERNEL_CONFIG)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi- tags

kernelconfig: $(KERNEL_OUT) $(KERNEL_CONFIG)
	env KCONFIG_NOTIMESTAMP=true \
	     $(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi- menuconfig
	env KCONFIG_NOTIMESTAMP=true \
	     $(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-eabi- savedefconfig
	cp $(KERNEL_OUT)/defconfig kernel/arch/arm/configs/$(KERNEL_DEFCONFIG)

endif
