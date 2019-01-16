BUILD_ROOT = ../../..
OBJS = main.o init.o

LED_DIR = ../libmy_led

LIB_DIRS     += $(LED_DIR)
INCLUDE_DIRS += -I$(LED_DIR)
LDLIBS       += -lmy_led

BINARY_NAME = main

include $(BUILD_ROOT)/common_defs.mk

.PHONY: $(BINARY_NAME)

all: $(BINARY_NAME)

$(BINARY_NAME): $(BINARY_NAME).bin

clean:
	@echo "Cleaning sample directory"
	@rm -f $(OBJS) main.d main.elf main.bin main.elf.map

flash: $(BINARY_NAME)
	$(FLASH_BINARY)
