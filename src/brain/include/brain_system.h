#ifndef _SYSTEM
//system header
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>

//pthread header
#include <pthread.h>

//mysql header

//system header
#define EPOLL_SIZE 20
#define BUFFER_SIZE 255
#endif

int ip_parse(char *str){
	int ip=0,i=0;
	char *ptr;
	ptr = strtok(str, ".");
	for(i=0; i<3; i++){
		ptr = strtok(NULL, ".");
		ip = atoi(ptr);    
	}   
	return ip; 
}


