#!/bin/bash

density=$(echo "$2" | tr '[:upper:]' '[:lower:]')
file="$1/Libraries/CMSIS/Device/ST/STM32F10x/Source/Templates/gcc/startup_$density.s"

if [[ ! -f "$file" ]]
then
	echo "startup file: $file is missing"
	exit 1
fi
echo $file found
cp $file startup/startup_stm32.s 
exit 0



