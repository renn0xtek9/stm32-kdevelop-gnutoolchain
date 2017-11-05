#!/bin/bash
logfile=log-shoot.txt
devicefile=/dev/ttyACM0
components=4
protocol=7
address=$1
command=$2

foo=$(printf "%03d.%03d" $address $command )
echo "$foo"
sleep 0.1s
echo "$foo" > $logfile
	


echo -n "$foo" > $devicefile





# echo "016.021" > /dev/usbcheck
