TARGET := $(shell basename $(CURDIR))

# Configuracion para qemu
QEMUE  := qemu-system-arm
QEMUF  := -M integratorcp -m 16 -nographic
QEMUD  := -S -s

# Configuracion para el compilador
TRIPLET := arm-none-eabi
CC := $(TRIPLET)-gcc
LD := $(TRIPLET)-ld
OC := $(TRIPLET)-objcopy

# Configuracion del objetivo
ARCH := -mthumb -mthumb-interwork -mcpu=arm926ej-s -ggdb
INC  := -I$(shell pwd)/inc

ASFLAGS := $(ARCH) $(INC) -x assembler-with-cpp
CFLAGS  := $(ARCH) $(INC) -Wall -pedantic -Os -ffast-math -ffunction-sections \
			-fdata-sections -fomit-frame-pointer
LDFLAGS := $(ARCH) -Tlink -Wl,--gc-sections,--nmagic,-z,max-page-size=4 -lgcc \
	       -nostartfiles -nostdlib

BUILD   := bin
SOURCE  := src

OBJECTS := $(patsubst $(SOURCE)/%.c, $(BUILD)/%.c.o, \
			$(patsubst $(SOURCE)/%.s, $(BUILD)/%.s.o, \
			$(shell find "$(SOURCE)" -name '*.c' -o -name '*.s')))

.PHONY: all test clean $(TARGET).bin
all: $(TARGET).bin

debug: $(TARGET).elf
	$(QEMUE) $(QEMUF) $(QEMUD) -kernel $^

test: $(TARGET).elf
	$(QEMUE) $(QEMUF) -kernel $^

clean:
	@rm -rf $(TARGET).elf $(TARGET).bin $(BUILD)

$(TARGET).bin: $(TARGET).elf
	$(OC) -O binary $^ $@

$(TARGET).elf: $(OBJECTS)
	@mkdir -p "$(@D)"
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD)/%.c.o: $(SOURCE)/%.c
	@mkdir -p "$(@D)"
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD)/%.s.o: $(SOURCE)/%.s
	@mkdir -p "$(@D)"
	$(CC) -c $(ASFLAGS) -o $@ $<
