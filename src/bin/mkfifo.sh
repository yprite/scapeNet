#!/bin/sh

mkfifo --mode 0666 /tmp/read_sense
mkfifo --mode 0666 /tmp/read_sense2
mkfifo --mode 0666 /tmp/write_sense
mkfifo --mode 0666 /tmp/read_face
mkfifo --mode 0666 /tmp/write_face
mkfifo --mode 0666 /tmp/write_php

