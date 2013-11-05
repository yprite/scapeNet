#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define EPOLL_SIZE 20
#define BUFFER_SIZE 255

typedef struct u_info{

	char source_ip[12];
	char port[5][10];
	char up_traffic_cur[10];
	char down_traffic_cur[10];
	char up_limit_traffic[10];
	char down_limit_traffic[10];
	int isStatus;
}u_info;


u_info user_info[255];


int main(void)
{
	struct epoll_event ev, *events;
	int epollFd, pipeFd[4];
	int readn, writen;
	int isChanged=0, isCheck=0;

	char buffer[BUFFER_SIZE];

//	테스트 소스 동적할당 사용자정보	
	
//	user_info=(u_info*)malloc(sizeof(u_info)*255);



	// 이벤트 풀의 크기만큼 events구조체를 생성한다.
	events = (struct epoll_event *)malloc(sizeof(*events) * EPOLL_SIZE);

	// epoll_create를 이용해서 epoll 지정자를 생성한다.	
	if ((epollFd = epoll_create(10)) < 0) {
		perror("epoll_create error");
		exit(1);
	}

	if ((pipeFd[0] = open("../senser/.read_face", O_RDWR)) < 0) {
		perror("fail to call open() : read_face");
		exit(1);
	}

	if ((pipeFd[1] = open("../senser/.write_face", O_RDWR)) < 0) {
		perror("fail to call open() : write_face");
		exit(1);
	}

	if ((pipeFd[2] = open("../senser/.read_sense", O_RDWR)) < 0) {
		perror("fail to call open() : read_sense");
		exit(1);
	}

	if ((pipeFd[3] = open("../senser/.write_sense", O_RDWR)) < 0) {
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
			perror("Epoll wait error");
			break;
		
		case 0:
			printf("No event in any pipe \n");
			if(isCheck ==0 || isChanged == 0){
				int i=0;
				for(i=1; i<255; i++){
					if(user_info[i].isStatus == 1){
					printf(" on node( 210.118.34.%d)\n", i);
					}
				}
			}
			break;

		default:
//			변경사항 적용시 flag 값 변경
//			flag 명 : isChanged
//			데이터타입 : int :1 1비트 사용
//			0 : off 변경사항없음
//			1 : on 변경사하있음
//			QoS에서 사용자의 정보가 변경되었는지 존재 유무 파악하는 데이터
	
			

			for (i = 0; i < state; i++) {
				if (events[i].data.fd == pipeFd[0]) {
					readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
					if (readn > 0){
		//				if(strcmp(buffer, "isChanged\n")==0){
		 				if((strcmp(buffer, "isChanged\n")==0)||isCheck==0){
							isChanged = 1;
							printf("Status is changed\n");
						}
						printf(".read_face : %s", buffer);
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
//					수정소스 이하
					if(readn>0 && isCheck){	
						if(buffer[0] =='!' && buffer[1] =='~'){
							char *ptr,ip[3];
							ptr = strtok(buffer, ".");
							while(ptr !=NULL){
								strcpy(ip, ptr);
								ptr=strtok(NULL, ".");
							}
							printf("ip : %d \n", atoi(ip));
							user_info[atoi(ip)].isStatus=1;
						}
					

//					수정소스 이하2 continue까지
						if(buffer[0] == '!' && buffer[1] == '@'){
							char *ip_ptr,*traffic_ptr,tmp[BUFFER_SIZE];
							char ip_src[3], traffic_cur[10];
							int ip_cnt=0,traffic_cnt=0;
		
							//문자열 복사 tmp
							strcpy(tmp, buffer);
							ip_ptr = strtok(tmp, ".&");
							while(ip_ptr != NULL){
								if(ip_cnt == 4){
									break;			
								}
								strcpy(ip_src, ip_ptr);
								ip_ptr = strtok(NULL, ".&");
								ip_cnt++;
							}
							//메모리 초기화
							memset(tmp, 0x00, BUFFER_SIZE);
							
							//문자열 복사 tmp
							strcpy(tmp, buffer);
							traffic_ptr = strtok(tmp, "&");

							while(traffic_ptr != NULL){
								if(traffic_cnt == 3){
									break;
								}
								strcpy(traffic_cur, traffic_ptr);
								traffic_ptr = strtok(NULL, "&");
								traffic_cnt++;
							}
// 상태확인 테스트 프린트					printf("ip_src : %s \t traffic_cur : %s\n", ip_src, traffic_cur);


							if(traffic_cur[0] == 'u'){
								traffic_cur[0] = '0';
								int tmp_up_traffic_cur = atoi(traffic_cur);
					
								if(atoi(user_info[atoi(ip_src)].up_limit_traffic) <= tmp_up_traffic_cur){
									printf("Kill Node (210.118.34.%d) \n", atoi(ip_src)); 
								}
							}
							else if(traffic_cur[0] == 'd'){
								traffic_cur[0] = '0';
								int tmp_up_traffic_cur = atoi(traffic_cur);
					
								if(atoi(user_info[atoi(ip_src)].down_limit_traffic) <= tmp_up_traffic_cur){
									printf("Kill Node (210.118.34.%d) \n", atoi(ip_src)); 
								}
							}
							printf("read_sense : %s\n", buffer);	
							
						}
						else 
							continue;
					}			
//					원본소스 이하
//					if (readn > 0) printf("read sense : %s\n", buffer);
//                                	else printf("read error!\n");
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
