################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
captivate/BASE/%.obj: ../captivate/BASE/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/bin/cl430" -vmspx --code_model=small --use_hw_mpy=F5 --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="D:/Documents/LockNFC/LockNFC_code" --include_path="D:/Documents/LockNFC/LockNFC_code/NFC" --include_path="D:/Documents/LockNFC/LockNFC_code/Hardware" --include_path="D:/Documents/LockNFC/LockNFC_code/driverlib" --include_path="D:/Documents/LockNFC/LockNFC_code/driverlib/MSP430FR2xx_4xx" --include_path="D:/Documents/LockNFC/LockNFC_code/mathlib" --include_path="D:/Documents/LockNFC/LockNFC_code/captivate" --include_path="D:/Documents/LockNFC/LockNFC_code/captivate/ADVANCED" --include_path="D:/Documents/LockNFC/LockNFC_code/captivate/BASE" --include_path="D:/Documents/LockNFC/LockNFC_code/captivate/COMM" --include_path="D:/Documents/LockNFC/LockNFC_code/captivate_app" --include_path="D:/Documents/LockNFC/LockNFC_code/captivate_config" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.4.LTS/include" --advice:power="all" --advice:hw_config="all" --define=__MSP430FR2633__ --define=__CUSTOMFR2633__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="captivate/BASE/$(basename $(<F)).d_raw" --obj_directory="captivate/BASE" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


