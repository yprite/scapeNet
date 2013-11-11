#!bin/sh

if [ $(id -u) -ne 0 ]
then
	echo "Script must be run as root. Try 'sudo sh ./install.sh'"
	exit 1
fi

echo "This is install script for scapeNet service."
echo "Installing the dialog package."
#sudo apt-get install dialog

while [ 1 ]
do
	echo -n "Are you using the kernel module? [y/n]"
	read input
	if [ "$input" = "y" ]
	then
		mode=1
		break
	elif [ "$input" = "n" ]
	then
		mode=0
		break
	else
		echo "The value is not valid."
	fi
done

#sudo apt-get install mysql-server
#sudo apt-get install mysql-client

if [ $mode -eq 0 ]
then
	echo "Installing the pcap library package."
	#sudo apt-get install libpcap-dev
fi



function display_output() {
	local h=${1-10}			# box height default 10
	local w=${2-41} 		# box width default 41
	local t=${3-Output} 	# box title 
	dialog --backtitle "Linux Shell Script Tutorial" --title "${t}" --clear --msgbox "$(<$OUTPUT)" ${h} ${w}
}

function show_date() {
	echo "Today is $(date) @ $(hostname -f)." >$OUTPUT
	display_output 6 60 "Date and Time"
}

function show_calendar() {
	cal >$OUTPUT
	display_output 13 25 "Calendar"
}


while true
do

### display main menu ###
dialog --clear  --help-button --backtitle "filesale present" \
	--title "==== [ SCAPENET CONFIGURATION ] ====" \
	--menu "You can use the UP/DOWN arrow keys, the first \n\
	letter of the choice as a hot key, or the \n\
	number keys 1-9 to choose an option.\n\
	Choose the TASK" 15 50 4 \
	Date/time "Displays date and time" \
	Calendar "Displays a calendar" \
	Editor "Start a text editor" \
	Exit "Exit to the shell" 2>"${INPUT}"
 
menuitem=$(<"${INPUT}")
 

# make decsion 
case $menuitem in
	Date/time) show_date;;
	Calendar) show_calendar;;
	Editor) $vi_editor;;	
	Exit) echo "Bye"; break;;
esac

done



