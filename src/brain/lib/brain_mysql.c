#include "../include/brain_mysql.h"


int brain_mysql_init(){
   
    if(mysql_init(&conn) == 0){
         perror("mysql_init() error");
         return -1;
    }
    else{
        printf("DB(mysql) init Ok\n");
        if((connection =  mysql_real_connect(&conn,DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0)) == 0 ){
            perror("mysql_real_connect() error");
            exit(1);
        }
        else{
            printf("DB(mysql) connection OK\n");
        }       
    }
    return 0;
}

int brain_mysql_load(char *str){
    query_stat = mysql_query(connection, str);
    if(query_stat != 0){
        perror("mysql_query error");
        exit(1);
    }
    else return 0;
}
int brain_mysql_data_return(MYSQL *mysql){
    
    sql_result = mysql_store_result(connection);
    if(sql_result == NULL){
        perror("myql_store_result error");
        exit(1);
    }
    return 0;
}
int brain_mysql_data_print(){
    while((sql_row = mysql_fetch_row(sql_result))!=NULL){
        printf("|%+10s|%+20s|%+20s|%+10s|%+10s|%+10s|%+10s|%+10s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6], sql_row[7]);
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
    return 1;
}
void brain_mysql_data_free(){
    mysql_free_result(sql_result);
}

void *timer_function(void *data){
   while(1){ 
    printf("\t\t\t\t\ttime start\n");    
    isTime = -1;
    sleep(60);
    isTime = 1;
    printf("\t\t\t\t\ttime end\n");
    }
}
