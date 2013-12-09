#!/bin/bash
#
#	run.sh
#	Service Run Script for SCAPENET
#
#	Created by LeeGwiro 2013. 11.
#


_temp="/tmp/answer.$$"
VER='1.0'
DB="mysql"


#
# @brief run root?
#
if [ $(id -u) -ne 0]
then
	echo "Script must be run as root. Try 'sudo ./run.sh'"
	exit 1
fi


#
# @brief 프로그램 초기화면. 계속 진행하거나 종료할 수 있음.
#
show_dashboard() {

	sudo ../src/bin/mkfifo.sh

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title ""\
		--yes-label "Next"\
		--no-label "Quit"\
		--yesno "\n\n\
		    ________ _______ ______ ______    ______     *   __    ___ ______ __________\n\
		  /   _____/   ____ /  _   |   __  \ /  ___/  O     /  \  /  /   ___/___    ___/\n\
		  \___   \/   /    /  /_|  |  |__| /   ___/  /H\   /    \/  /   ___/   /   /    \n\
		 ____/   /   /___ /  ___   |   ___/   /_______|\__/  /\    /   /______/   /     \n\
		/_______/ \______/__/   |__|__|  /_______________/__/  \__/__________/___/   TM\n\n\
This script is checking the runned process for scapenet. Select Next key to continue." 15 90

	if [ $? -ne 0 ]; then rm $_temp $_package $_module $_db; clear; exit 0; fi
	sudo mount --bind /home/scapenet/www /var/www
	check_service
}


#
# @brief 서비스 시작전 최종 체크.
#
# mixedgauge statue number
# 0 : Succeeded
# 1 : Failed
# 2 : Passed
# 3 : Completed
# 4 : Checked
# 5 : Done
# 6 : Skipped
# 7 : In Progress
check_service() {
	status=(7 7 7 7 7 7 7 7 7 0)
	progressLevel=0
	progressValue=0	
	while true; do
		dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
			--title "" \
			--mixedgauge "" 0 0 $progressValue \
			"Apache" "${status[0]}" \
			"$DB" "${status[1]}" \
			"brain_main_mysql" "${status[2]}" \
			"brain_arp_mysql" "${status[3]}" \
			"brain_traffic_mysql" "${status[4]}" \
			"brain_kill_mysql" "${status[5]}" \
			"brain_qos_mysql" "${status[6]}" \
			"brain_port_mysql" "${status[7]}" \
			"senses_scan" "${status[8]}" 

		if [ ${status[0]} -eq 2 ] && [ ${status[1]} -eq 2 ] && [ ${status[2]} -eq 2 ]\
		       	&& [ ${status[3]} -eq 2 ] && [ ${status[4]} -eq 2 ] && [ ${status[5]} -eq 2 ]\
		       	&& [ ${status[6]} -eq 2 ] && [ ${status[7]} -eq 2 ] && [ ${status[8]} -eq 2 ]; then break; fi

		case $progressLevel in
			0) check_process "apache2";;
			1) check_process "$DB";;
			2) check_process "brain_main_mysql";;
			3) check_process "brain_arp_mysql";;
			4) check_process "brain_traffic_mysql";;
			5) check_process "brain_kill_mysql";;
			6) check_process "brain_qos_mysql";;
			7) check_process "brain_port_mysql";;
			8) check_process "scan";;
		esac
		let progressLevel++
		if [ $progressLevel -eq 9 ]; then let progressLevel=0; fi
		sleep 0.3
	done
	echo ""
	echo -n "Press any key to continue..." && read a
}


