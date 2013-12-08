#/bash/sh/

sudo tc qdisc add dev eth0 root handle 1: htb default 30
sudo tc class add dev eth0 parent 1: classid 1:1 htb rate 1kbps ceil 1kbps
sudo tc class add dev eth0 parent 1: classid 1:2 htb rate 3kbps ceil 3kbps
sudo tc class add dev eth0 parent 1: classid 1:3 htb rate 5kbps ceil 5kbps
sudo tc class add dev eth0 parent 1: classid 1:4 htb rate 7kbps ceil 7kbps
sudo tc class add dev eth0 parent 1: classid 1:5 htb rate 10kbps ceil 10kbps

#sudo tc filter add dev eth0 protocol ip parent 1:0 prio 1 u32 match ip src 210.118.34.28/32 flowid 1:3
