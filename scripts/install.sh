#!/bin/bash
#
#	install.sh
#	Install Service Script for SCAPENET
#
#	Created by LeeGwiro 2013. 11.
#


_temp="/tmp/answer.$$"
_package="/tmp/package.$$"
_module="/tmp/module.$$"
_db="/tmp/db.$$"
_ip="/tmp/ip.$$"
_id="/tmp/id.$$"
_password="/tmp/password.$$"
PN=`basename "$0"`
VER='1.0'


#
# @brief root 권한으로 실행했는지 체크
#
if [ $(id -u) -ne 0 ]
then
	echo "Script must be run as root. Try 'sudo ./install.sh'"
	exit 1
fi


#
# @brief dialog 패키지 설치유무 확인. 이게 없으면 실행이 안됨.
#
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


#
# @brief 프로그램 instruction, version
#
show_version() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--msgbox "                 SCAPENET\n                   V$VER\n\nCopyright © firesale. All right reserved.\n" 0 0
}


#
# @brief 프로그램 초기화면. 계속 진행하거나 종료할 수 있음.
#
set_package() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--yes-label "Next"\
		--no-label "Quit"\
		--yesno "\n\n\
		    ________ _______ ______ ______    ______     *   __    ___ ______ __________\n\
		  /   _____/   ____ /  _   |   __  \ /  ___/  O     /  \  /  /   ___/___    ___/\n\
		  \___   \/   /    /  /_|  |  |__| /   ___/  /S\   /    \/  /   ___/   /   /    \n\
		 ____/   /   /___ /  ___   |   ___/   /_______|\__/  /\    /   /______/   /     \n\
		/_______/ \______/__/   |__|__|  /_______________/__/  \__/__________/___/   TM\n\n\
	    	 This step is checking the installed package. Select Next key to continue." 15 90

	if [ $? -ne 0 ]; then rm $_temp $_package $_module $_db $_ip $_id $_password; clear; exit 0; fi

	select_module
}


#
# @brief 어떤 module을 선택할 것인지 선택. Pcap or NetFilter.
#
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


#
# @brief 어떤 DB를 사용할 것인지 선택. MySQL or SSHDB.
#
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


#
# @brief 서비스 사용을 위해 필요한 설치안된 패키지와 선택한 모듈, DB가 출력됨.
#
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


#
# @brief 설치하지 않은 패키지를 설치.
#
install_package() {
	for package in `cat $_package`; do
		apt-get install $package
	done < $_package

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--msgbox "Install Complate!" 0 0

	create_table
}


#
# @brief DB 테이블 생성.
#
create_table() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 2 / 6 >"\
		--msgbox "Database Initializing..." 0 0

	if [ $? -ne 0 ]; then set_package; fi

	set_IPclass
}


#
# @brief IP class 지정. ex) 210.118.34
#
set_IPclass() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 3 / 6 >"\
		--inputbox "Try entering that you want IP class.\nex) 210.118.34" 0 0 2>$_ip
	
	if [ $? -ne 0 ]; then set_package; fi

	set_limit_value
}


#
# @brief 최대 트래픽 제한 설정. default값이나 사용자 설정값을 선택할 수 있음.
#
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


#
# @brief 관리자 ID 설정.
#
set_ID() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 5 / 6 >"\
		--inputbox "Try entering that you want ID below." 0 0 2>$_id
	
	if [ $? -ne 0 ]; then set_package; fi
	
	set_password
}


#
# @brief 관리자 Password 설정.
#
set_password() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 5 / 6 >"\
		--insecure "$@"\
		--passwordbox "Try entering that you want PASSWORD below." 10 0 2>$_password
	
	if [ $? -ne 0 ]; then set_package; fi
	
	#프록시, 메인 실행~
	
	check_service
}


#
# @brief 서비스 시작전 최종 체크.
#
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


### START ###
check_dialogPackage
show_version

while true; do
	set_package
done


