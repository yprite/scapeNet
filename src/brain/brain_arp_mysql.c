#include "include/brain_mysql.h"

char *query_head = "UPDATE ip_data SET isStatus =CASE";
char *query_leg = "else '0' END WHERE isStatus IN(0,1)";
char query_result[3000];

int main(){

	int readn=0;
	int pipeFd=0;
	int isOn=0, returnbyte=0;
	char buffer[BUFFER_SIZE];
	char query_body[2000];
	if((pipeFd = open("/tmp/write_arp", O_RDWR))<0){
		perror("fail to call");	
		exit(1);
	}
	memset(buffer, 0x00, BUFFER_SIZE);
	while(1){
		if(isOn==1){
			MYSQL *connection=NULL, conn;
			int query_stat =0;
			mysql_init(&conn);
			connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
			sprintf(query_result, "%s WHEN pid= 252 THEN 1 %s %s", query_head, query_body, query_leg);
			query_stat = mysql_query(connection, query_result);
			memset(query_result, 0x00, strlen(query_result));
			memset(query_body, 0x00, strlen(query_body));
			returnbyte = 0;
			isOn=0;
			mysql_close(connection);
		}
		readn = read(pipeFd, buffer, BUFFER_SIZE);
		if(readn>0){
			char temp[20],ptr;
			int ip=0;	
			memset(temp, 0x00, BUFFER_SIZE);
			sprintf(temp, "%s", buffer+2);
			ip= ip_parse(temp);	
			if(ip==250){
				isOn=1;
			}
			returnbyte += sprintf(query_body+returnbyte, "WHEN pid =%d THEN 1 ", ip);
		}
		memset(buffer, 0x00, BUFFER_SIZE);

	}
	return 0;
}
