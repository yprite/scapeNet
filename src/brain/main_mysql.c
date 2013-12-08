#include "include/brain_mysql.h"

void init_db();
void load_db();
void pipe_open();


//MYSQL *connection = NULL, conn;
//MYSQL_RES *sql_result;
//MYSQL_ROW sql_row;
//int query_stat =0;
int pipeFd[8];

int main(void){

	struct epoll_event ev, *events;
	int epollFd, logFd;
	char buffer[BUFFER_SIZE];
//	Description	pipeFd
//	pipeFd[0] :	read_face		->	WEB
//	pipeFd[1] :	read_sense		->	ARP
//	pipeFd[2] :	read_sense2		->	traffic
//	pipeFd[3] :	read_sense3		-> 	PORT
//	pipeFd[4] :	write_arp		->	DB ARP
//	pipeFd[5] :	write_traffic	->	DB traffic
//	pipeFd[6] :	write_qos		->	DB QoS
//	pipeFd[7] :	write_port		->	DB port
	
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

		state = epoll_wait(epollFd, eventsm EPOLL_SIZE, 1000);
		switch(state){

			case -1:
				perror("Epoll wait error");
				break;

			case 0:
				printf("No Evenet\r");
				break;

			default:
				for(i=0; i<state; i++){
					if(events[i].data.fd == pipeFd[0]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							printf("read_face buffer : %s\n", buffer);		
						}
						else{
							printf("read_face error\n");
						}
					}				
					else if(events[i].data.fd == pipeFd[1]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							printf("read_sense buffer : %s\n", buffer);		
						}
						else{
							printf("read_sense error\n");
						}
					}				
					else if(events[i].data.fd == pipeFd[2]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							printf("read_sense2 buffer : %s\n", buffer);		
						}
						else{
							printf("read_sense2 error\n");
						}
						
					}				
					else if(events[i].data.fd == pipeFd[3]){
						readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
						if(readn >0){
							printf("read_sense3 buffer : %s\n", buffer);		
						}
						else{
							printf("read_sense3 error\n");
						}
					}				
					
					
					
				}
		}
	}
	return 0;
}
void pipe_open(){
	if((pipeFd[0] = open("../../www/bin/read_face", O_RDWR))<0){
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
	if((pipeFd[5] = open("/tmp/write_tarffic", O_RDWR))<0){
		perror("fail to call open() : write_traffic");
		exit(1);
	}
	if((pipeFd[6] = open("/tmp/write_qos", O_RDWR))<0){
		perror("fail to call open() : write_qos");
		exit(1);
	}
	if((pipeFd[7] = open("/tmp/write_port", O_RDWR))<0){
		perror("fail to call open() : write_port");
		exit(1);
	}
}
void init_db(){
	int i=0;
	char temp[BUFFER_SIZE];
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	for(i=1; i<255; i++){
		 sprintf(temp, "update ip_data set isStatus = 0 ,up_traffic_cur =0, down_traffic_cur =0 where pid = %d", ip);
		 query_stat = mysql_query(connection, temp);
	}
}
void load_db(){
	char temp[20];
	int ip=0;
	query_stat = mysql_query(connection, "select * from ip_data");	
	sql_result = mysql_store_result(connection);
	while((sql_row = mysql_fetch_row(sql_result))!= NULL){
			ip=atoi(sql_row[0]);
			sprintf(user_info[ip].source_ip, "%s\n", sql_row[1]);
			sprintf(user_info[ip].mac, "%s\n", sql_row[2]);
			sprintf(user_info[ip].up_traffic_limit, "%s\n", sql_row[5]);
			sprintf(user_info[ip].down_traffic_limit, "%s\n", sql_row[6]);
	}
	printf("DB Load Ok\r");
}
