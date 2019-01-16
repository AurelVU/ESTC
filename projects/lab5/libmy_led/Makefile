BUILD_ROOT = ../../..

OBJS = my_led.o
DEPS = my_led.d

include $(BUILD_ROOT)/common_defs.mk

LIB = libmy_led.a

all: $(LIB)
	@echo "Done"

$(LIB): $(OBJS)
	@echo "Linking library $@"
	$(MAKE_LIBRARY)

clean:
	@echo "Cleaning library directory"
	@rm -f $(OBJS) $(DEPS) $(LIB)
