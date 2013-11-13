#!/bin/bash
_temp="/tmp/answer.$$"
_package="/tmp/package.$$"
PN=`basename "$0"`
VER='0.1'

##test

### 루트 권한으로 실행했는지 체크 ###
if [ $(id -u) -ne 0 ]
then
	echo "Script must be run as root. Try 'sudo ./install.sh'"
	exit 1
fi

### 다이얼로그 패키지 설치유무 확인 ###
check_dialogPackage() {
	echo "This is install script for scapeNet service."
	echo "Check that the dialog package is installed."
	check=`dpkg -l | grep -w dialog | awk '{print $2}' | grep -w dialog`
	if [ "$check" != "" ]
	then
		echo "Dialog package is installed."
		sleep 1
	else
		echo "Dialog package is not installed."
		echo -n "Would you like to install the dialog package?[y/n]"
		read input
		if [ "$input" = "y" ]
		then
			sudo apt-get install dialog
			echo "install success."
			sleep 1
		else
			echo "Bye."
			exit 1
		fi
	fi
}


set_package() {
	if [ -e $_package ]; then rm $_package; fi
	for packageName in libdbd-mysql-perl libmysqlclient18:i386 mysql-client-5.5 mysql-client-core-5.5 mysql-common mysql-server mysql-server-5.5 mysql-server-core-5.5 php5-mysql libapache2-mod-php5 php5 php5-cli php5-common php5-gd apache2 apach2-mpm-prefork apache2-utils apache2.2-bin apache2.2-common
	do
		check=`dpkg -l | grep -w $packageName | awk '{print $2}' | grep -w $packageName`
		if [ "$check" = "" ]
		then
			echo "$packageName" >> $_package
			echo "\n" >> $_package
		fi
	done
	printPackage=`cat $_package`
	dialog --title "" --msgbox "uninstalled package list.\nEnter the OK key to install.\n\n$printPackage" 30 60 
}

set_register() {
	dialog --backtitle "scapeNet - Register"\
		--form "Enter the information of admin to access" 20 70 15\
		"e-mail" 2 4 "" 2 15 20 0\
		"passward" 4 4 "" 4 15 20 0\
		"ip" 6 4 "" 6 15 20 0 2>$_temp
	
	if [ ${?} -ne 0 ]; then return; fi
	result=`cat $_temp`
	dialog --title "Items are separated by \\nn" --cr-wrap\
		--msgbox "\nYou entered:\n$result" 12 52
}

show_version() {
	dialog --backtitle "scapeNet - Version"\
		--msgbox "$PN - Version $VER\nThe scapeNet configuration service\n" 9 52
}

main_menu() {
	dialog --backtitle "FIRESALE present" --title " scapeNet configuration service - V. $VER "\
		--cancel-label "Quit" \
		--menu "This is the scapeNet.\nMove using [UP] [DOWN], [Enter] to select.\nTry it now!\n\n" 17 60 10\
		Package "scapeNet needs some package"\
		Register "Set the operator passward"\
		Version "Show program version info"\
		Quit "Exit configuration" 2>$_temp

	opt=${?}
	if [ $opt != 0 ]; then rm $_temp $_package; clear; exit; fi
	menuitem=`cat $_temp`
	case $menuitem in
		Package) set_package;;
		Register) set_register;;
		Version) show_version;;
		Quit) rm $_temp $_package; clear; exit;;
	esac
}


check_dialogPackage
while true; do
	main_menu
done
