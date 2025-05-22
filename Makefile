#################################################
#				STM32 Makefile 	(AC6)			#
# 							@ Reglucis			#
#################################################
# @attention
# Because the HAL library only has stm32f4xx_hal_msp.c and system_stm32f4xx.c but no corresponding .h, you must 
# manually add two fucking empty files stm32f4xx_hal_msp.h and system_stm32f4xx.h in the corresponding directory.
#
##-------------------------------------------------------------------------------------------------------------------##
##		(+) Configuration		##
Debug_Flag = 0
InSRAM_Flag = 1
CleanUp_Flag = 0

TARGET = #Project_Name
CC_OPT = 

OPENOCD_INTERFACE = cmsis-dap.cfg
OPENOCD_TARGET = stm32f4x.cfg

##		(+) Source file		##
startup_file = ./Core/startup_stm32f407xx.s

user_source_dir = \
Application\
Sys/Math \
Sys/DWT \
Sys/CCM 

AC6_PATH = D:/DevelopEnvironment/uVision/ARM/ARMCLANG/bin
OPENOCD_ROOT = D:/DevelopEnvironment/OpenOCD
SHELL = %SystemRoot%/System32/WindowsPowerShell/v1.0/powershell.exe

##		(+) Include file			##
C_INCLUDES = \
. \
Core/Inc \
Drivers/STM32F4xx_HAL_Driver/Inc \
Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
Drivers/CMSIS/Include \
Drivers/CMSIS/Device/ST/STM32F4xx/Include \
Drivers/CMSIS-DSP/Include \
Drivers/CMSIS-DSP/PrivateInclude

AS_INCLUDES = 
##		(+) Define			##
# AS defines
AS_DEFS = 
# C defines
C_DEFS = \
_RTE_ \
USE_HAL_DRIVER \
STM32F407xx \
ARM_MATH_CM4

##		(+) MCU			##
CPU = cortex-m4
FPU = fpv4-sp-d16
FLOAT-ABI = hard

##		(+) Compiler		##
STANDARD = c11
WARNING = #(reserve)
##-------------------------------------------------------------------------------------------------------------------##
##		(+) Path			##
BUILD_ROOT_DIR = .Output
CubeMX_source_dir = Core/Src
HAL_source_dir = Drivers/STM32F4xx_HAL_Driver/Src
CMSIS_DSP_ROOT_DIR = Drivers/CMSIS-DSP

CMSIS_DSP_srcs := $(CMSIS_DSP_ROOT_DIR)/Source/BasicMathFunctions/BasicMathFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/MatrixFunctions/MatrixFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/CommonTables/CommonTables.c \
$(CMSIS_DSP_ROOT_DIR)/Source/InterpolationFunctions/InterpolationFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/BayesFunctions/BayesFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/ComplexMathFunctions/ComplexMathFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/QuaternionMathFunctions/QuaternionMathFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/ControllerFunctions/ControllerFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/SVMFunctions/SVMFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/DistanceFunctions/DistanceFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/StatisticsFunctions/StatisticsFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/FastMathFunctions/FastMathFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/SupportFunctions/SupportFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/FilteringFunctions/FilteringFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/TransformFunctions/TransformFunctions.c \
$(CMSIS_DSP_ROOT_DIR)/Source/WindowFunctions/WindowFunctions.c

