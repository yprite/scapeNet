#!/bin/sh

READ_SENSE=/tmp/read_sense
READ_SENSE2=/tmp/read_sense2
READ_SENSE3=/tmp/read_sense3
WRITE_ARP=/tmp/write_arp
WRITE_TRAFFIC=/tmp/write_traffic
WRITE_KILL=/tmp/write_kill
WRITE_PORT=/tmp/write_port
WRITE_SENSE=/tmp/write_sense
READ_FACE=/home/scapeNet/www/bin/read_face
READ_FACE2=/home/scapeNet/www/bin/read_face2

if [ ! -e $READ_SENSE ]; then mkfifo --mode 0666 $READ_SENSE; fi
if [ ! -e $READ_SENSE2 ]; then mkfifo --mode 0666 $READ_SENSE2; fi
if [ ! -e $READ_SENSE3 ]; then mkfifo --mode 0666 $READ_SENSE3; fi
if [ ! -e $WRITE_ARP ]; then mkfifo --mode 0666 $WRITE_ARP; fi
if [ ! -e $WRITE_TRAFFIC ]; then mkfifo --mode 0666 $WRITE_TRAFFIC; fi
if [ ! -e $WRITE_KILL ]; then mkfifo --mode 0666 $WRITE_KILL; fi
if [ ! -e $WRITE_PORT ]; then mkfifo --mode 0666 $WRITE_PORT; fi
if [ ! -e $WRITE_SENSE ]; then mkfifo --mode 0666 $WRITE_SENSE; fi
if [ ! -e $READ_FACE ]; then mkfifo --mode 0666 $READ_FACE; fi
if [ ! -e $READ_FACE2 ]; then mkfifo --mode 0666 $READ_FACE2; fi


