#!/bin/bash
cd $(mktemp -d)
git clone https://github.com/renn0xtek9/stm32-kdevelop-gnutoolchain.git
cd stm32-kdevelop-gnutoolchain/
make check
make configure
make all
errorcode="$?"
if [ "$errorcode" != "0" ]
then 
	echo "Build FAILED"	
else 
	echo "Build SUCCESS"
fi 
