#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "/usr/include/mysql/mysql.h"


#define EPOLL_SIZE 20
#define BUFFER_SIZE 255
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "gnsrjs833"
#define DB_NAME "scapenet"
#define CHOP(x) x[strlen(x)-1]=''




typedef struct u_info{
	char source_ip[12];
	char port[5][10];
	int up_traffic_cur;
	int down_traffic_cur;
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
	int ip_cnt=1;
	char buffer[BUFFER_SIZE];

//	테스트 소스 동적할당 사용자정보	
	
//	user_info=(u_info*)malloc(sizeof(u_info)*255);


//--------------------------------------------------------	
// 초기화부분 수정 전 함수화 필요(모듈화 추후 예정)
// 모듈명 init_user_info()
// 반환값 
// 성공시 0
// 실패시 1
	MYSQL       *connection = NULL, conn;
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	int query_stat = 0;
	char query[BUFFER_SIZE];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

	if(connection == NULL){
		perror("Mysql Connection Error\n");
		exit(1);
	}
	
	query_stat = mysql_query(connection, "select * from user");

	if(query_stat != 0){
		perror("Mysql query error");
		exit(1);
	}

	sql_result = mysql_store_result(connection);

	printf("\tMemory status in user table on the mysql\n");
	printf("-----------------------------------------------------------------\n");
	printf("|%+20s|%+20s|%+10s|%+10s|\n", "MAC ADDRESS", "IP ADDRESS", "UP_LIMIT", "DOWN_LIMIT");
	printf("-----------------------------------------------------------------\n");
		
	while((sql_row = mysql_fetch_row(sql_result)) != NULL){
		char temp[20];
		char *ptr;
		int ip,cnt=0;
		strcpy(temp, sql_row[1]);
//		printf("sql_row[1] : %s\t temp : %s\n", sql_row[1], temp);
		ptr = strtok(temp, ".");
		while(ptr != NULL){
			if(cnt == 3){
				ip=atoi(ptr);
				break;	
			}
//			printf("ptr : %s\n", ptr);
			ptr = strtok(NULL, ".");
			cnt++;
		}
//		printf("ip : %d\n", ip);
		strcpy(user_info[ip].source_ip,  sql_row[1]);
		strcpy(user_info[ip].up_limit_traffic, sql_row[2]);
		strcpy(user_info[ip].down_limit_traffic,  sql_row[3]);
		
		printf("|%+20s|%+20s|%+10s|%+10s|\n", sql_row[0],sql_row[1], sql_row[2], sql_row[3]);
		isCheck=1;	
	}
	printf("-----------------------------------------------------------------\n");
	printf("\tMemory status in user_info on the c program\n");
	printf("-----------------------------------------------------------------\n");
	while(ip_cnt<255){
//	while(user_info[ip_cnt++].source_ip != NULL){
		if(strlen(user_info[ip_cnt].source_ip) != 0){	
			printf("|%+20s|%+20s|%+10s|%+10s|\n", user_info[ip_cnt].up_traffic_cur,user_info[ip_cnt].source_ip,
							user_info[ip_cnt].up_limit_traffic,
							user_info[ip_cnt].down_limit_traffic);
		}
		ip_cnt++;
	}
	mysql_free_result(sql_result);

	mysql_close(connection);

//--------------------------------------------------------	

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
					if(readn>0 && isCheck == 1){	
						if(buffer[0] =='!' && buffer[1] =='~'){
							char *ptr,ip[3];
							ptr = strtok(buffer, ".");
							while(ptr !=NULL){
								strcpy(ip, ptr);
								ptr=strtok(NULL, ".");
							}
//ip 확인							printf("ip : %d \n", atoi(ip));
							user_info[atoi(ip)].isStatus=1;
						}
					

//					수정소스 이하2 continue까지
						if(buffer[0] == '!' && buffer[1] == '@'){
							char *ip_ptr,*traffic_ptr,tmp[BUFFER_SIZE];
							char ip_src[3], traffic_cur[10];
							int ip_cnt=0,traffic_cnt=0,ip=0;
//문자열 복사를 안할경우  buffer에 영향을 끼침		
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
							ip = atoi(ip_src);
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
								user_info[ip].up_traffic_cur += (atoi(traffic_cur));
								printf("up_traffic_cur : %d \n", user_info[ip].up_traffic_cur);
								if(atoi(user_info[ip].up_limit_traffic) <= user_info[ip].up_traffic_cur){
									printf("Kill Node (210.118.34.%d) \n", ip); 
								}
							}
/*							else if(traffic_cur[0] == 'd'){
								traffic_cur[0] = '0';
								int tmp_up_traffic_cur = atoi(traffic_cur);
					
								if(atoi(user_info[ip].down_limit_traffic) <= tmp_up_traffic_cur){
									printf("Kill Node (210.118.34.%d) \n", ip); 
								}
							}*/
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