#
# @brief 프로세스 실행 여부 체크. 실행 안돼있으면 친절하게 실행해줌.
#
check_process() {
	CNT=`ps -ef | grep "$1" | grep -v grep | wc -l`
	if [ $CNT -ne 0 ]
	then
		case "$1" in
			"apache2" ) if [ ${status[0]} -eq 2 ]; then return; fi 
				let status[0]=2
				let progressValue+=10;;
			"$DB" ) if [ ${status[1]} -eq 2 ]; then return; fi
				let status[1]=2
				let progressValue+=10;;
			"brain_main_mysql" ) if [ ${status[2]} -eq 2 ]; then return; fi
				let status[2]=2
				let progressValue+=10;;
			"brain_arp_mysql" ) if [ ${status[3]} -eq 2 ]; then return; fi
				let status[3]=2
				let progressValue+=10;;
			"brain_traffic_mysql" ) if [ ${status[4]} -eq 2 ]; then return; fi
				let status[4]=2
				let progressValue+=10;;
			"brain_kill_mysql" ) if [ ${status[5]} -eq 2 ]; then return; fi
				let status[5]=2
				let progressValue+=10;;
			"brain_qos_mysql" ) if [ ${status[6]} -eq 2 ]; then return; fi
				let status[6]=2
				let progressValue+=10;;
			"brain_port_mysql" ) if [ ${status[7]} -eq 2 ]; then return; fi
				let status[7]=2
				let progressValue+=10;;
			"scan" ) if [ ${status[8]} -eq 2 ]; then return; fi
				let status[8]=2
				let progressValue+=20;;
		esac
	else
		case "$1" in
			"apache2" ) let status[0]=4;;
			"$DB" ) let status[1]=4;;
			"brain_main_mysql" ) let status[2]=4
				sleep 0.2
				(../src/brain/brain_main_mysql > /dev/null &)
				{ for I in 10 20 30 40 50 60 70 80 90 100 ; do
					echo $I
					sleep 0.01
				done
				echo 100; } | dialog --gauge "Please wait for running brain_main_mysql process..." 6 60 0
				;;
			"brain_arp_mysql" ) let status[3]=4
				sleep 0.2
				(../src/brain/brain_arp_mysql > /dev/null &)
				{ for I in 10 20 30 40 50 60 70 80 90 100 ; do
					echo $I
					sleep 0.01
				done
				echo 100; } | dialog --gauge "Please wait for running brain_arp_mysql process..." 6 60 0
				;;
			"brain_traffic_mysql" ) let status[4]=4
				sleep 0.2
				(../src/brain/brain_traffic_mysql > /dev/null &)
				{ for I in 10 20 30 40 50 60 70 80 90 100 ; do
					echo $I
					sleep 0.01
				done
				echo 100; } | dialog --gauge "Please wait for running brain_traffic_mysql process..." 6 60 0
				;;
			"brain_kill_mysql" ) let status[5]=4
				sleep 0.2
				(../src/brain/brain_kill_mysql > /dev/null &)
				{ for I in 10 20 30 40 50 60 70 80 90 100 ; do
					echo $I
					sleep 0.01
				done
				echo 100; } | dialog --gauge "Please wait for running brain_kill_mysql process..." 6 60 0
				;;
			"brain_qos_mysql" ) let status[6]=4
				sleep 0.2
				(../src/brain/brain_qos_mysql > /dev/null &)
				{ for I in 10 20 30 40 50 60 70 80 90 100 ; do
					echo $I
					sleep 0.01
				done
				echo 100; } | dialog --gauge "Please wait for running brain_qos_mysql process..." 6 60 0
				;;
			"brain_port_mysql" ) let status[7]=4
				sleep 0.2
				(../src/brain/brain_port_mysql > /dev/null &)
				{ for I in 10 20 30 40 50 60 70 80 90 100 ; do
					echo $I
					sleep 0.01
				done
				echo 100; } | dialog --gauge "Please wait for running brain_port_mysql process..." 6 60 0
				;;
			"scan" ) let status[8]=4
				sleep 0.2
				(../src/brain/scan > /dev/null &)
				{ for I in 10 20 30 40 50 60 70 80 90 100 ; do
					echo $I
					sleep 0.01
				done
				echo 100; } | dialog --gauge "Please wait for running senses_scan process..." 6 60 0
				;;
		esac
	fi
}


### START ###
show_dashboard

