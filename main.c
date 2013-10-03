#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define EPOLL_SIZE 20
#define BUFFER_SIZE 255

int main(void)
{
	struct epoll_event ev, *events;
	int epollFd, pipeFd[4];
	int readn, writen;

	char buffer[BUFFER_SIZE];

	// 이벤트 풀의 크기만큼 events구조체를 생성한다.
	events = (struct epoll_event *)malloc(sizeof(*events) * EPOLL_SIZE);

	// epoll_create를 이용해서 epoll 지정자를 생성한다.	
	if ((epollFd = epoll_create(10)) < 0) {
		perror("epoll_create error");
		exit(1);
	}

	if ((pipeFd[0] = open(".read_face", O_RDWR)) < 0) {
		perror("fail to call open() : read_face");
		exit(1);
	}

	if ((pipeFd[1] = open(".write_face", O_RDWR)) < 0) {
		perror("fail to call open() : write_face");
		exit(1);
	}

	if ((pipeFd[2] = open(".read_sense", O_RDWR)) < 0) {
		perror("fail to call open() : read_sense");
		exit(1);
	}

	if ((pipeFd[3] = open(".write_sense", O_RDWR)) < 0) {
		perror("fail to call open() : write_sense");
		exit(1);
	}


	// 만들어진 듣기 소켓을 epoll이벤트 풀에 추가한다.
	// EPOLLIN(read) 이벤트의 발생을 탐지한다.
	ev.events = EPOLLIN;
	
	ev.data.fd = pipeFd[0];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[0], &ev);
	
	ev.data.fd = pipeFd[1];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[1], &ev);
	
	ev.data.fd = pipeFd[2];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[2], &ev);

	ev.data.fd = pipeFd[3];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[3], &ev);

	
	
	while(1) {
		int state, i;
		// epoll이벤트 풀에서 이벤트가 발생했는지를 검사한다.
		state = epoll_wait(epollFd, events, EPOLL_SIZE, 2000);
		switch(state) {
		case -1:
			perror("epoll wait error");
			break;
		
		case 0:
			printf("timeout\n");
			break;

		default:
			for (i = 0; i < state; i++) {
				if (events[i].data.fd == pipeFd[0]) {
					readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
					if (readn > 0){
						char tmp[100];
						buffer[strlen(buffer)-1] = '\0';
						printf("read face : %s\n", buffer);
					}
					else printf("read error!\n");
				}
				else if (events[i].data.fd == pipeFd[1]) {
                                	readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
                                	if (readn > 0) printf("write face : %s\n", buffer);
                                	else printf("read error!\n");
                                }
				else if (events[i].data.fd == pipeFd[2]) {                        					
                                	readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
					if (readn > 0) printf("read sense : %s\n", buffer);
                                	else printf("read error!\n");
                                }

				else if (events[i].data.fd == pipeFd[3]) {
                                	readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
					if (readn > 0) printf("write sense : %s\n", buffer);
                                	else printf("read error!\n");
                                }
				memset(buffer, 0x00, BUFFER_SIZE);
			}
		}
	}
}
