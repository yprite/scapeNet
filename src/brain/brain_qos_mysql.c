#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFFER_SIZE 255


int main(){
	
	int readn=0;
	int pipeFd=0;
	char buffer[BUFFER_SIZE];

	if((pipeFd = open("/home/scapenet/www/bin/read_face2", O_RDWR))<0){
		perror("fail to call");	
		exit(1);
	}
	memset(buffer, 0x00, BUFFER_SIZE);
	while(1){
		readn = read(pipeFd, buffer, BUFFER_SIZE);
		if(readn>0){
				printf("buffer:%s\n", buffer);
				system(buffer);
		}
		memset(buffer, 0x00, BUFFER_SIZE);
		
	}
	return 0;
}
