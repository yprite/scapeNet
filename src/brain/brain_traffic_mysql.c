/**
 * Brain Traffic Mysql
 * Author Kim Yonghun
 */

#include "include/brain_mysql.h" 

#define UP_LIMIT 4000
#define DOWN_LIMIT 4000

volatile int up_traffic[BUFFER_SIZE],down_traffic[BUFFER_SIZE];
int isOn;
pthread_mutex_t lock;

/**
 * Brain CheckTraffic 관리 함수 
 */
void *CheckTraffic(void *arg){

	while(1){

		MYSQL *connection= NULL, conn;
		int query_stat =0,ip=0;
		char temp[BUFFER_SIZE];


		//		pthread_mutex_lock(&lock);
		if(isOn==1){
			mysql_init(&conn);
			connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
			for(ip=1; ip<255; ip++){
			//	up_traffic[ip] /= 1024;
			//	down_traffic[ip] /= 1024;
				if(ip==252){
					sprintf(temp, "UPDATE ip_data SET up_traffic_cur = %d, down_traffic_cur = %d, isStatus = 1 where pid =%d", up_traffic[ip], down_traffic[ip], ip);
					query_stat = mysql_query(connection, temp);
//					printf("Server(%d:%d)%d\n", up_traffic[ip],down_traffic[ip],query_stat);
					up_traffic[ip]=0;
					down_traffic[ip]=0;
				}
				else if(up_traffic[ip]>UP_LIMIT){
					sprintf(temp, "UPDATE ip_data SET up_traffic_cur = %d, down_traffic_cur = %d, isStatus = 2 where pid =%d and isStatus between 0 and 3", up_traffic[ip], down_traffic[ip], ip);
					query_stat = mysql_query(connection, temp);
//					printf("UP(%d:%d:%d)%d\n", ip,up_traffic[ip],down_traffic[ip],query_stat);
					up_traffic[ip]=0;
					down_traffic[ip]=0;

				}
				else if(down_traffic[ip]>DOWN_LIMIT){
					sprintf(temp, "UPDATE ip_data SET up_traffic_cur = %d, down_traffic_cur = %d, isStatus = 3 where pid =%d and isStatus between 0 and 3", up_traffic[ip], down_traffic[ip], ip);
					query_stat = mysql_query(connection, temp);
//					printf("DOWN(%d:%d:%d)%d\n", ip,up_traffic[ip],down_traffic[ip],query_stat);
					up_traffic[ip]=0;
					down_traffic[ip]=0;
				}
				else{
					//					printf("[%d] :%d :%d\n", ip, up_traffic[ip], down_traffic[ip]);
					sprintf(temp, "UPDATE ip_data SET up_traffic_cur = %d, down_traffic_cur = %d, isStatus = 1 where pid =%d and isStatus between 1 and 3", up_traffic[ip], down_traffic[ip], ip);
					query_stat = mysql_query(connection, temp);
//					printf("NORMAL(%d:%d:%d)%d\n", ip,up_traffic[ip],down_traffic[ip],query_stat);
					up_traffic[ip]=0;
					down_traffic[ip]=0;
					usleep(10);
				}
				memset(temp, 0x00, BUFFER_SIZE);

			}
			isOn=0;
			mysql_close(connection);
		}
		//		pthread_mutex_unlock(&lock);
		sleep(1);
		isOn=1;
	}
}
/**
 * Brain Pipe 전달 함수 
 */

int main(){

	int readn=0;
	int pipeFd=0;
	char buffer[BUFFER_SIZE];
	pthread_t t1;

	if((pipeFd = open("/tmp/write_traffic", O_RDWR))<0){
		perror("fail to call");
		exit(1);		
	}
	pthread_mutex_init(&lock, NULL);
	memset(buffer, 0x00, BUFFER_SIZE);
	pthread_create(&t1, NULL, CheckTraffic, NULL);

	while(1){
		readn = read(pipeFd, buffer, BUFFER_SIZE);
		if(readn>0){
			if(isOn!=1){
				int ip=0,cnt=0;
				char temp[BUFFER_SIZE];
				char *ptr;
				sprintf(temp, "%s", buffer+13);
				ptr = strtok(temp, "L");
				while(ptr != NULL){
					if(cnt ==0){
						ip=atoi(ptr);
					}
					else if(cnt==2){
						//						pthread_mutex_lock(&lock);
						if(ptr[0] =='u'){
							sprintf(temp, "%s", ptr+1);
							up_traffic[ip] += atoi(temp);
							//							printf("u :%d( %d)\n", ip, up_traffic[ip]);
						}
						else if(ptr[0] =='d'){
							sprintf(temp, "%s", ptr+1);
							down_traffic[ip] += atoi(temp);
							//							printf("d :%d( %d)\n", ip, down_traffic[ip]);
						}
					}
					ptr =strtok(NULL, "L");
					cnt++;
				}
			}
		}
		memset(buffer, 0x00, BUFFER_SIZE);

	}
	return 0;
}
