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
			sudo apt-get install dialog -y
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
		--title "< The NMS for ALL >"\
		--yes-label "Next"\
		--no-label "Quit"\
		--yesno "\n\n\
		    ________ _______ ______ ______    ______     *   __    ___ ______ __________\n\
		  /   _____/   ____ /  _   |   __  \ /  ___/  O     /  \  /  /   ___/___    ___/\n\
		  \___   \/   /    /  /_|  |  |__| /   ___/  /S\   /    \/  /   ___/   /   /    \n\
		 ____/   /   /___ /  ___   |   ___/   /_______|\__/  /\    /   /______/   /     \n\
		/_______/ \______/__/   |__|__|  /_______________/__/  \__/__________/___/   TM\n\n\
	    	 This step is checking the installed package. Select Next key to continue." 15 90

	if [ $? -ne 0 ]; then rm $_temp $_package $_module $_db; clear; exit 0; fi

	select_module
}


#
# @brief 어떤 module을 선택할 것인지 선택. Pcap or NetFilter.
#
select_module() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 5 >"\
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
		--title "< 2 / 5 >"\
		--ok-label "Next"\
		--cancel-label "Prev"\
		--radiolist "You can use this to present a list of choices which can be turned on or off.\
		You can use the UP/DOWN arrow keys, Press SPACE to toggle an option on or off.\n\n\
		Which of the following are databases?" 0 0 0 \
		"mysql"	"Use a MySQL database." on \
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
	for packageName in libpcap-dev apache2 libapache2-mod-php5 php5 php5-cli php5-mysql php5-gd php5-xmlrpc php5-intl php5-memcache mysql-server mysql-client libmysqlclient-dev 
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
	#printPackage=`cat $_temp`
	sizePackage=`stat -c %s $_temp`
	if [ $sizePackage -eq 0 ]
	then
		printPackage="done"
	else
		printPackage=`cat $_temp`
	fi

	#DB정보 run.sh에 알려줌
	sed -e "/^DB/s/DB=......./DB=\"$printDB\"/g" ./run.sh > ./run.sh.tmp
	mv ./run.sh.tmp ./run.sh
	chown leegwiro ./run.sh
	chmod +x ./run.sh

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 3 / 5 >"\
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
		apt-get install $package -y
	done < $_package

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 3 / 5 >"\
		--msgbox "\n         Install Complate!" 7 40

	create_binary
}


#
# @brief 
#
create_binary() {

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 4 / 5 >"\
		--msgbox "\n     now, create binary files." 7 40
	
	if [ $_module = "NetFilter" ]
	then
		cd ../src/senses; make -f Makefile_netfilter; cd -
	else
		cd ../src/senses; make -f Makefile_libpcap; cd -
	fi

	cd ../src/brain; make -f Makefile_mysql; cd -

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 4 / 5 >"\
		--msgbox "\n  binary files creation succeeded." 7 40

	if [ $? -ne 0 ]; then set_package; fi

	create_table	
}



#
# @brief DB 테이블 생성.
#
create_table() {	

	mysql -uroot -p1234 < ../sql/init.sql
	{ for I in $(seq 1 100) ; do
		echo $I
		sleep 0.01
	done
	echo 100; } | dialog --gauge "Please wait for create database table..." 6 60 0


	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 5 / 5 >"\
		--msgbox "\n  Database table creation succeeded." 7 40

	if [ $? -ne 0 ]; then set_package; fi

	service_start
}


#
# @brief 서비스 지금 실행할꺼야??
#
service_start() {
	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< The NMS for ALL >"\
		--yes-label "Start"\
		--no-label "Cancel"\
		--yesno "Install succeeded!\nScapenet needs to start the administrator ID, Password and system IP Class. Look at the below that default value.\n\nIP Class : 210.118.34.*\nID : admin\nPW : 1234\n\nDo you want to run now?" 0 0 2>$_temp

	case $? in
		0) ./run.sh; exit 0;;
		1) set_package;;
		255) set_package;;
	esac
}


### START ###
check_dialogPackage
show_version

while true; do
	set_package
done


