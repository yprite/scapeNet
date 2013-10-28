#include "senser_portscan.h"

long MAXSCANADDRESS =  512;


long    findcount   = 0;
double  totalnum    = 0;
long    scannum     = 0;

//int portscan(char* start_ip, char* end_ip, int t_port, int repley)
void *portscan(void *arg)
{
	unsigned int port;
    unsigned long i = 0;
    int max;
    int loop = 0;
    int ret = -1;
    unsigned long   start_addr, end_addr;
    time_t          scantime;
    unsigned long   cur_ip;
    unsigned long   value = 1;
    struct host hosts[MAXSCANADDRESS];
    struct host * p = NULL;
	long limit = 256;

	char *start_ip;
	char *end_ip;
	int t_port;
	int repley;
	portscan_grub_args *m_args = 0;
    
	p = hosts;

	m_args = (portscan_grub_args *)arg;
	start_ip = m_args->ip;
	end_ip = m_args->ip;
	t_port = m_args->t_port;
	repley = m_args->repley;

    if ( t_port < 0 || t_port > 65535) {
         fprintf(stdout, "Port must between 0-65535\n");
		 return 0;
    }

    start_addr = ntohl( inet_addr(start_ip) );
    end_addr = ntohl( inet_addr(end_ip) );

    if (start_addr > end_addr) {
        fprintf(stdout, "Check your ip range\n");
		return 0;
    }

    port = t_port;
    max = repley;

    scantime = time(NULL);
    cur_ip = start_addr;

	
	if(repley == 2){
		cur_ip = 1;
		end_addr = 65535;
		MAXSCANADDRESS = 1;
	}

    while( cur_ip <= end_addr ) {


//printf("%ld : %ld", cur_ip, end_addr);

        memset(hosts, -1, sizeof(hosts));

        for ( loop = 0; loop < max; loop++) {
            p = hosts;
            for ( i = cur_ip; i < cur_ip + MAXSCANADDRESS && i <= end_addr; i++, p++) {

                if ( ((i % 256)==0) || ((i % 256)==255) )
                    continue;

                if (p->sock == -1) {
                    p->sock = socket(AF_INET, SOCK_STREAM, 0);
                    if( p->sock == -1 ){
                        perror("socket error:");
                    }
                    // non-blocking mode is enabled
                    fcntl(p->sock, F_SETFL, O_RDONLY|O_NONBLOCK);
                }
				if(repley!=2){
                if ( (p->status != 0) && 
                     (p->status != 106) ) {
                    	p->status = scan(p->sock, i, port);
//						printf("scan(p->sock, %ld, %d)", i, port);
                    usleep(1000);
                }

				}else{
//					printf("scan(p->sock, %ld, %d)", start_addr, i);
					 p->status = scan(p->sock, start_addr, i);
					usleep(1000);
				}


            }
        }

        p = hosts;
        for ( i = cur_ip; i < cur_ip + MAXSCANADDRESS && i <= end_addr; i++, p++) {

           if ( ((i % 256)==0) || ((i % 256)==255) )
                continue;

            if ( (p->sock != -1) ) {
                close(p->sock);
           }
        }

        cur_ip = cur_ip + MAXSCANADDRESS;
    }

    fprintf(stdout, "\n\nScan End! Find PortCount:%ld",findcount); 
    fprintf(stdout, "\nTotal %ld s\n", (time(NULL)-scantime) );

    return 1;

}

int scan(int sock, unsigned long ip, int port ) {

    struct sockaddr_in  sin;
    int n;

    memset(&sin, 0, sizeof(sin) );

    sin.sin_family = PF_INET;
    sin.sin_addr.s_addr = htonl(ip);
    sin.sin_port = htons(port);

    if ( (n = connect(sock, (struct sockaddr*)&sin, sizeof(sin))) == -1 ) {
        if ( errno == EINPROGRESS )
            return EINPROGRESS;

        if ( errno == EALREADY )
            return EALREADY;

        if ( errno == EISCONN ){
            findcount += 1;
            fprintf(stdout, "%s -> %d\n", (char*)inet_ntoa(sin.sin_addr), \
                    ntohs(sin.sin_port) ); 
            return EISCONN;
        }
        //perror("socket error: ");
        return 0;
    }

    /* connect completed immediately */
    if ( n == 0 ) {
           findcount += 1;
           //fprintf(stdout,"connect completed immediately\n");
           fprintf(stdout, "%s -> %d\n", (char*)inet_ntoa(sin.sin_addr),
                   ntohs(sin.sin_port) ); 
           return 0;
    }

    return n;

}
