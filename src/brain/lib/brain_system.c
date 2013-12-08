#include "../include/brain_system.h"


int ip_parse(char *str){
	
	int ip=0,i=0;
	char *ptr;
	ptr = strtok(str, ".");

	for(i=0; i<=3; i++){
		ptr = strtok(NULL, ".");
		ip = atoi(ptr);		
	}

	
	return ip;
}

