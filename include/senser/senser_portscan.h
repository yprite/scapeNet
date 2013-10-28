
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


struct host {
    int sock;
    int status;
};

void usage(char *);
int scan(int, unsigned long, int);
int init_socket();
int portscan(char*, char* ,int, int);

