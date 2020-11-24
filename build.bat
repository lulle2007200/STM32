setlocal enabledelayedexpansion

set BUILD_DIR=.\build
set PROJECT_NAME=Test

set AS=clang
set CC=clang
set LD=clang
set OBJCOPY=llvm-objcopy
set READELF=llvm-readelf
set OBJDUMP=llvm-objdump

set SYSROOT=".\Lib\Newlib"
set LIBCLANG=".\Lib\Compiler-rt\thumb\v7e-m\fpv4-sp\hard"
set LIBGCC=".\Lib\Gcc\thumb\v7e-m\fpv4-sp\hard"

set OPTIMIZATIONS=-O0 -flto

set DEBUG=-glldb


set LD_SCRIPT=.\stm32l422cb.ld

set C_SOURCES=^
 Src\system_stm32l4xx.c^
 Drivers\Is31fl3733\is31fl3733.c^
 Drivers\Backlight\backlight.c^
 Drivers\usb\cdc.c^
 Drivers\usb\usb_core.c^
 Drivers\usb\usbd_stm32l422_dev_fs.c^
 Drivers\STM32L4xx_HAL_Driver\Src\stm32l4xx_ll_utils.c^
 Drivers\STM32L4xx_HAL_Driver\Src\stm32l4xx_ll_pwr.c^
 Drivers\STM32L4xx_HAL_Driver\Src\stm32l4xx_ll_rcc.c^
 Drivers\STM32L4xx_HAL_Driver\Src\stm32l4xx_hal.c^
 Drivers\STM32L4xx_HAL_Driver\Src\stm32l4xx_hal_pcd.c^
 Drivers\STM32L4xx_HAL_Driver\Src\stm32l4xx_ll_gpio.c^
 Drivers\STM32L4xx_HAL_Driver\Src\stm32l4xx_ll_i2c.c^
 Src\main.c


set C_INCLUDES=^
 -IInc^
 -IDrivers/STM32L4xx_HAL_Driver/Inc^
 -IDrivers/STM32L4xx_HAL_Driver/Inc/Legacy^
 -IDrivers/CMSIS/Device/ST/STM32L4xx/Include^
 -IDrivers/CMSIS/Include^
 -IDrivers/CMSIS/Core/Include^
 -IDrivers/usb^
 -IDrivers/Is31fl3733^
 -IDrivers/Backlight^
 -IInc/Config

set C_DEFINES=^
 -DUSE_FULL_LL_DRIVER^
 -DUSE_HAL_DRIVER^
 -DSTM32L422xx

set ASM_SOURCES=^
 Src\asm\Startup.s^
 Src\asm\VectorTable.s

set ASM_INCLUDES=

set ASM_DEFINES=


set OBJECTS=^
 %SYSROOT%\lib\thumb\v7e-m\fpv4-sp\hard\crt0.o^
 %LIBGCC%\crtbegin.o^
 %LIBGCC%\crtend.o^
 %LIBGCC%\crti.o^
 %LIBGCC%\crtn.o^
 %LIBGCC%\crtfastmath.o



set LIBS=^
 -lclang_rt.builtins^
 -lc^
 -lm

set LIB_DIR=^
 -L%LIBCLANG%^
 -L%SYSROOT%\lib\thumb\v7e-m\fpv4-sp\hard


set TARGET_TRIPLE=--target=arm-none-eabi
set ARCH=-march=armv7e-m
set CPU=-mcpu=cortex-m4
set FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=hard
set MCU=%TARGET_TRIPLE% %ARCH% %CPU% %FPU% -mthumb -mlittle-endian

set COMMON_FLAGS=%MCU% %DEBUG% %OPTIMIZATIONS% -fdata-sections -ffunction-sections --sysroot=%SYSROOT%

set C_FLAGS=%COMMON_FLAGS% %C_DEFINES% %C_INCLUDES% -c

set ASM_FLAGS=%COMMON_FLAGS% %ASM_DEFINES% %ASM_INCLUDES% -x assembler-with-cpp -c

set LD_FLAGS=%COMMON_FLAGS% -nostdlib -fuse-ld=lld -T%LD_SCRIPT% -Wl,-Map=%BUILD_DIR%\%PROJECT_NAME%.map,--cref,--gc-sections %LIB_DIR% %LIBS%


if exist %BUILD_DIR%/nul rmdir /s /q %BUILD_DIR%
mkdir %BUILD_DIR%


for %%A in (%C_SOURCES%) do (
	%CC% %C_FLAGS% %%A -o %BUILD_DIR%\%%~nA%%~xA.o
)

for %%A in (%ASM_SOURCES%) do (
	%AS% %ASM_FLAGS% %%A -o %BUILD_DIR%\%%~nA%%~xA.o
)

for %%A in (%C_SOURCES%) do (
	set OBJECTS=!OBJECTS! %BUILD_DIR%\%%~nA%%~xA.o
)

for %%A in (%ASM_SOURCES%) do (
	set OBJECTS=!OBJECTS! %BUILD_DIR%\%%~nA%%~xA.o
)

%LD% %OBJECTS% %LD_FLAGS% -v -o %BUILD_DIR%\%PROJECT_NAME%.elf

rem llvm-objcopy produces faulty hex images, use arm-none-eabi-objcopy instead
rem %OBJCOPY% -O ihex -S %BUILD_DIR%\%PROJECT_NAME%.elf %BUILD_DIR%\%PROJECT_NAME%.hex
arm-none-eabi-objcopy -O ihex -S %BUILD_DIR%\%PROJECT_NAME%.elf %BUILD_DIR%\%PROJECT_NAME%.hex

%OBJCOPY% -O binary -S %BUILD_DIR%\%PROJECT_NAME%.elf %BUILD_DIR%\%PROJECT_NAME%.bin

%OBJDUMP% -D %BUILD_DIR%\%PROJECT_NAME%.elf > %BUILD_DIR%\%PROJECT_NAME%_disassembly.s

.\Tools\DfuSe_commandline.exe %BUILD_DIR%\%PROJECT_NAME%.hex %BUILD_DIR%\%PROJECT_NAME%.dfu >nul 2>&1

%READELF% --all %BUILD_DIR%\%PROJECT_NAME%.elf > %BUILD_DIR%\%PROJECT_NAME%_elf_info.txt