#include "include/brain_mysql.h" 




int main(){
	
	int readn=0;
	int pipeFd=0;
	char buffer[BUFFER_SIZE];

	if((pipeFd = open("/tmp/write_kill", O_RDWR))<0){
		perror("fail to call");	
		exit(1);
	}
	memset(buffer, 0x00, BUFFER_SIZE);
	while(1){
		readn = read(pipeFd, buffer, BUFFER_SIZE);
		if(readn>0){
				MYSQL *connection= NULL, conn;
				int query_stat =0,ip=0;
				char temp[BUFFER_SIZE];
				mysql_init(&conn);
				connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
				if(buffer[0] == 'k'){
					char query[BUFFER_SIZE];
					sprintf(temp, "%s", buffer+2);
					ip = ip_parse(temp);
					sprintf(query, "UPDATE ip_data SET isStatus = 4 where pid = %d", ip);
					query_stat = mysql_query(connection, query);
				}
				else if(buffer[0] == 'p'){
					char query[BUFFER_SIZE];
					sprintf(temp, "%s", buffer+2);	
					ip = ip_parse(temp);
					sprintf(query, "UPDATE ip_data SET isStatus = 1 where pid = %d", ip);
					query_stat = mysql_query(connection, query);
				}
				mysql_close(connection);
		}
		memset(buffer, 0x00, BUFFER_SIZE);
		
	}
	return 0;
}
