all: clean library example

flash_example: example
	@$(MAKE) -C example flash

example: library
	@$(MAKE) -C example all

library:
	@$(MAKE) -C libmy_led all

clean:
	@$(MAKE) -C example clean
	@$(MAKE) -C libmy_led clean
