#--------------------------Thes are a set of #define pass to the compiler , the density you have to google it
ARCHI=STM32
#The Familiy is meant to be the prefix of "_StdPeriph" when you ls $STM32_STDLIBV_4_1/Librairies/ WARNING be careful to not have trailing space at end of foolowing line
FAMILY=STM32F10x
TYPE=STM32F1
MCU=STM32F103C8Tx
DENSITY=STM32F10X_MD 
#--------------------------Define Pathes
# TODO here under in device and CORE you might want to change CM3 if not using cortex M3
DEVICE = $(STM32_STDLIBV_4_1)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
CORE = $(STM32_STDLIBV_4_1)/Libraries/CMSIS/Include
PERIPH=$(STM32_STDLIBV_4_1)/Libraries/$(FAMILY)_StdPeriph_Driver



BUILDDIR = build
CORETYPE=cortex-m3
#--------------------------Define sources 
SOURCES += $(shell ls $(PERIPH)/src/*.c)
SOURCES += $(shell ls src/*.c)
SOURCES += startup/startup_stm32.s 


INCLUDES += -I$(DEVICE)/ \
			-I$(CORE)/ \
 			-I$(PERIPH)/inc \
			-I$(STM32_STDLIBV_4_1)/Libraries/CMSIS/Device/ST/STM32F10x/Include \
			-I$(STM32_STDLIBV_4_1)/Libraries/STM32_USB-FS-Device_Driver/inc \
			-Iinc
			
DEFINES += -D$(ARCHI)\
	-D$(TYPE)\
	-D$(DENSITY)\
	-D$(MCU)\
	-DUSE_STDPERIPH_DRIVER \
	-DDEBUG 
#--------------------------Here under, you should not have to modify anything 
OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
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

#--------------------------Catch enviroment variable
STM32_STDLIBV_4_1:=$(STM32_STDLIBV_4_1)
STM32_STDLIBV_4_1:=$(STM32_STDLIBV_4_1)
STLINK_DEVICE := $(STLINK_DEVICE)
#--------------------------Check excutable 
STFLASH := $(shell command -v st-flash 2> /dev/null)
ARM_NONE_EABI_GDB := $(shell command -v arm-none-eabi-gdb 2>/dev/null)


configure: check
	./configure/copy_startup_file.sh $(STM32_STDLIBV_4_1) $(DENSITY)

check:
	@echo SOURCES "\n"  $(SOURCES) 
	@echo "\n"
	@echo INCLUDES "\n" $(INCLUDES) 
ifeq ($(STLINK_DEVICE),)
	$(error Please define environment variable STLINK_DEVICE like <busnbr>:<devnbr>  e.g 0483:3748)
endif
	@echo STLINK_DEVICE  $(STLINK_DEVICE) 
ifeq ($(ARM_NONE_EABI_GDB),)    # ifeq has to be in first column ,and be carefule about spaces (on space before the '(' )
	$(error arm-none-eabi-gdb is not available please install it. e.g. sudo apt-get install arm-none-eabi-gdb)
endif
	@echo ARM_NONE_EABI_GDB $(ARM_NONE_EABI_GDB)
ifeq ($(STFLASH),)
	$(error "st-flash is not available please install it. Compile from source from https://github.com/texane/stlink")
endif
	@echo STFLASH $(STFLASH)
ifeq ($(STM32_STDLIBV_4_1),)				# TODO remove this since we don't need it in simplest hello world
	$(error Please define environment variable STM32_STDLIBV_4_1)
endif
	@echo STM32F10X_USB_PERIPH_PATH $(STM32F10X_USB_PERIPH_PATH)
ifeq ($(STM32_STDLIBV_4_1),)
	$(error Please define environment variable STM32_STDLIBV_4_1)
endif	
	@echo STM32_STDLIBV_4_1 $(STM32_STDLIBV_4_1)
# 	Check wether all files are here
	./configure/check_files_and_folder.sh $(SOURCES)
# 	Check wether all includes are here
	
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

all: check $(BIN)	

flash: $(BIN)
	sudo st-flash write $(BIN) 0x8000000

clean:
	rm -rf build
