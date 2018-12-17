################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./captouch.obj" \
"./main.obj" \
"./Hardware/VLO_Library.obj" \
"./Hardware/mcu.obj" \
"./Hardware/nfc.obj" \
"./Hardware/spi.obj" \
"./Hardware/trf79xxa.obj" \
"./Hardware/uart.obj" \
"./NFC/felica.obj" \
"./NFC/iso14443a.obj" \
"./NFC/iso14443b.obj" \
"./NFC/iso15693.obj" \
"./NFC/ndef.obj" \
"./NFC/nfc_app.obj" \
"./captivate/ADVANCED/CAPT_Manager.obj" \
"./captivate/BASE/CAPT_ISR.obj" \
"./captivate/COMM/CAPT_Interface.obj" \
"./captivate/COMM/FunctionTimer.obj" \
"./captivate/COMM/I2CSlave.obj" \
"./captivate/COMM/UART.obj" \
"./captivate_app/CAPT_App.obj" \
"./captivate_app/CAPT_BSP.obj" \
"./captivate_config/CAPT_UserConfig.obj" \
"../lnk_msp430fr2633.cmd" \
"../captivate/BASE/libraries/captivate_fr2633_family.lib" \
"../driverlib/MSP430FR2xx_4xx/libraries/driverlib.lib" \
"../driverlib/MSP430FR2xx_4xx/libraries/driverlib_lcsd.lib" \
"../driverlib/MSP430FR2xx_4xx/libraries/driverlib_scsd.lib" \
"../mathlib/libraries/IQmathLib.lib" \
"../mathlib/libraries/IQmathLib_CCS_MPY32_5xx_6xx_CPUX_small_code_small_data.lib" \
"../mathlib/libraries/QmathLib.lib" \
"../mathlib/libraries/QmathLib_CCS_MPY32_5xx_6xx_CPUX_small_code_small_data.lib" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Hardware/subdir_vars.mk
-include NFC/subdir_vars.mk
-include captivate/ADVANCED/subdir_vars.mk
-include captivate/BASE/subdir_vars.mk
-include captivate/BASE/libraries/subdir_vars.mk
-include captivate/COMM/subdir_vars.mk
-include captivate_app/subdir_vars.mk
-include captivate_config/subdir_vars.mk
-include driverlib/MSP430FR2xx_4xx/libraries/subdir_vars.mk
-include mathlib/libraries/subdir_vars.mk
-include subdir_rules.mk
-include Hardware/subdir_rules.mk
-include NFC/subdir_rules.mk
-include captivate/ADVANCED/subdir_rules.mk
-include captivate/BASE/subdir_rules.mk
-include captivate/BASE/libraries/subdir_rules.mk
-include captivate/COMM/subdir_rules.mk
-include captivate_app/subdir_rules.mk
-include captivate_config/subdir_rules.mk
-include driverlib/MSP430FR2xx_4xx/libraries/subdir_rules.mk
-include mathlib/libraries/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
LockNFC_code.out \

EXE_OUTPUTS__QUOTED += \
"LockNFC_code.out" \

BIN_OUTPUTS += \
LockNFC_code.hex \

BIN_OUTPUTS__QUOTED += \
"LockNFC_code.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "LockNFC_code.out"

# Tool invocations
LockNFC_code.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmspx --code_model=small --use_hw_mpy=F5 --advice:power="all" --advice:hw_config="all" --define=__MSP430FR2633__ --define=__CUSTOMFR2633__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"LockNFC_code.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"C:/ti/ccsv8/ccs_base/msp430/include" -i"C:/ti/ccsv8/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="LockNFC_code_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "LockNFC_code.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

LockNFC_code.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "LockNFC_code.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "captouch.obj" "main.obj" "Hardware\VLO_Library.obj" "Hardware\mcu.obj" "Hardware\nfc.obj" "Hardware\spi.obj" "Hardware\trf79xxa.obj" "Hardware\uart.obj" "NFC\felica.obj" "NFC\iso14443a.obj" "NFC\iso14443b.obj" "NFC\iso15693.obj" "NFC\ndef.obj" "NFC\nfc_app.obj" "captivate\ADVANCED\CAPT_Manager.obj" "captivate\BASE\CAPT_ISR.obj" "captivate\COMM\CAPT_Interface.obj" "captivate\COMM\FunctionTimer.obj" "captivate\COMM\I2CSlave.obj" "captivate\COMM\UART.obj" "captivate_app\CAPT_App.obj" "captivate_app\CAPT_BSP.obj" "captivate_config\CAPT_UserConfig.obj" 
	-$(RM) "captouch.d" "main.d" "Hardware\mcu.d" "Hardware\nfc.d" "Hardware\spi.d" "Hardware\trf79xxa.d" "Hardware\uart.d" "NFC\felica.d" "NFC\iso14443a.d" "NFC\iso14443b.d" "NFC\iso15693.d" "NFC\ndef.d" "NFC\nfc_app.d" "captivate\ADVANCED\CAPT_Manager.d" "captivate\BASE\CAPT_ISR.d" "captivate\COMM\CAPT_Interface.d" "captivate\COMM\FunctionTimer.d" "captivate\COMM\I2CSlave.d" "captivate\COMM\UART.d" "captivate_app\CAPT_App.d" "captivate_app\CAPT_BSP.d" "captivate_config\CAPT_UserConfig.d" 
	-$(RM) "Hardware\VLO_Library.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

