#!/bin/sh

PN1=brain_main_mysql
PN2=brain_qos_mysql
PN3=brain_arp_mysql
PN4=brain_traffic_mysql
PN5=brain_kill_mysql
PN6=brain_qos_mysql
PN7=brain_port_mysql

for PN in $PN1 $PN2 $PN3 $PN4 $PN5 $PN6 $PN7
do
	PC=`ps -e| grep $PN| awk '{print $1}'`
	#PC=`ps -ef| grep $PN| grep -v grep`
	if ! [ "$PC" = "" ]
	then
		kill -9 $PC > /dev/null	
		echo "$PN killed"
	fi
done
