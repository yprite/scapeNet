
//system header
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <fcntl.h>

//pthread header
#include <pthread.h>

//mysq header
#include "/usr/include/mysql/mysql.h"

//system header
#define EPOLL_SIZE 20
#define BUFFER_SIZE 255

//mysql define
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "scapenet"
#define CHOP(x) x[strlen(x)-1]=''

//Mysql Query
#define QUERY1 "select * from ip_data"

//Mysql Variable

MYSQL *connection, conn;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;
int query_stat;

//Main Variable
typedef struct u_info{
    char source_ip[20];
    char mac[20];
    char port[5][10];
    int up_traffic_cur;
    int down_traffic_cur;
    char up_traffic_limit[10];
    char down_traffic_limit[10];
    int isStatus;
}u_info;
u_info user_info[255];
int isTime;

//Mysql function
int brain_mysql_init();
int brain_mysql_load(char*);
int brain_mysql_data_return();
int brain_mysql_data_print();
void brain_mysql_data_free();
int brain_mysql_data_copy();

//Main function
int brain_main_init_data(int);// parameter 0: mysql, 1: sshdb 
void *timer_function(void *data);
