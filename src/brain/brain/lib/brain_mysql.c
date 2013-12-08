#include "../include/brain_mysql.h"


int brain_mysql_init(){
   
    if(mysql_init(&conn) == 0){
         perror("mysql_init() error");
         return -1;
    }
    else{
//        printf("DB(mysql) init Ok\n");
        if((connection =  mysql_real_connect(&conn,DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0)) == 0 ){
            perror("mysql_real_connect() error");
            exit(1);
        }
//        else{
//            printf("DB(mysql) connection OK\n");
//        }       
    }
    return 0;
}

int brain_mysql_load(char *str){
    query_stat = mysql_query(connection, str);
    if(query_stat != 0){
        perror("mysql_query error");
	return -2;
    }
    else return 0;
}
int brain_mysql_data_return(){
    
    sql_result = mysql_store_result(connection);
    if(sql_result == NULL){
        perror("myql_store_result error");
	exit(1);
//	return -3;
    }
    return 0;
}
int brain_mysql_data_print(){
    while((sql_row = mysql_fetch_row(sql_result))!=NULL){
        printf("|%10s|%20s|%20s|%10s|%10s|%10s|%10s|%10s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6], sql_row[7]);
    }    
    return 0;
}
int brain_mysql_data_copy(){
    char temp[20];
    char *ptr;
    int ip=0,cnt=0;
    while((sql_row = mysql_fetch_row(sql_result))!=NULL){
//        strcpy(temp, sql_row[1]);
        sprintf(temp, "%s", sql_row[1]);
        ptr = strtok(temp, ".");
        while(ptr != NULL){
            if(cnt == 3){
                ip=atoi(ptr);
                cnt=0;
                break;
            }
            ptr = strtok(NULL, ".");
            cnt++;
        }
        
//        printf("user_info[%d]|%s|%s|%s|%s|\n", ip,sql_row[1], sql_row[2], sql_row[5], sql_row[6]);
//          sprintf(user_info[ip].source_ip, "%s", sql_row[1]);
        strcpy(user_info[ip].source_ip, sql_row[1]);
        strcpy(user_info[ip].mac, sql_row[2]);
        strcpy(user_info[ip].up_traffic_limit, sql_row[5]);
        strcpy(user_info[ip].down_traffic_limit, sql_row[6]);
        
    }
    return 0;
}
void brain_mysql_data_free(){
    mysql_free_result(sql_result);
}
int brain_init_db(int mode){
	if(mode == 0){
		int ip=0;
		char temp[BUFFER_SIZE];
		if(brain_mysql_init() != 0){
			printf("return value : -1 |error in brain_init_db()\n");
			return -1;
		}
		for(ip=1; ip<255; ip++){
			sprintf(temp, "update ip_data set isStatus = 0 ,up_traffic_cur =0, down_traffic_cur =0 where pid = %d", ip);
//			printf("temp : %s\n", temp);
			if(brain_mysql_load(temp) != 0){
				printf("return value : -2 |error in brain_init_db()\n");
				return -2;
			}
//			usleep(10);
		}
		mysql_close(connection);
	}
	else if(mode==1){
		printf("SSHDB Init\n");
	}
	printf("DB Initialize OK\n");
	return 0;
}

int brain_load_db(int mode){
	if(mode ==0){
		if(brain_mysql_init() !=0){
			return -1;
		}
		if(brain_mysql_load(QUERY1) != 0){
			return -2;
		}
		if(brain_mysql_data_return() != 0){
			return -3;
		}
		if(brain_mysql_data_copy() != 0){
			return -4;
		}
		brain_mysql_data_free();
		mysql_close(connection);
	}
	else if(mode ==1){
		printf("SSHDB Load\n");
	}
	return 0;
}
int brain_update_db(int mode, int ip, int isOn, int up_traffic_cur,int down_traffic_cur){

	if(mode == 0){
		if(brain_mysql_init() != 0){
			printf(" return value : -1 |error in brain_update_db()\n");
			return -1;
		}
		char temp[BUFFER_SIZE];
		sprintf(temp, "update ip_data set isStatus = %d, up_traffic_cur = %d, down_traffic_cur = %d where pid = %d", isOn, up_traffic_cur, down_traffic_cur, ip);
		if(brain_mysql_load(temp) != 0){
			printf(" return value : -2 |error in brain_update_db()\n");
			return -2;
		}
		mysql_close(connection);
	}
	else if(mode ==1){
		if(brain_mysql_init() != 0){
			printf(" return value : -1 |error in brain_update_db()\n");
			return -1;
		}
		char temp[BUFFER_SIZE];
		sprintf(temp, "update ip_data set isStatus = 0");
		if(brain_mysql_load(temp) != 0){
			printf(" return value : -2 |error in brain_update_db()\n");
			return -2;
		}
		mysql_close(connection);
	}
	else{
		printf("mode uselected\n");
		return 1;
	}
//	usleep(10);
	return 0;
} 
int write_logfile(char *buffer){

	time_t timer;
	struct tm *t;
	
	char date[9];
	int fileAccess;
	FILE *fp;
	
	timer = time(NULL);
	t = localtime(&timer);
	sprintf(date, "../../log/%d%d%d.log", t->tm_year+1900, t->tm_mon, t->tm_mday);
	fileAccess = access(date, R_OK|W_OK);

	if(fileAccess ==0){
		fp  = fopen(date, "a+");
	}
	else{
		fp = fopen(date, "w+");
	}
	
	if(fp == NULL){
		perror("fail to fopen");
		return -10;		
	}
	
	fseek(fp, 0, SEEK_END);
	
//	fwrite(buffer, 1, strlen(buffer), fp);
	fclose(fp);

	return 0;
}


void *timer_function(void *data){
	while(1){
		if(isTime == -1 || isTime == 2){
//			printf("\t\t\t\t\t\ttime strat\n");
			sleep(1);
//			usleep(10000);
//			printf("\t\t\t\t\t\ttime end\n");
			isTime = 2 ;
			isTimeOn ++;
		}	
    	}
}
void *check_Node(void *data){
//	int ip=0;
	sleep(11);
	isChecked=2;
	while(1){
//		if(isCheckNode == 1){
/*			for(ip=1; ip<255; ip++){
				printf("%d -> %d : %d\n", ip,user_info[ip].isStatus, isNodeLive[ip]);
				if(user_info[ip].isStatus != isNodeLive[ip]){
					printf("%d is off \n", ip);
					user_info[ip].isStatus = 0;
					brain_update_db(0,ip,0);				
				}
			}
			for(ip=0; ip<255; ip++){
				isNodeLive[ip] = 0;
			} 		*/
		if(isChecked == 2){
			sleep(3);
			isChecked=1;
		}
		
	}
}
