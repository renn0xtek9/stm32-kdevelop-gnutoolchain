#!/bin/bash
for f in ${@} 
do 
	if [[ ! -f "$f" ]] && [[ ! -d "$f" ]]
	then
		echo $f is missing 
		exit 1
	fi	
done 
exit 0
