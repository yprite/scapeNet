#!/bin/sh

PN1=brain_main
PN2=brain_qos
PN3=brain_arp
PN4=brain_traffic
PN5=brain_kill
PN6=brain_qos
PN7=brain_port
PN8=scan

for PN in $PN1 $PN2 $PN3 $PN4 $PN5 $PN6 $PN7 $PN8
do
	PC=`ps -a| grep $PN| awk '{print $1}'`
	#PC=`ps -ef| grep $PN| grep -v grep`
	if ! [ "$PC" = "" ]
	then
		kill -9 $PC > /dev/null	
		echo "$PN killed"
	fi
done
