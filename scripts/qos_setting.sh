#/bash/sh/

# tc 유틸리티를 이용해서 QOS를 설정한다.

# ethernet interface에 qdisc를 설정하고 root 노드에 기본 대역폭을 설정한다.
sudo tc qdisc add dev eth0 root handle 1: htb default 30

# root 노드의 하위 노드인 class에 id를 부여하여 대역폭에 대한 제한과 보장량을 설정해준다.
# 현재 노드구조는 가상 상위에 root 노드 아래에 root 노드를 상속받아 class ID가 1,2,3,4,5 가 있는 형태이다.
sudo tc class add dev eth0 parent 1: classid 1:1 htb rate 1kbps ceil 1kbps
sudo tc class add dev eth0 parent 1: classid 1:2 htb rate 3kbps ceil 3kbps
sudo tc class add dev eth0 parent 1: classid 1:3 htb rate 5kbps ceil 5kbps
sudo tc class add dev eth0 parent 1: classid 1:4 htb rate 7kbps ceil 7kbps
sudo tc class add dev eth0 parent 1: classid 1:5 htb rate 10kbps ceil 10kbps

## 아래와 같은 형태로 사용가능하다. 
## 특정 목적지를 QOS 노드의 Class에 부여해서 스케쥴링 하도록 한다.
#sudo tc filter add dev eth0 protocol ip parent 1:0 prio 1 u32 match ip src 210.118.34.28/32 flowid 1:3
