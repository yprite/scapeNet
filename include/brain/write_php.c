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
	int epollFd, pipeFd;
	int readn, writen;
	int isChanged=0, isCheck=0;

	char buffer[BUFFER_SIZE];
	char *cmd = "curl -d \"q=";
	char *cmd2= "\" http://210.118.34.222/action/write_face.php";
	char cm2[1000];
//	테스트 소스 동적할당 사용자정보	
	
//	user_info=(u_info*)malloc(sizeof(u_info)*255);



	// 이벤트 풀의 크기만큼 events구조체를 생성한다.
	events = (struct epoll_event *)malloc(sizeof(*events) * EPOLL_SIZE);

	memset(cm2, 0x00, 1000);
	// epoll_create를 이용해서 epoll 지정자를 생성한다.	
	if ((epollFd = epoll_create(10)) < 0) {
		perror("epoll_create error");
		exit(1);
	}

	if ((pipeFd = open("../face/bin/write_face", O_RDWR)) < 0) {
		perror("fail to call open() : write_face");
		exit(1);
	}


	// 만들어진 듣기 소켓을 epoll이벤트 풀에 추가한다.
	// EPOLLIN(read) 이벤트의 발생을 탐지한다.
	ev.events = EPOLLIN;
	
	ev.data.fd = pipeFd;
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd, &ev);

	
	
	while(1) {
		int state, i;
		// epoll이벤트 풀에서 이벤트가 발생했는지를 검사한다.
		state = epoll_wait(epollFd, events, EPOLL_SIZE, 2000);
		switch(state) {
		case -1:
			perror("Epoll wait error");
			break;
		
		case 0:
			printf("No event in any pipe \n");
			break;

		default:
//			변경사항 적용시 flag 값 변경
//			flag 명 : isChanged
//			데이터타입 : int :1 1비트 사용
//			0 : off 변경사항없음
//			1 : on 변경사하있음
//			QoS에서 사용자의 정보가 변경되었는지 존재 유무 파악하는 데이터
	
			

			for (i = 0; i < state; i++) {
				if (events[i].data.fd == pipeFd) {
					readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
					if (readn > 0){
						sprintf(cm2, "%s%s%s", cmd, buffer,cmd2);
						system(cm2);
						printf("write_face : %s\n", buffer);
						printf("cm2 : %s\n", cm2);
						memset(cm2, 0x00, 1000);
//						usleep(300);
					}
					else printf("read error!\n");
				}
				memset(buffer, 0x00, BUFFER_SIZE);
			}
		}
	}
}
