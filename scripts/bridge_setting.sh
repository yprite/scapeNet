#!/bin/bash

brctl addbr br0

brctl stp br0 on

brctl addif br0 eth0

brctl addif br0 eth1

ifconfig eth0 down
ifconfig eth1 down

ifconfig eth0 0.0.0.0  promisc up

ifconfig eth1 0.0.0.0 promisc up

ifconfig br0 210.118.34.253 netmask 255.255.255.0

route add default gw 210.118.34.1 br0

route add default gw 210.118.34.1 eth0

