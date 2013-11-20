#include "include/brain_mysql.h"


//u_info user_info[255];

int main(void)
{
    struct epoll_event ev, *events;
    int epollFd, pipeFd[5]; // epollFd : 이벤트 폴링 파일 디스크립터 
                            // pipeFd : 파이프 파일 디스크립터 5개 (등록할 수 있는 배열)

/*------------------------------------------------------*/
    int readn;//, writen;      // readn : read한 바이트수
                            // writen : write한 바이트수

/*---------------------------------------------------*/
    pthread_t p_thread[2];   // pthread형 변수
    int thr_id=0, thr_id2=0;
    int status;

/*---------------------------------------------------*/
    /*아직 미완성 변수 */
    int isChanged=0, isChecked=0;//, isExit=0; // isChanged    : 상태 변경 
                                            // isChecked    : 트래픽량 체크 
                                            // isExit       : 프로그램 종료    
//    int stat=0;

    char buffer[BUFFER_SIZE];

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
//    thr_id2 = pthread_create(&p_thread[1], NULL, check_Node, NULL);
    if(thr_id2 < 0){
	perror("check thread create error : ");
	exit(0);
    }

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

    if ((pipeFd[0] = open("../bin/read_face", O_RDWR)) < 0) {
        perror("fail to call open() : read_face");
        exit(1);
    }
    printf("\t[+]pipeFd[0] open Success\n");

    if ((pipeFd[1] = open("../bin/write_face", O_RDWR)) < 0) {
        perror("fail to call open() : write_face");
        exit(1);
    }
    printf("\t[+]pipeFd[1] open Success\n");

    if ((pipeFd[2] = open("../bin/read_sense", O_RDWR)) < 0) {
        perror("fail to call open() : read_sense");
        exit(1);
    }
    printf("\t[+]pipeFd[2] open Success\n");

    if ((pipeFd[3] = open("../bin/read_sense2", O_RDWR)) < 0) {
        perror("fail to call open() : read_sense2");
        exit(1);
    }
    printf("\t[+]pipeFd[3] open Success\n");

    if ((pipeFd[4] = open("../bin/write_sense", O_RDWR)) < 0) {
        perror("fail to call open() : write_sense");
        exit(1);
    } 
    printf("\t[+]pipeFd[4] open Success\n");



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
	    isCheckNode = 1;
            printf("No event in any pipe \n");
/*          if(isChecked ==0 || isChanged == 0){
                int i=0;
                for(i=1; i<255; i++){
                    if(user_info[i].isStatus == 1){
                    printf(" on node( 210.118.34.%d)\n", i);
                    }
                }
                isChecked=1;
            }*/
	    isCheckNode = 0;
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
        	                	printf("read_Face : %s\n", buffer);
/*                        if(
                        write(pipeFd[3], buffer, BUFFER_SIZE);*/
				}
				else printf("read_face error!\n");
                	}
			else if (events[i].data.fd == pipeFd[2]) {
				if(isCheckNode == 1){
					brain_init_db(0);
				}
				isCheckNode =0;
                        	readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
                                if (readn > 0){
//					printf("pipeFd[2] read string : %s", buffer);
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
					if(ip != 1){
						user_info[ip].isStatus = 1;
						isNodeLive[ip]=1;
//						printf("isNodeLive(%d) : %d\n", ip, isNodeLive[ip]);
						brain_update_db(0, ip, 1);
//						printf("scanning node : %d\n", ip);
					}
					
					ip=0;
				}
                                else printf("read error!\n");
			}
	                else if (events[i].data.fd == pipeFd[3]) {
				
				isCheckNode = 1;
				readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
//				printf("read_sense2 : %s\n", buffer);
				if(readn >0){
		                        if(isChanged == 0 ||(buffer[1] == '@')){
						isChanged = 1; 
						if(isTime ==0 ){
							isTime = 2;
						}
						char *ptr_L,*ptr_IP,tmp[BUFFER_SIZE],tmp_arr[4][20], down_temp[BUFFER_SIZE], up_temp[BUFFER_SIZE];
						int i=0,ip=0; 
						int up_traffic_cur=0,down_traffic_cur=0;
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
						
//						for(i=0; i<strlen(tmp_arr[2]); i++){
//							tmp[i] = tmp_arr[2][i+1];
//                           			}
//						temp_traffic = atoi(tmp);
						if(tmp_arr[2][0] == 'u'){
							for(i=0; i<strlen(tmp_arr[2]); i++){
								up_temp[i] = tmp_arr[2][i+1];
							}
							up_traffic_cur = atoi(up_temp);	
							user_info[ip].up_traffic_cur += up_traffic_cur;
//							printf("up : %d\n", user_info[ip].up_traffic_cur);
							if(isTime == 2){
//								printf("user_info[%d].up_traffic_cur : %d\n", ip, user_info[ip].up_traffic_cur);
//								printf("user_info[%d].up_traffic_limit : %d\n", ip, atoi(user_info[ip].up_traffic_limit));
//								printf("isTime is on\n");
								
								if(user_info[ip].up_traffic_cur > atoi(user_info[ip].up_traffic_limit)){
									printf("Kill Node (%d):up_traffic over\n", ip);
									user_info[ip].up_traffic_cur = 0;
								}
								isTime=-1;
							} 
						}
						else if(tmp_arr[2][0] == 'd'){
							for(i=0; i<strlen(tmp_arr[2]); i++){
								down_temp[i] = tmp_arr[2][i+1];
							}
							down_traffic_cur = atoi(down_temp);
							user_info[ip].down_traffic_cur +=down_traffic_cur;
							if(isTime == 2){
//								printf("user_info[%d].down_traffic_cur : %d\n", ip, user_info[ip].down_traffic_cur);
//								printf("user_info[%d].down_traffic_limit : %d\n", ip, atoi(user_info[ip].down_traffic_limit));
								if(user_info[ip].down_traffic_cur > atoi(user_info[ip].down_traffic_limit)){
									printf("Kill Node (%d):down_traffic over\n", ip);
									user_info[ip].down_traffic_cur = 0;
								}
								isTime=-1;
							} 
						}
					}
					isChanged=0;
				}
		                else printf("read_sense error!\n");//*/
				isCheckNode = 0;
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
