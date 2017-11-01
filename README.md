# KDevelop-GNU Toolchain for STM32
## Goal
The goal of this repository is to provide a helloworld program on the STM32 (the programm just blink a LED on pin A5) using KDevelop and a GNU toolchain (i.e. Makefile, GDB etc.).
The project has several branch, each time for different type of project.
**ANY COLLABORATION** would be very much appreciated !
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
* the source of the standard peripheral library. **You need to download this from ST website!**
* time ....

## How-to 
Those helloworld program are meant to work out of the box. Bear in mind however the current state of the project is very pre-pre-pre alpha. Also their might be things to change if you e.g. use a different MCU.
Prior to compilation you will need to edit a bit the Makefile. Check especially the few first lines to see if it correspond to you architecture. If not you will have to tune a bit the make file

```
make configure 
make all
sudo make flash
```

## Debugging 

### Debugging manually from the console
Follow instruction from [the st-link that you will have to compile from source](https://github.com/texane/stlink)
That is:
Start the plug you board with the st-link and start the st-util programm
```
st-util
```
In another console, you can start arm-none-eabi-gdb with the program as arguement 
```
arm-none-eabi-gdb program.elf
```
Then in that console you have to connect to the remote target, load the stuff and continue
```
tar extended-remote: 4242 
load 
continue
```
### Debugging inside KDevelop 
The debuggin *should* work inside KDevelop however there is currently a know bug of KDevelop.
Some workaround (involving source compilation of KDevelop have been proposed in [Bug377633](https://bugs.kde.org/show_bug.cgi?id=377633)

What you can still do is in the menu 
```
Run/Configure Launches
```
Define (if not yet done) a new target. Tick "Executable" enter the .elf program .
Then under "Debug" enter the full path to /usr/bin/arm-none-eabi-gdb
This should be able to launch and start debug session **(provided that st-util is running !)**.
Inside the GDB console (in KDevelop) you can then enter the command 
```
tar extended-remote: 4242 
load 
continue
```

## Known Issue 
### ttyACM0 Device or resource busy on Ubuntu
On Ubuntu, trying to plug a STM32 via virtual comport might lead to
```
cannot open /dev/ttyACM0: Device or resource busy
```
My understanding is that the problem is similar to [this](http://starter-kit.nettigo.eu/2015/serial-port-busy-for-avrdude-on-ubuntu-with-arduino-leonardo-eth/)
The present code configure the STM32 as a modem. 
Under ubuntu the modem manager will try to connect to any modem automatically 
To fix this you need to edit the udev rules located in 
```
install/51-stm32board.rules
```
By editing the Vendor id and Product id with the one you have on your device (use lsusb).
Then you need to copy that rules to 
```
/etc/udev/rules.d
```
and restart the udev server
```
sudo udevadm trigger
```
