CUR_DIR := $(shell pwd)

all:
	python3 $(CUR_DIR)/scripts/kconfig.py

menuconfig:
	menuconfig


clean:
