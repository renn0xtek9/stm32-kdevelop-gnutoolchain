#!/bin/bash 
echo "args"> run_shell_script.log
echo "${@}" >> run_shell_script.log
# pass=`kdialog --password "Enter you sudo password"`
# echo $pass | sudo -S skill -9 st-util # Kill any running instance
# echo $padd | sudo st-util & 
# sleep 1.0 
# ${@} build/program.elf --command=gdbinit.gdb

/usr/bin/arm-none-eabi-gdb /home/max/Projects/Projets/STM32_Helloworld_standard/build/program.elf 

# --command=/home/max/Projects/Projets/STM32_Helloworld_standard/gdbinit.gdb 

# /home/max/Projects/Projets/STM32_Helloworld_standard/debug_launch_script.sh
