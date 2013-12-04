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

	../src/bin/mkfifo.sh

	dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
		--title "< 1 / 6 >"\
		--yes-label "Next"\
		--no-label "Quit"\
		--yesno "\n\n\
		    ________ _______ ______ ______    ______     *   __    ___ ______ __________\n\
		  /   _____/   ____ /  _   |   __  \ /  ___/  O     /  \  /  /   ___/___    ___/\n\
		  \___   \/   /    /  /_|  |  |__| /   ___/  /H\   /    \/  /   ___/   /   /    \n\
		 ____/   /   /___ /  ___   |   ___/   /_______|\__/  /\    /   /______/   /     \n\
		/_______/ \______/__/   |__|__|  /_______________/__/  \__/__________/___/   TM\n\n\
This script is checking the runned process for scapenet. Select Next key to continue." 15 90

	if [ $? -ne 0 ]; then rm $_temp $_package $_module $_db $_ip $_id $_password; clear; exit 0; fi

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
	status=(7 7 7 7 7 0)
	progressLevel=0
	progressValue=0	
	while true; do
		dialog --backtitle "Samsung Software Membership FIRESALE present The SCAPENET V$VER"\
			--title "< 6 / 6 >" \
			--mixedgauge "" 0 0 $progressValue \
			"Apache" "${status[0]}" \
			"$DB" "${status[1]}" \
			"brain_main" "${status[2]}" \
			"brain_write" "${status[3]}" \
			"senses_scan" "${status[4]}" 

		if [ ${status[0]} -eq 2 ] && [ ${status[1]} -eq 2 ] && [ ${status[2]} -eq 2 ] && [ ${status[3]} -eq 2 ] && [ ${status[4]} -eq 2 ]; then break; fi
		case $progressLevel in
			0) check_process "apache2";;
			1) check_process "$DB";;
			2) check_process "brain_main_mysq";;
			3) check_process "brain_write_php";;
			4) check_process "scan";;
		esac
		let progressLevel++
		if [ $progressLevel -eq 5 ]; then let progressLevel=0; fi
		sleep 0.3
	done

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
				status[0]=2
				let progressValue+=20;;
			"$DB" ) if [ ${status[1]} -eq 2 ]; then return; fi
				status[1]=2
				let progressValue+=20;;
			"brain_main_mysq" ) if [ ${status[2]} -eq 2 ]; then return; fi
				status[2]=2
				let progressValue+=20;;
			"brain_write_php" ) if [ ${status[3]} -eq 2 ]; then return; fi
				status[3]=2
				let progressValue+=20;;
			"scan" ) if [ ${status[4]} -eq 2 ]; then return; fi
				status[4]=2
				let progressValue+=20;;
		esac
	else
		case "$1" in
			"apache2" ) status[0]=4;;
			"$DB" ) status[1]=4;;
			"brain_main_mysq" ) status[2]=4
				sleep 0.5
				(../src/brain/brain_main_mysql > /dev/null &)
				{ for I in $(seq 1 100) ; do
					echo $I
					sleep 0.1
				done
				echo 100; } | dialog --gauge "Please wait for running process..." 6 60 0
				;;
			"brain_write_php" ) status[3]=4
				(../src/brain/brain_write_php > /dev/null &);;
			"scan" ) status[4]=4
				(../src/senses/scan /dev/null &);;
		esac
	fi
}


### START ###
show_dashboard

