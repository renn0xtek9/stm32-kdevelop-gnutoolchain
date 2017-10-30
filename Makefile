#--------------------------First catch enviroment variable
STM32F10X_STD_PERIPH_PATH:=$(STM32F10X_STD_PERIPH_PATH)
ifndef STM32F10X_STD_PERIPH_PATH
	$(error Please define environment variable STM32F10X_STD_PERIPH_PATH)
endif
STM32F10X_USB_PERIPH_PATH:=$(STM32F10X_USB_PERIPH_PATH)
ifndef STM32F10X_USB_PERIPH_PATH
		$(error Please define environment variable STM32F10X_USB_PERIPH_PATH)
endif
#--------------------------Define Pathes
# TODO here under in device and CORE you might want to change CM3 if not using cortex M3
DEVICE = $(STM32F10X_STD_PERIPH_PATH)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
CORE = $(STM32F10X_STD_PERIPH_PATH)/Libraries/CMSIS/CM3/CoreSupport

PERIPH=StdPeriph_Driver/
BUILDDIR = build



CORETYPE=cortex-m3
#--------------------------Thes are a set of #define pass to the compiler , the density you have to google it
ARCHI=STM32
TYPE=STM32F1 
MCU=STM32F103C8Tx
DENSITY=STM32F10X_MD 



SOURCES += $(shell ls $(PERIPH)/src/*.c)
SOURCES += $(shell ls src/*.c)
SOURCES += startup/startup_stm32.s   




OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

INCLUDES += -I$(DEVICE)/ \
			-I$(CORE)/ \
			-I$(PERIPH)/inc \
			-I$(STM32F10X_USB_PERIPH_PATH)/Libraries/STM32_USB-FS-Device_Driver/inc \
			-Iinc
			
DEFINES += -D$(ARCHI) \
	-D$(TYPE)\
	-D$(DENSITY)\
	-D$(MCU)\
	-DUSE_STDPERIPH_DRIVER \
	-DDEBUG 

ELF = $(BUILDDIR)/program.elf
HEX = $(BUILDDIR)/program.hex
BIN = $(BUILDDIR)/program.bin

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
AR = arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy
 	
CFLAGS  = -O0 -g -Wall -I.\
   -mcpu=$(CORETYPE) -mthumb \
   -mfpu=fpv4-sp-d16 -mfloat-abi=soft \
   $(INCLUDES)  \
   $(DEFINES)

LDSCRIPT = LinkerScript.ld
LDFLAGS += -T$(LDSCRIPT) -mthumb -mcpu=$(CORETYPE) -mfloat-abi=soft -Wl,-Map=output.map -Wl,--gc-section




check: 	
	@echo SOURCES "\n"  $(SOURCES) 
	@echo "\n"
	@echo INCLUDES "\n" $(INCLUDES) 

$(BIN): $(ELF)
	@echo Objet $(OBJCOPY)
	$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	@echo $@
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

all: $(BIN)	

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

clean:
	rm -rf build
