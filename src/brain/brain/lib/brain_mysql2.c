#include "../include/brain_mysql.h"

void init_db(){
    int ip=0;
    char temp[BUFFER_SIZE];
    mysql_init(&conn);
    connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
    for(ip=1; ip<255; ip++){
         sprintf(temp, "update ip_data set isStatus = 0 ,up_traffic_cur =0, down_traffic_cur =0 where pid = %d", ip);
         query_stat = mysql_query(connection, temp);
    }
}
void load_db(){
    char temp[20];
    int ip=0;
    query_stat = mysql_query(connection, "select * from ip_data");
    sql_result = mysql_store_result(connection);
    while((sql_row = mysql_fetch_row(sql_result))!= NULL){
            ip=atoi(sql_row[0]);
            sprintf(user_info[ip].source_ip, "%s\n", sql_row[1]);
            sprintf(user_info[ip].mac, "%s\n", sql_row[2]);
            sprintf(user_info[ip].up_traffic_limit, "%s\n", sql_row[5]);
            sprintf(user_info[ip].down_traffic_limit, "%s\n", sql_row[6]);
    }   
    printf("DB Load Ok\r");
}

