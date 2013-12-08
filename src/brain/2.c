#include "include/brain_mysql.h"


//u_info user_info[255];

void *qos(void *data){

	char *str=0;

	str = (char*)data;
	system(data);	
}

int main(void)
{
    struct epoll_event ev, *events;
    int epollFd, pipeFd[8]; // epollFd : 이벤트 폴링 파일 디스크립터 
                            // pipeFd : 파이프 파일 디스크립터 6개 (등록할 수 있는 배열)
	// pipeFd[0] : pipe file read_face
	// pipeFd[1] : pipe file write_face
	// pipeFd[2] : pipe file read_sense
	// pipeFd[3] : pipe file read_sense2
	// pipeFd[4] : pipe file write_sense
	// pipeFd[5] : log file 
	// pipeFd[5] : pipe file write_php

/*------------------------------------------------------*/
    int readn;//, writen;      // readn : read한 바이트수
                            // writen : write한 바이트수

/*---------------------------------------------------*/
    pthread_t p_thread[2];   // pthread형 변수
    int thr_id=0, thr_id2=0;
    int status,isStatusArr[255]={0,};

/*---------------------------------------------------*/
    /*아직 미완성 변수 */
    int isChanged=0;//, isExit=0; // isChanged    : 상태 변경 
                                            // isChecked    : 트래픽량 체크 
                                            // isExit       : 프로그램 종료    
//    int stat=0;

    char buffer[BUFFER_SIZE];
    
    time_t timer;
    struct tm *t;
   
//    int temp_u=0, temp_d=0; 

//  테스트 소스 동적할당 사용자정보

//  쓰레드 생성 아규먼트 1
    
    thr_id = pthread_create(&p_thread[0], NULL, timer_function, NULL);
    if(thr_id < 0){
        perror("timer thread create error : ");
        exit(0);
    }
    brain_init_db(0);

//  user_info=(u_info*)malloc(sizeof(u_info)*255);
	
    brain_load_db(0);

    printf("DB Load ok\n");

    
//------------------------------------------------
// mysql db 로드 부분 문제점 발견 
/*    if(brain_mysql_init() != 0){
       return -1;
    }
    brain_mysql_load(QUERY1);
    brain_mysql_data_return();    
    //brain_mysql_data_print();
    brain_mysql_data_copy();
   int ip=1;
    for(ip=1; ip<255; ip++){
        printf("[%d]|%s|%s|%s|%s|%s|%s|%d|\n", ip,user_info[ip].source_ip, user_info[ip].mac, user_info[ip].up_traffic_cur, user_info[ip].down_traffic_cur, user_info[ip].up_traffic_limit, user_info[ip].down_traffic_limit, user_info[ip].isStatus);
    }
    brain_mysql_data_free();
    mysql_close(connection);*/

/*
    while((sql_row = mysql_fetch_row(sql_result))!=NULL){
            printf("%s|%s\n", sql_row[0],sql_row[1]);
    }
    */
    memset(buffer, 0x00, BUFFER_SIZE);
    // 이벤트 풀의 크기만큼 events구조체를 생성한다.
    events = (struct epoll_event *)malloc(sizeof(*events) * EPOLL_SIZE);

    // epoll_create를 이용해서 epoll 지정자를 생성한다.
    if ((epollFd = epoll_create(10)) < 0) {
        perror("epoll_create error");
        exit(1);
    }
    printf("------------------------------\n");
    printf("Pipe File Open Start\n");
    printf("\t[+]epoll_create Success\n");

    //if ((pipeFd[0] = open("./www/bin/read_face", O_RDWR)) < 0) {
    if ((pipeFd[0] = open("../../www/bin/read_face", O_RDWR)) < 0) {
        perror("fail to call open() : read_face");
        exit(1);
    }
    printf("\t[+]pipeFd[0] open Success\n");

    if ((pipeFd[1] = open("/tmp/write_face", O_RDWR|O_SYNC)) < 0) {
        perror("fail to call open() : write_face");
        exit(1);
    }
    printf("\t[+]pipeFd[1] open Success\n");

    if ((pipeFd[2] = open("/tmp/read_sense", O_RDWR)) < 0) {
        perror("fail to call open() : read_sense");
        exit(1);
    }
    printf("\t[+]pipeFd[2] open Success\n");

    if ((pipeFd[3] = open("/tmp/read_sense2", O_RDWR)) < 0) {
        perror("fail to call open() : read_sense2");
        exit(1);
    }
    printf("\t[+]pipeFd[3] open Success\n");

    if ((pipeFd[4] = open("/tmp/write_sense", O_RDWR|O_SYNC)) < 0) {
        perror("fail to call open() : write_sense");
        exit(1);
    }
    printf("\t[+]pipeFd[4] open Success\n");
    if ((pipeFd[5] = open("/tmp/error.log", O_RDWR | O_APPEND | O_CREAT)) < 0){
	perror("fail to call open() : error.log");
	exit(1);
    }
    printf("\t[+]pipeFd[5] open Success\n");
    if ((pipeFd[6] = open("/tmp/write_php", O_RDWR|O_SYNC)) < 0) {
        perror("fail to call open() : write_sense");
        exit(1);
    }
    printf("\t[+]pipeFd[6] open Success\n");
    
	if ((pipeFd[7] = open("/tmp/read_sense3", O_RDWR|O_SYNC)) < 0) {
        perror("fail to call open() : write_sense");
        exit(1);
    }
    printf("\t[+]pipeFd[7] open Success\n");

    printf("------------------------------\n");
    printf("Event Polling System start\n");
    // 만들어진 듣기 소켓을 epoll이벤트 풀에 추가한다.
    // EPOLLIN(read) 이벤트의 발생을 탐지한다.
    ev.events = EPOLLIN;

    ev.data.fd = pipeFd[0];
    epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[0], &ev);
    printf("\t[+]pipeFd[0] add in event_polling\n");

    ev.data.fd = pipeFd[2];
    epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[2], &ev);
    printf("\t[+]pipeFd[2] add in event_polling\n");

    ev.data.fd = pipeFd[3];
    epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[3], &ev);
	printf("\t[+]pipeFd[3] add in event_polling\n");

	ev.data.fd = pipeFd[7];
    epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[7], &ev);
	printf("\t[+]pipeFd[7] add in event_polling\n");

    printf("------------------------------\n");
    printf("Service Start\n");
    printf("------------------------------\n");
    while(1) {
        int state, i;
        // epoll이벤트 풀에서 이벤트가 발생했는지를 검사한다.
        state = epoll_wait(epollFd, events, EPOLL_SIZE, 2000);
        switch(state) {
        case -1:
            perror("Epoll wait error");
            break;

        case 0:
	    timer = time(NULL);
            t = localtime(&timer);
            printf("[%d.%d.%d|%d:%d:%d]\t System OK \n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
/*          if(isChecked ==0 || isChanged == 0){
                int i=0;
                for(i=1; i<255; i++){
                    if(user_info[i].isStatus == 1){
                    printf(" on node( 210.118.34.%d)\n", i);
                    }
                }
                isChecked=1;
            }*/
            break;
		
        default:
//          변경사항 적용시 flag 값 변경
//          flag 명 : isChanged
//          데이터타입 : int :1 1비트 사용
//          0 : off 변경사항없음
//          1 : on 변경사하있음
//          QoS에서 사용자의 정보가 변경되었는지 존재 유무 파악하는 데이터
        	for (i = 0; i < state; i++) {	
              	if (events[i].data.fd == pipeFd[0]) {
	    	       	readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
		            if (readn > 0){
							char write_temp[BUFFER_SIZE],write_temp2[BUFFER_SIZE];
							char *ptr_temp,*ptr_ip,*ptr_qos;
							char temp3[254],temp4[254];
							int ip=0;
							int i=0,j=0,returnbyte3=0;
                       		write(pipeFd[4], buffer, BUFFER_SIZE);
							sprintf(write_temp, "%s", buffer);
							ptr_temp = strtok(write_temp, " ");
							if(strcmp(ptr_temp, "k")==0){
								ptr_temp = strtok(NULL, " ");
								ptr_ip=strtok(ptr_temp, ".");
								for(i=1; i<=3; i++){
									ptr_ip = strtok(NULL, ".");		
									ip = atoi(ptr_ip);
								}
								sprintf(write_temp2, "%d:0:0:4E",ip);
								write(pipeFd[6], write_temp2, strlen(write_temp2));
								printf("kill : %s\n", write_temp2);
								user_info[ip].isStatus = 4;
								ptr_temp = NULL;
								ptr_ip = NULL;
								ip =0;
							}
							else if(strcmp(ptr_temp, "p") == 0){
								ptr_temp = strtok(NULL, " ");
								ptr_ip=strtok(ptr_temp, ".");
								for(i=1; i<=3; i++){
									ptr_ip = strtok(NULL, ".");		
									ip = atoi(ptr_ip);
								}
								sprintf(write_temp2, "%d:0:0:5E",ip);
								printf("pass : %s\n", write_temp2);
								write(pipeFd[6], write_temp2, strlen(write_temp2));
								user_info[ip].isStatus = 1;
								ptr_temp = NULL;
								ptr_ip = NULL;
								ip =0;
							}
/*							else if(strcmp(ptr_temp, "q") == 0){
								while(ptr_temp != NULL){
									returnbyte3 += sprintf(temp3+returnbyte3, "%s ", ptr_temp);
									ptr_temp = strtok(NULL, " ");
								}
								for(j=0; j<strlen(temp3); j++){
									temp4[j] = temp3[j+2];
								}
								write(pipeFd[6], temp4, strlen(temp4));


//								write(pipeFd[6], write_temp, strlen(write_temp));
							}*/
					}
					else printf("read_face error!\n");
        	   	}
				else if (events[i].data.fd == pipeFd[2]) {
/*				if(isCheckNode  == 0){
					char write_temp[BUFFER_SIZE];
					sprintf(write_temp, "0.0.0.0:0:0:6E");
					write(pipeFd[6], write_temp, strlen(write_temp));
					isCheckNode=1;
				}*/
                        	readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
                                if (readn > 0){
//					printf("user_info[56].up : %d, user_info[56].down : %d\n",  user_info[56].up_traffic_cur,  user_info[56].down_traffic_cur);
					int i=0,ip=0;
					char tmp[BUFFER_SIZE], *ptr_ip;
					for(i=0; i<readn; i++){
						tmp[i] = buffer[i+2];
					}
					i=0;
//					for(i=0; i<255; i++){
//						isNodeLive[i]=0;
//					}
//					i=0;
					ptr_ip = strtok(tmp, ".");
					while(ptr_ip != NULL){
						if(i ==3 ){
							ip = atoi(ptr_ip);
							break;
						}
						ptr_ip = strtok(NULL, ".");
						i++;
					}
//					printf("ip : %d\n", ip);
//					printf("isChecked :%d\n", isChecked);
					if(ip != 1 && isChecked == 0){
/*						if(abc%3 == 0){
							printf("abc : %d\n", abc);
							brain_update_db(1,ip,0,0,0);	
							abc=0;						
						}*/
						if(user_info[ip].isStatus <2 &&user_info[ip].isStatus>=0){
							char write_temp[BUFFER_SIZE];
							sprintf(write_temp, "%d:0:0:6E",ip);
							write(pipeFd[6], write_temp, strlen(write_temp));
//						isStatusArr[ip]=1;
									
//						printf("isNodeLive(%d) : %d\n", ip, isNodeLive[ip]);
//						brain_update_db(0, ip, user_info[ip].isStatus,0,0);
//						brain_update_db(0, ip, 0,1,user_info[ip].up_traffic_cur);
							user_info[ip].isStatus = 1;
						}
//						printf("user_info[%d].isStatus : %d\tup:%5ddown:%5d\n", ip,user_info[ip].isStatus,user_info[ip].up_traffic_cur, user_info[ip].down_traffic_cur);
//						brain_update_db(0,ip, user_info[ip].isStatus,user_info[ip].up_traffic_cur,user_info[ip].down_traffic_cur);
//						brain_update_db(0, ip, 0,2,user_info[ip].down_traffic_cur);
//						printf("scanning node : %d\n", ip);
						
					}
//					else if(ip != 1&& isChecked == 1){						
//						for(i=1; i<255; i++){
//							printf("user_info[%d].up : %d, user_info[%d].down : %d\n", i, user_info[i].up_traffic_cur, i, user_info[i].down_traffic_cur);
//							isNodeLive[ip]=1;
//							brain_update_db(0,i, user_info[i].isStatus,user_info[i].up_traffic_cur,user_info[i].down_traffic_cur);
//							for(i=1; i<255; i++){
//								user_info[i].down_traffic_cur=0;
//								user_info[i].up_traffic_cur=0;
//							}
//							if(i == 254){
//								printf("break\n");
//								isChecked = 2;
//							}
//						}
//					}
					
					ip=0;
				}
                                else printf("read error!\n");
			}
	                else if (events[i].data.fd == pipeFd[3]) {
				readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
//				printf("read_sense2 : %s\n", buffer);
				if(readn >0){
					char write_temp[BUFFER_SIZE];
					int i=0,ip=0,j=0; 
		            if(isChanged == 0 ||(buffer[1] == '@')){
						isChanged = 1; 
						if(isTime ==0 ){
							isTime = 2;
						}
						time_t timer;
						struct tm *t;
						char *ptr_L,*ptr_IP,tmp[BUFFER_SIZE],tmp_arr[4][20], down_temp[BUFFER_SIZE], up_temp[BUFFER_SIZE];
						int up_traffic_cur=0,down_traffic_cur=0;
						
						timer = time(NULL);
						t = localtime(&timer);
						
						for(i=0; i<readn; i++){
							tmp[i] = buffer[i+2];
						}
						i=0;
						ptr_L = strtok(tmp, "L\n");
						while(ptr_L != NULL){
							memcpy(tmp_arr[i], ptr_L, strlen(ptr_L)+1);
							ptr_L = strtok(NULL, "L\n");
							i++;
							}
						i=0;
						memset(tmp, 0x00, BUFFER_SIZE);
						memcpy(tmp, tmp_arr[0], strlen(tmp_arr[0])+1);
						ptr_IP = strtok(tmp, ".");
						while(ptr_IP != NULL){
							if( i == 3 ){
								ip=atoi(ptr_IP);
								i=0;
								break;
							}
							ptr_IP = strtok(NULL, ".");
							i++;
						}
						i=0;
						memset(tmp, 0x00, BUFFER_SIZE);
						if(ip == 252){
							int i=0;
							for(i=0; i<255; i++){
								if(user_info[i].isStatus != 0 || i != 252){
									user_info[252].up_traffic_cur += user_info[i].up_traffic_cur;	
									user_info[252].down_traffic_cur += user_info[i].down_traffic_cur;
								}
							
							}
							user_info[252].up_traffic_cur = user_info[252].up_traffic_cur/2048; 
							user_info[252].down_traffic_cur = user_info[252].down_traffic_cur/2048;
							sprintf(write_temp, "%d:%d:%d:%d", ip, user_info[252].up_traffic_cur, user_info[252].down_traffic_cur, 1);
							printf("\t\t\t\ttotal traffic : %s\n", write_temp);
							write(pipeFd[6], write_temp, strlen(write_temp));
							memset(write_temp, 0x00, BUFFER_SIZE);
						}
						else if(tmp_arr[2][0] == 'u'){
							for(i=0; i<strlen(tmp_arr[2]); i++){
								up_temp[i] = tmp_arr[2][i+1];
							}
							up_traffic_cur = atoi(up_temp);	
							user_info[ip].up_traffic_cur += up_traffic_cur;
//							temp_u = user_info[ip].up_traffic_cur;
							if(user_info[ip].up_count >=7){
								char buffer[100];
								printf("[%d.%2d.%2d|%2d:%2d:%2d]\t 210.118.34.%d is traffic over about upload\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,ip);
								sprintf(buffer, "[%d.%2d.%2d|%2d:%2d:%2d]\t Warnig (210.118.34.%d) : upload traffic over\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, ip);
								write(pipeFd[5], buffer, strlen(buffer));
								
								user_info[ip].isStatus=2;
								user_info[ip].up_count=0;
								sprintf(write_temp, "%d:%d:%d:%d", ip, user_info[ip].up_traffic_cur/1024, user_info[ip].down_traffic_cur/1024, user_info[ip].isStatus);
								write(pipeFd[6], write_temp, strlen(write_temp));
								memset(write_temp, 0x00, BUFFER_SIZE);
								user_info[ip].up_traffic_cur = 0;
								user_info[ip].isStatus=1;
							}
							if(isTime == 2){
								if(user_info[ip].up_traffic_cur/60 > atoi(user_info[ip].up_traffic_limit)){
									printf("[%d.%d.%d|%d:%d:%d]\t Warnig (210.118.34.%d)\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, ip);
									user_info[ip].up_count++;
									user_info[ip].isStatus=2;
									sprintf(write_temp, "%d:%d:%d:%d", ip, user_info[ip].up_traffic_cur/1024, user_info[ip].down_traffic_cur/1024, user_info[ip].isStatus);
									write(pipeFd[6], write_temp, strlen(write_temp));
									memset(write_temp, 0x00, BUFFER_SIZE);
									user_info[ip].up_traffic_cur = 0;
								}
//								else{
//									user_info[ip].isStatus =1;	
//								}
//								isTime=-1;
							}
//							if(isTimeOn >=3 && isTime ==2){
//								user_info[ip].up_count =0;
//								isTimeOn = 0;
//							}
						}
						else if(tmp_arr[2][0] == 'd'){
							for(i=0; i<strlen(tmp_arr[2]); i++){
								down_temp[i] = tmp_arr[2][i+1];
							}
							down_traffic_cur = atoi(down_temp);
							user_info[ip].down_traffic_cur +=down_traffic_cur;
//							temp_d = user_info[ip].down_traffic_cur;
//							printf("ip(%d) dw , %d\n",ip,user_info[ip].down_traffic_cur);
							if(user_info[ip].down_count >=7){
								char buffer[100];
								printf("[%d.%2d.%2d|%2d:%2d:%2d]\t 210.118.34.%d is traffic over about download %d\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,ip,user_info[ip].isStatus);
								sprintf(buffer, "[%d.%2d.%2d|%2d:%2d:%2d]\t Warnig (210.118.34.%d) : download traffic over\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, ip);
								write(pipeFd[5], buffer, strlen(buffer));
								user_info[ip].isStatus = 3;
								user_info[ip].down_count =0;
								sprintf(write_temp, "%d:%d:%d:%d", ip, user_info[ip].up_traffic_cur/1024, user_info[ip].down_traffic_cur/1024, user_info[ip].isStatus);
								write(pipeFd[6], write_temp, strlen(write_temp));
								memset(write_temp, 0x00, BUFFER_SIZE);
								user_info[ip].down_traffic_cur=0;
								user_info[ip].isStatus=1;
							} 
							if(isTime == 2){
								if(user_info[ip].down_traffic_cur / 60  > atoi(user_info[ip].down_traffic_limit)){
									printf("[%d.%2d.%2d|%2d:%2d:%2d]\t Warnig (210.118.34.%d)\n", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, ip);
									user_info[ip].down_count++;
									user_info[ip].isStatus=3;
									sprintf(write_temp, "%d:%d:%d:%d", ip, user_info[ip].up_traffic_cur/1024, user_info[ip].down_traffic_cur/1024, user_info[ip].isStatus);
									write(pipeFd[6], write_temp, strlen(write_temp));
									user_info[ip].down_traffic_cur=0;
								}
								isTime=-1;
							}
//							if(isTimeOn >=3 && isTime == 2){
//								user_info[ip].down_count =0;
//								isTimeOn = 0;
//							}
						}
					
						if(user_info[ip].isStatus >0){
							sprintf(write_temp, "%d:%d:%d:%d", ip, user_info[ip].up_traffic_cur/2048, user_info[ip].down_traffic_cur/2048, user_info[ip].isStatus);
							write(pipeFd[6], write_temp, strlen(write_temp));
							isCheckNode=0;
							memset(write_temp, 0x00, BUFFER_SIZE);
						}
					}
					isChanged=0;
					printf("%d:%d:%d:%d\n", ip, user_info[ip].up_traffic_cur, user_info[ip].down_traffic_cur, user_info[ip].isStatus);
				}
		                else printf("read_sense error!\n");//*/
				
			}
	       if (events[i].data.fd == pipeFd[7]) {
			    char temp[BUFFER_SIZE],write_temp[BUFFER_SIZE];
				char *token_order;
		   		readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
				sprintf(temp, "%s\n", buffer);
                if (readn > 0){
						int i=0,ip=0,port=0;
						token_order = strtok(temp, "D#.L");
						for(i=0; i<4; i++){
							if(i==3){
								ip = atoi(token_order);
							}
							token_order = strtok(NULL, "D#.L");
						}
						port = atoi(token_order);
						sprintf(write_temp, "%d:%d:0:8", ip,port);
						write(pipeFd[6], write_temp, strlen(write_temp));
				}
				else printf("read_sense3 error\n");
		   }
			memset(buffer, 0x00, BUFFER_SIZE);
		}
	 }//switch case
		usleep(100); 
	}//while
    pthread_join(p_thread[0], (void **)status);
    pthread_join(p_thread[1], (void **)status);
   
    return 0;  
}
