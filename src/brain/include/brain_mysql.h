#include "/usr/include/mysql/mysql.h"

#define EPOLL_SIZE 20
#define BUFFER_SIZE 255
#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "scapenet"
#define CHOP(x) x[strlen(x)-1]=''

MYSQL *connection = NULL, conn;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;
qurey_stat=0;







