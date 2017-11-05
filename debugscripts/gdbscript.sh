#!/bin/bash
sudo skill -9  st-util 
sleep 0.2
sudo st-util &
sleep 0.2
# /usr/bin/arm-none-eabi-gdb  -ix gdbbeforeloading.gdb -x gdbrun.gdb  --interpreter=mi2 -quiet ./../build/program.elf
/usr/bin/arm-none-eabi-gdb  -ix gdbbeforeloading.gdb -x gdbrun.gdb  --interpreter=tui ./../build/program.elf


