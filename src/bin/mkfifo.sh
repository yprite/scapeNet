#!/bin/sh

READ_SENSE=/tmp/read_sense
READ_SENSE2=/tmp/read_sense2
READ_SENSE3=/tmp/read_sense3
WRITE_SENSE=/tmp/write_sense
READ_FACE=/tmp/read_face
WRITE_FACE=/tmp/write_face
WRITE_PHP=/tmp/write_php

if [ ! -e $READ_SENSE ]; then mkfifo --mode 0666 $READ_SENSE; fi
if [ ! -e $READ_SENSE2 ]; then mkfifo --mode 0666 $READ_SENSE2; fi
if [ ! -e $READ_SENSE3 ]; then mkfifo --mode 0666 $READ_SENSE3; fi
if [ ! -e $WRITE_SENSE ]; then mkfifo --mode 0666 $WRITE_SENSE; fi
if [ ! -e $READ_FACE ]; then mkfifo --mode 0666 $READ_FACE; fi
if [ ! -e $WRITE_FACE ]; then mkfifo --mode 0666 $WRITE_FACE; fi
if [ ! -e $WRITE_PHP ]; then mkfifo --mode 0666 $WRITE_PHP; fi

