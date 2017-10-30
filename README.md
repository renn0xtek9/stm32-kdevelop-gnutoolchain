# KDevelop-GNU Toolchain for STM32
## Goal
The goal of this repository is to provide a helloworld program (the programm just blink a LED on pin A5) using KDevelop and a GNu toolchain (i.e. Makefile, GDB etc.)
**WARNING** at the moment this is (very half-backed). The chain has been written using an STM32F103C8T6, and although the goal would be to make the chain as flexible as possible, loads of things probably remains hardcode. Moreover, the current status required that the project is first initiated by OpenSTM32 although none as SW4STM32, or "the shitty eclipse-based stuff" 

### Characteristics
This project uses 
* GNU toolchain (typically on an Linux platform (e.g. Ubuntu 16.04)
* Standard Peripheral for the MCU (not HAL)


## Requirement 
You will need following program
* make
* [the st-link that you will have to compile from source](https://github.com/texane/stlink)
* arm-none-eabi-gdb
* time ....

