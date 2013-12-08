#include "include/brain_mysql.h" 



int main(){
	
	int readn=0;
	int pipeFd=0;
	char buffer[BUFFER_SIZE];

	if((pipeFd = open("/tmp/write_port", O_RDWR))<0){
		perror("fail to call");	
		exit(1);
	}
	memset(buffer, 0x00, BUFFER_SIZE);
	while(1){
		readn = read(pipeFd, buffer, BUFFER_SIZE);
		if(readn>0){
				MYSQL *connection= NULL, conn;
				int query_stat =0,ip=0;
				char temp[BUFFER_SIZE],port[BUFFER_SIZE];
				char *ptr;
				memset(port, 0x00, BUFFER_SIZE);
				mysql_init(&conn);
				connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

				sprintf(temp, "%s", buffer+13);
				ptr = strtok(temp, "L");
				ip=atoi(ptr);
				ptr =strtok(NULL, "L");
				sprintf(port, "%s", ptr);
//				printf("%d\n", port);
				memset(temp, 0x00, BUFFER_SIZE);
				sprintf(temp, "UPDATE ip_data SET port = \"%s\" where pid = %d", port,ip);
				query_stat = mysql_query(connection, temp);
				// db insert 
				
				mysql_close(connection);
		}
		memset(buffer, 0x00, BUFFER_SIZE);
		
	}
	return 0;
}
