#!/bin/sh

PN1=brain_main_mysq
PN2=brain_write_php
PN3=scan

for PN in $PN1 $PN2 $PN3
do
	PC=`ps -e| grep $PN| awk '{print $1}'`
	#PC=`ps -ef| grep $PN| grep -v grep`
	if ! [ "$PC" = "" ]
	then
		kill -9 $PC > /dev/null	
		echo "$PN killed"
	fi
done
