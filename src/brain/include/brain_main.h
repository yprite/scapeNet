#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#define EPOLL_SIZE 5
#define BUFFER_SIZE 255


typedef struct u_info{

    char source_ip[12];
    char port[5][10];
    char up_traffic_cur[10];
    char down_traffic_cur[10];
    char up_traffic_limit[10];
    char down_traffic_limit[10];
    int isStatus;

}u_info;
