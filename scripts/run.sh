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
# @brief 프로그램 초기화면. 계속 진행하거나 종료할 수 있음.
#
show_dashboard() {
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
	    	 This step is checking the installed package. Select Next key to continue." 15 90

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
# 8 : Blank	

check_service() {
	status=(7 7 7 7 7)
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

		#read input
		#case $input in
		case $progressLevel in
			0) check_process "apache2";;
			1) check_process "$DB";;
			2) check_process "brain_main";;
			3) check_process "brain_write";;
			4) check_process "senses_scan";;
			5) exit 0;;
		esac
		let progressLevel++
		sleep 0.2
		#read input
		#if [ $input != 0 ]; then return; fi
	done
}


#
# @brief 프로세스 실행 여부 체크. 실행 안돼있으면 친절하게 실행해줌.
#
check_process() {
	CNT=`ps -ef | grep "$1" | grep -v grep | wc -l`
	if [ $CNT -ne 0 ]
	then
		case "$1" in
			"apache2" ) status[0]=2
				let progressValue+=20;;
			"$DB" ) status[1]=2
				let progressValue+=20;;
			"brain_main" ) status[2]=2
				let progressValue+=20;;
			"brain_write" ) status[3]=2
				let progressValue+=20;;
			"senses_scan" ) status[4]=2
				let progressValue+=20;;
		esac
	else
		case "$1" in
			"apache2" ) status[0]=4;;
			"$DB" ) status[1]=4;;
			"brain_main" ) status[2]=4
				../src/brain_main
				{ for I in $(seq 1 100) ; do
					echo $I
					sleep 0.1
				done
				echo 100; } | dialog --gauge "Please wait for running process..." 6 60 0
				;;
			"brain_write" ) status[3]=4
				../src/brain_write;;
			"senses_scan" ) status[4]=4
				../src/senses_scan;;
		esac
	fi
}


### START ###
show_dashboard

