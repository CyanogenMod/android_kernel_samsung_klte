TARGET_NAME := mwlan_aarp
TARGET_KO := $(TARGET_NAME).ko

CLIB := .

obj-m += $(TARGET_NAME).o
$(TARGET_NAME)-objs := \
	a.o\

EXTRA_CFLAGS += -Wall -Wno-uninitialized -I $(PWD)/$(CLIB)
EXTRA_CFLAGS += $(_CFLAGS)
EXTRA_CFLAGS += -DPLAT_VER=$(shell printf 0x%02x%02x%02x $(subst ., ,$(PLATFORM_VERSION))) -DMODEL_$(subst -,_,$(PRODUCT_MODEL))

all:
	make -C $(SRCPATH) M=$(PWD) modules

clean:
	make -C $(SRCPATH) M=$(PWD) clean
