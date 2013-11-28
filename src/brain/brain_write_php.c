#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include "/usr/include/mysql/mysql.h"

#define EPOLL_SIZE 20
#define BUFFER_SIZE 255

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "scapenet"

void *timer_function(void *data);
char *query_head = "UPDATE ip_data SET isStatus = CASE";
char query_body[4000]; 
char *query_leg = "else '0' END WHERE isStatus IN (0,1)";
char query_result[5000];
int isChecked = 0;
int isLiveNode[255];
int main(void)
{
	struct epoll_event ev, *events;
	int epollFd, pipeFd[1];
	int readn, writen;
	int ip=0, up_traffic=0, down_traffic=0, isStatus=0;
	int cnt_read=0;
	char buffer[BUFFER_SIZE];
	int status;
	int isScanNode=0;
	int returnbyte=0;
	MYSQL *connection = NULL, conn;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_stat=0;
	int tempi=0;

	pthread_t p_thread[1];
	int thr_id = 0;
	
	// 이벤트 풀의 크기만큼 events구조체를 생성한다.
	events = (struct epoll_event *)malloc(sizeof(*events) * EPOLL_SIZE);

	// epoll_create를 이용해서 epoll 지정자를 생성한다.	
	if ((epollFd = epoll_create(10)) < 0) {
		perror("epoll_create error");
		exit(1);
	}

	if ((pipeFd[0] = open("../bin/write_php", O_RDWR)) < 0) {
		perror("fail to call open() : read_face");
		exit(1);
	}
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	
//	thr_id = pthread_create(&p_thread[0], NULL, timer_function, NULL);
	

	ev.events = EPOLLIN;
	ev.data.fd = pipeFd[0];
	epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[0], &ev);
	
	while(1) {
		int state, i;
		char temp_buffer2[BUFFER_SIZE];
		int q=0;
		// epoll이벤트 풀에서 이벤트가 발생했는지를 검사한다.
		state = epoll_wait(epollFd, events, EPOLL_SIZE, 1000);
		switch(state) {
		case -1:
			perror("epoll wait error");
			break;
		
		case 0:
//			if(isChecked == 1){
//				for(q=1; q<255; q++){
//					memset(temp_buffer2, 0x00, BUFFER_SIZE);
//					sprintf(temp_buffer2, "update ip_data set isStatus = 0 where pid = %d", q);
//					query_stat = mysql_query(connection, temp_buffer2);
//					printf("tmpe_buffer2 : %s\n", temp_buffer2);
//				}
				printf("No event\n");
//				isChecked =0;
//			}
			break;

		default:
			for (i = 0; i < state; i++) {
				if (events[i].data.fd == pipeFd[0]) {
					char *ptr, temp_buffer[BUFFER_SIZE];
					int cnt=0;
					readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
					if (readn > 0){
						sprintf(temp_buffer, "%s", buffer);
						ptr = strtok(temp_buffer, ":E");
						while(ptr != NULL){
							if(cnt == 0){
								ip = atoi(ptr);
							}
							else if(cnt == 1){
								up_traffic = atoi(ptr);
							}
							else if(cnt == 2){
								down_traffic = atoi(ptr);
							}
							else if(cnt == 3){
								isStatus = atoi(ptr);
								break;
							}
							ptr = strtok(NULL, ":E");
							cnt++;
						}
						cnt = 0;
						memset(temp_buffer, 0x00, BUFFER_SIZE);
						if((tempi-isStatus)==5){
							printf("Scanning Node\n");
							sprintf(query_result, "%s %s%s", query_head, query_body, query_leg);
							printf("%s\n", query_result);
							query_stat = mysql_query(connection, query_result);	
							memset(query_result, 0x00, strlen(query_result));
							returnbyte =0;
							tempi=0;
						}
						if(isStatus == 1 ){
							sprintf(temp_buffer, "update ip_data set up_traffic_cur = %d, down_traffic_cur = %d, isStatus = %d where pid = %d", up_traffic, down_traffic, isStatus,ip);
//							printf("update ip_data set up_traffic_cur = %d, down_traffic_cur = %d, isStatus = %d where pid = %d\n", up_traffic, down_traffic, isStatus,ip);
							query_stat = mysql_query(connection, temp_buffer);
							cnt_read=0;
							isScanNode =0;
							memset(temp_buffer, 0x00, BUFFER_SIZE);
						}
						else if(isStatus >1 &&isStatus<6){
							sprintf(temp_buffer, "update ip_data set up_traffic_cur = %d, down_traffic_cur = %d, isStatus = %d where pid = %d", up_traffic, down_traffic, isStatus,ip);
//							printf("update ip_data set up_traffic_cur = %d, down_traffic_cur = %d, isStatus = %d where pid = %d\n", up_traffic, down_traffic, isStatus,ip);
							query_stat = mysql_query(connection, temp_buffer);
							memset(temp_buffer, 0x00, BUFFER_SIZE);
						}
					}
					if(isStatus == 6){
//						printf("ARP Scanning\n");
						returnbyte += sprintf(query_body + returnbyte, "WHEN pid = %d THEN 1 ", ip);
						isLiveNode[ip]=1;
						cnt_read =0;	
						isScanNode =0;
						tempi=isStatus;
					}	
					cnt_read++;
				}
				memset(buffer, 0x00, BUFFER_SIZE);
			}
		}
	}
	pthread_join(p_thread[0], (void**)status);
	mysql_close(connection);
}


void *timer_function(void *data){
	while(1){
		sleep(60);
		isChecked=0;
	}

}
