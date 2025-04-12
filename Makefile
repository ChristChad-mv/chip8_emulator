.PHONY: clean All

All:
	@echo "----------Building project:[ chip_8 - Debug ]----------"
	@cd "chip_8" && "$(MAKE)" -f  "chip_8.mk"
clean:
	@echo "----------Cleaning project:[ chip_8 - Debug ]----------"
	@cd "chip_8" && "$(MAKE)" -f  "chip_8.mk" clean
