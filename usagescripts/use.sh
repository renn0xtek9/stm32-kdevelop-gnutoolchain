#!/bin/bash
logfile=log.txt
devicefile=/dev/ttyACM0

#*********************************Commands 
Aux="$(pwd)/shoot.sh 21 63"
Shutdown="$(pwd)/shoot.sh 20 12"

Bassplus="$(pwd)/shoot.sh 16 22"
Bassminus="$(pwd)/shoot.sh 16 23"
Trebbleplus="$(pwd)/shoot.sh 16 24"
Trebbleminus="$(pwd)/shoot.sh 16 25"
Natural="$(pwd)/shoot.sh 16 183"		#Reset Bass and Treble but it will restart from where it was after
IncredibleSurround="$(pwd)/shoot.sh 16 192"		#Reset Bass and Treble


Volumeminus="$(pwd)/shoot.sh 16 17"
Volumeplus="$(pwd)/shoot.sh 16 16"



#*********************************Function
function kill_volume
{
	for (( c=0; c<=30; c++ ))
	do
		$Volumeminus
		sleep 0.1s
	done
}
function decent_volume  
{
	kill_volume 
	for (( c=0; c<=8; c++ ))
	do
		$Volumeplus
		sleep 0.1s
	done
	
}
function normale_settings
{
	$Aux
	sleep 0.1s
	decent_volume 
	for (( c=0; c<=5; c++))
	do 
		$Bassplus
		sleep 0.1s
	done 
	for (( c=0; c<=5; c++))
	do 
		$Trebbleminus
	done 
	for (( c=0; c<=2; c++))
	do 
		$Trebbleplus
	done	
}
#*********************************Set up Auxiallaire at decent Volume 
normale_settings
$IncredibleSurround



