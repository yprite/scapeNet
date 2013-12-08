#ifndef _MYSQL
#define _MYSQL

//mysql header
#include "/usr/include/mysql/mysql.h"
#endif
#include "brain_system.h"
//mysql define
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "scapenet"
#define CHOP(x) x[strlen(x)-1]=''

//Mysql Query
#define QUERY1 "select * from ip_data"

//Mysql Variable


//Main Variable
/*typedef struct u_info{
	char source_ip[20];
	char mac[20];
	//    char port[5][10];
	int up_traffic_cur;
	int down_traffic_cur;
	char up_traffic_limit[10];
	char down_traffic_limit[10];
	int up_count;
	int down_count;
	int isStatus;
}u_info;
u_info user_info[255];*/
