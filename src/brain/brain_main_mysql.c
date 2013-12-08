#include "include/brain_system.h"

void pipe_open();


int pipeFd[9];

int main(void){

	struct epoll_event ev, *events;
	int epollFd, logFd,readn;
	char buffer[BUFFER_SIZE];

//	Description	pipeFd
//	pipeFd[0] :	read_face		->	WEB
//	pipeFd[1] :	read_sense		->	ARP
//	pipeFd[2] :	read_sense2		->	traffic
//	pipeFd[3] :	read_sense3		-> 	PORT
//	pipeFd[4] :	write_arp		->	DB ARP
//	pipeFd[5] :	write_traffic	->	DB traffic
//	pipeFd[6] :	write_port		->	DB port
//	pipeFd[7] :	write_kill		->	DB Kill
//	pipeFd[8] :	write_sense		->	COMMAND 
	
	memset(buffer, 0x00, BUFFER_SIZE);
	events = (struct epoll_event *)malloc(sizeof(*events) *EPOLL_SIZE);
	if((epollFd = epoll_create(10)) < 0) {
		perror("epoll_create error");
		exit(1);
	}
	pipe_open();

	ev.events = EPOLLIN;
	ev.data.fd = pipeFd[0];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[0], &ev);
	ev.data.fd = pipeFd[1];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[1], &ev);
	ev.data.fd = pipeFd[2];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[2], &ev);
	ev.data.fd = pipeFd[3];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[3], &ev);
	while(1){
		int state,i;

		state = epoll_wait(epollFd, events, EPOLL_SIZE, 1000);
		switch(state){

			case -1:
				perror("Epoll wait error");
				break;

			case 0:
				printf("No Evenet\n");
				break;

			default:
				for(i=0; i<state; i++){
					if(events[i].data.fd == pipeFd[0]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							write(pipeFd[8], buffer, strlen(buffer));
							if(buffer[0] !='s'){
								write(pipeFd[7], buffer, strlen(buffer));
							}
						}
						else{
							printf("read_face error\n");
						}
					}				
					else if(events[i].data.fd == pipeFd[1]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							write(pipeFd[4], buffer, strlen(buffer));
						}
						else{
							printf("read_sense error\n");
						}
					}				
					else if(events[i].data.fd == pipeFd[2]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							write(pipeFd[5], buffer, strlen(buffer));
						}
						else{
							printf("read_sense2 error\n");
						}
						
					}				
					else if(events[i].data.fd == pipeFd[3]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							write(pipeFd[6], buffer, strlen(buffer));

						}
						else{
							printf("read_sense3 error\n");
						}
					}		
					readn=0;
					memset(buffer, 0x00, BUFFER_SIZE);	
				}
		}
	}
	return 0;
}
void pipe_open(){
	if((pipeFd[0] = open("/home/scapenet/www/bin/read_face", O_RDWR))<0){
		perror("fail to call open() : read_face");
		exit(1);
	}
	if((pipeFd[1] = open("/tmp/read_sense", O_RDWR))<0){
		perror("fail to call open() : read_sense");
		exit(1);
	}
	if((pipeFd[2] = open("/tmp/read_sense2", O_RDWR))<0){
		perror("fail to call open() : read_sense2");
		exit(1);
	}
	if((pipeFd[3] = open("/tmp/read_sense3", O_RDWR))<0){
		perror("fail to call open() : read_sense3");
		exit(1);
	}
	if((pipeFd[4] = open("/tmp/write_arp", O_RDWR))<0){
		perror("fail to call open() : write_arp");
		exit(1);
	}
	if((pipeFd[5] = open("/tmp/write_traffic", O_RDWR))<0){
		perror("fail to call open() : write_traffic");
		exit(1);
	}
	if((pipeFd[6] = open("/tmp/write_port", O_RDWR))<0){
		perror("fail to call open() : write_port");
		exit(1);
	}
	if((pipeFd[7] = open("/tmp/write_kill", O_RDWR))<0){
		perror("fail to call open() : write_man");
		exit(1);
	}
	if((pipeFd[8] = open("/tmp/write_sense", O_RDWR))<0){
		perror("fail to call open() : write_sense");
		exit(1);
	}
}
