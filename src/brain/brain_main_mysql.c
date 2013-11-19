#include "include/brain_mysql.h"


//u_info user_info[255];

int main(void)
{
    struct epoll_event ev, *events;
    int epollFd, pipeFd[5]; // epollFd : 이벤트 폴링 파일 디스크립터 
                            // pipeFd : 파이프 파일 디스크립터 5개 (등록할 수 있는 배열)

    int readn, writen;      // readn : read한 바이트수
                            // writen : write한 바이트수

    /*아직 미완성 변수 */
    int isChanged=0, isCheck=0; // isChanged :  상태 변경 

    int stat=0;
    

    char buffer[BUFFER_SIZE];

//  테스트 소스 동적할당 사용자정보

//  user_info=(u_info*)malloc(sizeof(u_info)*255);

    if(brain_mysql_init() != 0){
       return -1;
    }
    brain_mysql_load(QUERY1);
    brain_mysql_data_return();    
    //brain_mysql_data_print();
    brain_mysql_data_copy();
./*   int ip=1;
    for(ip=1; ip<255; ip++){
        printf("[%d]|%s|%s|%s|%s|%s|%s|%d|\n", ip,user_info[ip].source_ip, user_info[ip].mac, user_info[ip].up_traffic_cur, user_info[ip].down_traffic_cur, user_info[ip].up_traffic_limit, user_info[ip].down_traffic_limit, user_info[ip].isStatus);
    }*/
    brain_mysql_data_free();

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
    printf("[+]epoll_create Success\n");

    if ((pipeFd[0] = open("../bin/read_face", O_RDWR)) < 0) {
        perror("fail to call open() : read_face");
        exit(1);
    }
    printf("[+]pipeFd[0] open Success\n");

    if ((pipeFd[1] = open("../bin/write_face", O_RDWR)) < 0) {
        perror("fail to call open() : write_face");
        exit(1);
    }
    printf("[+]pipeFd[1] open Success\n");

    if ((pipeFd[2] = open("../bin/read_sense", O_RDWR)) < 0) {
        perror("fail to call open() : read_sense");
        exit(1);
    }
    printf("[+]pipeFd[2] open Success\n");

    if ((pipeFd[3] = open("../bin/read_sense2", O_RDWR)) < 0) {
        perror("fail to call open() : read_sense2");
        exit(1);
    }
    printf("[+]pipeFd[3] open Success\n");

    if ((pipeFd[4] = open("../bin/write_sense", O_RDWR)) < 0) {
        perror("fail to call open() : write_sense");
        exit(1);
    } 
    printf("[+]pipeFd[3] open Success\n");



    printf("----------------------\n");
    // 만들어진 듣기 소켓을 epoll이벤트 풀에 추가한다.
    // EPOLLIN(read) 이벤트의 발생을 탐지한다.
    ev.events = EPOLLIN;

    ev.data.fd = pipeFd[0];
    epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[0], &ev);
    printf("pipeFd[0] add in event_polling\n");

    ev.data.fd = pipeFd[2];
    epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[2], &ev);
    printf("pipeFd[2] add in event_polling\n");

    ev.data.fd = pipeFd[3];
    epoll_ctl(epollFd, EPOLL_CTL_ADD, pipeFd[3], &ev);
    printf("pipeFd[3] add in event_polling\n");


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
                isCheck=1;
            }
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
//              else if (events[i].data.fd == pipeFd[1]) {
//                                  readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
//                                  if (readn > 0) printf("write face : %s\n", buffer);
//                                  else printf("read error!\n");
//                           }
                else if (events[i].data.fd == pipeFd[2]) {
                    readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
                    if(readn >0){
                        printf("read_sense : %s\n", buffer);
//                        write(pipeFd[1], buffer, BUFFER_SIZE);
                    }
                    else printf("read_sense error!\n");
                }

//              else if (events[i].data.fd == pipeFd[3]) {
//                                  readn = read(events[i].data.fd, buffer, BUFFER_SIZE);
//                  if (readn > 0) printf("write sense : %s\n", buffer);
//                                  else printf("read error!\n");
//                 }
                memset(buffer, 0x00, BUFFER_SIZE);
            }
        }
    }
}