_obj_dir := $(BUILD_ROOT_DIR)\obj
_CMSIS_DSP_dir := $(BUILD_ROOT_DIR)\CMSIS_DSP
# startup source file
_startup_file = $(subst .s,.o,$(addprefix $(_obj_dir)/, $(notdir $(startup_file))))
# USER source file
_CubeMX_source_src := $(sort $(foreach i, $(CubeMX_source_dir), $(wildcard $(i)/*.c)))
_user_src := $(sort $(foreach i, $(user_source_dir), $(wildcard $(i)/*.c)))
_user_src += $(_CubeMX_source_src)
vpath %.c $(dir $(_user_src))
vpath %.h $(dir $(_user_src))
_user_obj := $(addprefix $(_obj_dir)/, $(notdir $(_user_src:.c=.o)))

vpath %.h $(C_INCLUDES)
# HAL source file
_HAL_src := $(sort $(foreach i, $(HAL_source_dir), $(wildcard $(i)/*.c)))
vpath %.c $(dir $(_HAL_src))
_HAL_obj := $(addprefix $(_obj_dir)/, $(notdir $(_HAL_src:.c=.o)))
# CMSIS_DSP file
vpath %.c $(dir $(CMSIS_DSP_srcs))
_CMSIS_DSP_obj := $(addprefix $(_CMSIS_DSP_dir)/, $(notdir $(CMSIS_DSP_srcs:.c=.o)))

all_obj = $(_startup_file) $(_HAL_obj) $(_user_obj) $(_CMSIS_DSP_obj)
##-------------------------------------------------------------------------------------------------------------------##

COMPILER	= $(AC6_PATH)/armclang.exe
ASSEMBLER	= $(AC6_PATH)/armasm.exe
LINKER		= $(AC6_PATH)/armlink.exe
LIBMANAGER 	= $(AC6_PATH)/armar.exe
FROMELF		= $(AC6_PATH)/fromelf.exe

MCU = --target=arm-arm-none-eabi -mcpu=$(CPU) -mfpu=$(FPU) -mfloat-abi=$(FLOAT-ABI)
LANGAGE = -std=$(STANDARD)
_C_DEFS = $(addprefix -D , $(C_DEFS))                 
_C_INCLUDES = $(addprefix -I , $(C_INCLUDES)) 
_sct = --strict --scatter "$(sct_file)"

CCFLAGS = $(MCU) $(LANGAGE) $(_C_DEFS) $(_C_INCLUDES) $(CC_OPT)
ASFLAGS = -masm=auto $(MCU) $(_C_INCLUDES) $(CC_OPT) 
LIFLAGS = --cpu Cortex-M4.fp.sp $(_sct) --list="$(BUILD_ROOT_DIR)/$(TARGET).map" \
--map --symbols --info unused --info sizes --xref

ifeq ($(InSRAM_Flag), 1)
sct_file = ./Core/F4xx_SRAM.sct
C_DEFS += \
USER_VECT_TAB_ADDRESS \
VECT_TAB_SRAM
else
sct_file = ./Core/F4xx_Flash.sct
endif

ifeq ($(Debug_Flag), 1)
CCFLAGS += -g -gdwarf-4 -O0
ASFLAGS += -g -O0
else
CCFLAGS += -O3 -gdwarf-4
ASFLAGS += -O3
endif

##-------------------------------------------------------------------------------------------------------------------##
#######################################
# all
#######################################
.PHONY: all
ifeq ($(CleanUp_Flag), 1)
all: build program clean
else
all: build program
endif

#######################################
# build
#######################################
.PHONY: build
build: $(BUILD_ROOT_DIR)/$(TARGET).bin
$(BUILD_ROOT_DIR)/$(TARGET).bin: $(BUILD_ROOT_DIR)/$(TARGET).elf
	@ echo converting elf to bin
	@ $(FROMELF) $(BUILD_ROOT_DIR)/$(TARGET).elf --bin -o $(BUILD_ROOT_DIR)/$(TARGET).bin
	@ echo bin file has been created

$(BUILD_ROOT_DIR)/$(TARGET).hex: $(BUILD_ROOT_DIR)/$(TARGET).elf 
	@ echo converting elf to hex
	@ $(FROMELF) $(BUILD_ROOT_DIR)/$(TARGET).elf --i32 -o $(BUILD_ROOT_DIR)/$(TARGET).hex
	@ echo hex file has been created

$(BUILD_ROOT_DIR)/$(TARGET).elf: $(all_obj)
	@ echo Linking Targer: $@ By $(sct_file)
	@ $(LINKER) $(all_obj) $(LIFLAGS) -o $@
	@ echo elf file has been created
# @ DEL .Output/obj/MyMathLib.o

$(_startup_file): $(startup_file) makefile | $(_obj_dir)
	@ echo Building $@
	@ $(COMPILER) -c $(ASFLAGS) $< -o $(_startup_file) -Wa,armasm,--diag_suppress=A1950W

$(_obj_dir)/%.o: %.c %.h makefile | $(_obj_dir)
	@ echo Building $@
	@ $(COMPILER) -c $(CCFLAGS) $< -o $@
$(_CMSIS_DSP_dir)/%.o: %.c makefile | $(_CMSIS_DSP_dir)
	@ echo Building $@
	@ $(COMPILER) -c $(CCFLAGS) $< -o $@
$(_obj_dir): | $(BUILD_ROOT_DIR)
	@ $(shell mkdir $(_obj_dir))
$(_CMSIS_DSP_dir): | $(BUILD_ROOT_DIR)
	@ $(shell mkdir $(_CMSIS_DSP_dir))
$(BUILD_ROOT_DIR):
	@ $(shell mkdir $(BUILD_ROOT_DIR))
	@ $(shell attrib $(BUILD_ROOT_DIR) +h)

#######################################
# program (openocd)
#######################################
OPENOCD_EXE = $(OPENOCD_ROOT)\bin\openocd.exe

.PHONY: program
ifeq ($(InSRAM_Flag), 1)
OPENOCD_FLASH_START = 0x20000000
program: $(BUILD_ROOT_DIR)/$(TARGET).bin
	@ $(OPENOCD_EXE) \
	-f $(OPENOCD_ROOT)/share/openocd/scripts/interface/$(OPENOCD_INTERFACE) \
	-f $(OPENOCD_ROOT)/share/openocd/scripts/target/$(OPENOCD_TARGET) \
	-d0 \
	-c "adapter speed 8000" \
	-c "init" \
	-c "load_image $(BUILD_ROOT_DIR)/$(TARGET).bin $(OPENOCD_FLASH_START)" \
	-c "reset run" \
	-c "exit"
else
OPENOCD_FLASH_START = 0x08000000
program: $(BUILD_ROOT_DIR)/$(TARGET).bin
	@ $(OPENOCD_EXE) \
	-f $(OPENOCD_ROOT)/share/openocd/scripts/interface/$(OPENOCD_INTERFACE) \
	-f $(OPENOCD_ROOT)/share/openocd/scripts/target\$(OPENOCD_TARGET) \
	-d0 \
	-c "transport select swd" \
	-c "adapter speed 10000" \
	-c "program $(BUILD_ROOT_DIR)/$(TARGET).bin $(OPENOCD_FLASH_START) verify reset exit"
endif

#######################################
# clean
#######################################
.PHONY: cleanfiles
cleanfiles:
	@echo off
	@echo [INFO] Clean compiled files...
	@DEL /S /Q *.bak 1>nul 2>nul
	@DEL /S /Q *.ddk 1>nul 2>nul
	@DEL /S /Q *.edk 1>nul 2>nul
	@DEL /S /Q *.lst 1>nul 2>nul
	@DEL /S /Q *.lnp 1>nul 2>nul
	@DEL /S /Q *.mpf 1>nul 2>nul
	@DEL /S /Q *.mpj 1>nul 2>nul
	@DEL /S /Q *.obj 1>nul 2>nul
	@DEL /S /Q *.omf 1>nul 2>nul
	@DEL /S /Q *.plg 1>nul 2>nul
	@DEL /S /Q *.rpt 1>nul 2>nul
	@DEL /S /Q *.tmp 1>nul 2>nul
	@DEL /S /Q *.__i 1>nul 2>nul
	@DEL /S /Q *.crf 1>nul 2>nul
	@DEL /S /Q *.o   1>nul 2>nul
	@DEL /S /Q *.d   1>nul 2>nul
	@DEL /S /Q *.axf 1>nul 2>nul
	@DEL /S /Q *.tra 1>nul 2>nul
	@DEL /S /Q *.dep 1>nul 2>nul
	@DEL /S /Q JLinkLog.txt 1>nul 2>nul
	@DEL /S /Q *.iex 1>nul 2>nul
	@DEL /S /Q *.htm 1>nul 2>nul
	@DEL /S /Q *.dbgconf 1>nul 2>nul
	@DEL /S /Q *.uvguix.* 1>nul 2>nul
	@DEL /S /Q *.scvd 1>nul 2>nul
	@echo [INFO] Cleanup completed!
	
.PHONY: cleanCfiles
cleanCfiles:
	@echo off
	@echo [INFO] Clean compiled *.C files...
	@DEL /S /Q *.c 1>nul 2>nul
	@echo [INFO] Cleanup completed!

.PHONY: clean
clean:
	@echo off
	@rd /s /q $(BUILD_ROOT_DIR)
