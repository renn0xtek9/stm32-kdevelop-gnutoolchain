#!/bin/bash
logfile=log.txt
devicefile=/dev/ttyACM0
components=4
protocol=7

for (( address=16; address<=21; address++ ))
do
	for (( command=0; command<=63; command++ )) 
	do 
		foo=$(printf "%03d.%03d" $address $command )
		echo "$foo"
		sleep 5.0s
		echo "$foo" > $logfile
		
		
		echo -n "$foo" >> $devicefile
	done
done



# echo "004.005.020.021" > /dev/usbcheck
