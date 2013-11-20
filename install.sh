#!/bin/bash
_temp="/tmp/answer.$$"
_package="/tmp/package.$$"
_module="/tmp/module.$$"
_db="/tmp/db.$$"
_ip="/tmp/ip.$$"
_id="/tmp/id.$$"
_password="/tmp/password.$$"
PN=`basename "$0"`
VER='1.0'


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
		echo -n "Would you like to install the dialog package?[y/n] "
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


show_version() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--msgbox "                 SCAPENET\n                   V$VER\n\nCopyright © firesale. All right reserved.\n" 0 0
}


set_package() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--yes-label "Next"\
		--no-label "Quit"\
		--yesno "This step is checking the installed package. Select Next key to continue." 0 0
	
	if [ $? -ne 0 ]; then rm $_temp $_package $_module $_db $_ip $_id $_password; clear; exit 0; fi

	select_module
}


select_module() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--ok-label "Next"\
		--cancel-label "Prev"\
		--radiolist "You can use this to present a list of choices which can be turned on or off.\
		You can use the UP/DOWN arrow keys, Press SPACE to toggle an option on or off.\n\n\
		Which of the following are modules?" 0 0 0 \
		"Pcap"	"Use a pacp module." on \
		"NetFilter"	"Use a netfilter module in kernel" off 2>$_module

	case $? in
		0) select_DB;;
		1) set_package;;
		255) return;;
	esac
}


select_DB() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--ok-label "Next"\
		--cancel-label "Prev"\
		--radiolist "You can use this to present a list of choices which can be turned on or off.\
		You can use the UP/DOWN arrow keys, Press SPACE to toggle an option on or off.\n\n\
		Which of the following are databases?" 0 0 0 \
		"MySQL"	"Use a MySQL database." on \
		"SSHDB"	"Use a SSHDB" off 2>$_db

	case $? in
		0) check_package;;
		1) select_module;;
		255) return;;
	esac
}


check_package() {
	if [ -e $_package ]; then rm $_package; fi
	for packageName in libpcap-dev apache2 libapache2-mod-avth-mysql libapache2-mod-php5 php5 php5-cli php5-mysql php5-gd php5-xmlrpc php5-intl php5-memcache mysql-server mysql-client libmysqlclient-dev 
	do
		check=`dpkg -l | grep -w $packageName | awk '{print $2}' | grep -w $packageName`
		if [ "$check" = "" ]
		then
			echo "$packageName" >> $_package
		fi
	done
	
	printModule=`cat $_module`
	printDB=`cat $_db`
	while read line; do 
		echo $line >> $_temp 
		echo "\n" >> $_temp 
	done < $_package
	printPackage=`cat $_temp`

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--yes-label "INSTALL"\
		--no-label "Cancel"\
		--yesno "Uninstalled package and selected module/DB list.\nEnter the INSTALL key to install.\n\n*MODULE : $printModule\n*DB : $printDB\n*Uninstalled Package :\n$printPackage" 0 0

	case $? in
		0) install_package;;
		1) set_package;;
		255) set_package;;
	esac
}


install_package() {
	for package in `cat $_package`; do
		apt-get install $package
	done < $_package

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--msgbox "Install Complate!" 0 0

	create_table
}


create_table() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 2 / 6 >"\
		--msgbox "Database Initializing..." 0 0

	if [ $? -ne 0 ]; then set_package; fi

	set_IPclass
}


set_IPclass() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 3 / 6 >"\
		--inputbox "Try entering that you want IP class." 0 0 2>$_ip
	
	if [ $? -ne 0 ]; then set_package; fi

	set_limit_value
}


set_limit_value() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 4 / 6 >"\
		--yes-label "Default"\
		--no-label "User Set"\
		--yesno "Configurate to traffic" 0 0 2>$_temp

	case $? in
		0) set_ID;;
		1) ;;
		255) set_package;;
	esac
}


set_ID() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 5 / 6 >"\
		--inputbox "Try entering that you want ID below." 0 0 2>$_id
	
	if [ $? -ne 0 ]; then set_package; fi
	
	set_password
}


set_password() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 5 / 6 >"\
		--insecure "$@"\
		--passwordbox "Try entering that you want PASSWORD below." 10 0 2>$_password
	
	if [ $? -ne 0 ]; then set_package; fi
	
	#프록시, 메인 실행~
	
	check_service
}


check_service() {
	while true; do
		dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
			--title "< 6 / 6 >"\
			--mixedgauge "" 0 0 33\
			"Apache" "0" \
			"DB" "1" \
			"brain-main" "2" \
			"senses-main" "3" \
			""	"8" \
			"service1" "4" \
			"service2" "5" \
			"service3" "6" \
			"service4" "7" 
		read input
		if [ input != 0 ]; then return; fi
	done
}

	
set_register() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--form "Enter the information of admin to access" 0 0 0\
		"e-mail" 2 4 "" 2 15 20 0\
		"passward" 4 4 "" 4 15 20 0\
		"ip" 6 4 "" 6 15 20 0 2>$_temp
	
	if [ ${?} -ne 0 ]; then return; fi
	result=`cat $_temp`
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "" --cr-wrap\
		--msgbox "\nYou entered:\n$result" 0 0
}


### START ###
check_dialogPackage
show_version

while true; do
	set_package
done


