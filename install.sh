#!bin/sh


mode=0
echo "This is install script for scapeNet service."
echo "Installing dialog package."
#sudo apt-get install dialog

while [ 1 ]
do
	echo -n "Are you using the kernel module? [y/n]"
	read input

	if [ $input -eq 'y' ]
	then
		$mode=1
		break
	elif [ $input -eq 'n' ]
	then
		$mode=0
		break
	else
		echo "The value is not valid."
	fi
done

#sudo apt-get install mysql-server
#sudo apt-get install mysql-client

if [ $mode -eq 0 ]
then
	echo "Installing pcap package."
	#sudo apt-get install libpcap-dev
fi


