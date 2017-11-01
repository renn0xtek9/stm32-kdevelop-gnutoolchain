#!/bin/bash
# $1: Path of library e.g. /home/max/Projects/Sources/STM32_USB-FS-Device_Lib_V4.1.0
# $2: density e.g. STM32F10x_MD
# $3: Family e.g STM32F10x
density=$(echo "$2" | tr '[:upper:]' '[:lower:]')
file="$1/Libraries/CMSIS/Device/ST/$3/Source/Templates/gcc/startup_$density.s"

if [[ ! -f "$file" ]]
then
	echo "startup file: $file is missing"
	exit 1
fi
echo $file found
mkdir -p startup
cp $file startup/startup_stm32.s 
exit 0
