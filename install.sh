#!/bin/bash

_temp="/tmp/answer.$$"
PN=`basename "$0"`
VER='0.1'

if [ $(id -u) -ne 0 ]
then
	echo "Script must be run as root. Try 'sudo ./install.sh'"
	exit 1
fi


echo "This is install script for scapeNet service."
echo "Check that the dialog package is installed."
CHECK=`dpkg -l | grep -w dialog | awk '{print $2}' | grep -w dialog`
if [ "$CHECK" != "" ]
then
	echo "Dialog package is installed."
	sleep 1
else
	echo "Dialog package is not installed."
	echo -n "Would you like to install the dialog package?[y/n]"
	read INPUT
	if [ "$INPUT" = "y" ]
	then
		sudo apt-get install dialog
	else
		echo "Bye."
		exit 1
	fi
fi


set_passward() {
	dialog --backtitle "scapeNet - set passward"\
		--inputbox "Enter the passward that you want to set" 8 52 2>$_temp

	result=`cat $_temp`
	dialog --msgbox "\nYou entered:\n$result" 9 52
}

show_version() {
	dialog --backtitle "scapeNet - show version"\
		--msgbox "$PN - Version $VER\nThe scapeNet configuration service\n" 9 52
}

main_menu() {
	dialog --backtitle "FIRESALE present" --title " scapeNet configuration service - V. $VER "\
		--cancel-label "Quit" \
		--menu "Move using [UP] [DOWN], [Enter] to select" 17 60 10\
		Passward "Set the passward"\
		Version "Show program version info"\
		Quit "Exit configuration" 2>$_temp

	opt=${?}
	if [ $opt != 0 ]; then rm $_temp; exit; fi
	menuitem=`cat $_temp`
	echo "menu=$menuitem"
	case $menuitem in
		Passward) set_passward;;
		Version) show_version;;
		Quit) rm $_temp; exit;;
	esac
}

while true; do
	main_menu
done
