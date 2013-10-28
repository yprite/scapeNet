#include <stdio.h>

#include "senser_networkScan.h"

#define BUFFER_SIZE 255

void receiver_epoll(network_grub_args *n_args);

int main(int argc, char *argv[])
{
	network_grub_args n_args;
	pthread_t t_id1;
	int state1 = 0;
	int i;
	
	printf("network Scaning\n");
	memset(&n_args, 0, sizeof(network_grub_args));
	n_args.g_ip = 1;
	
	state1 = pthread_create(&t_id1, NULL, networkScan, &n_args);
	if(state1 != 0) {
		fprintf(stderr, "pthread_create() error\n");
		return 0;
	}

	printf("count = %d\n", argc);

	if(argc > 1) {
		for(i=1; i<argc; i++) {
			int t_ip = atoi(argv[i]);
			printf("%d\n",t_ip);
			n_args.k_list.target_ip[t_ip] = 1;
		}
	}

	receiver_epoll(&n_args);

	return 0;
}

void receiver_epoll(network_grub_args *n_args)
{
	int pipeFd = 0;
	int readn = 0;
	char buffer[BUFFER_SIZE] = {0,};
	char *token_order, *token_ip;
	u_char ip[4] = {0,};
	int i = 0;

	if( (pipeFd = open(".write_sense", O_RDWR)) < 0) {
		perror("fail to call open()");
		exit(1);
	}

	// pipe 데이터 기다리는 부분
	while(1) {
		if ((readn = read(pipeFd, buffer, BUFFER_SIZE)) < 0) {
			perror("read error");
			exit(1);
		}
		else {
			int flag_order = 0;
			buffer[strlen(buffer)-1] = '\0';

			//head 분리
			token_order = strtok(buffer, " ");
			if(strcmp(token_order, "k") == 0) {
				puts("kill");
				flag_order = 1;
			} else if( strcmp(token_order, "p") == 0) {
				puts("pass");
				flag_order = 2;
			}

			token_order = strtok(NULL, " ");

			// IP 분리
			token_ip = strtok(token_order, ".");
			ip[0] = atoi(token_ip);
			for (i = 1; i <= 3; i++) {
				token_ip = strtok(NULL, ".");
				ip[i] = atoi(token_ip);
			}
			
			// kill & pass
			switch(flag_order) {
				case 1:
					printf("kill ip = %d\n",ip[3]);
					n_args->k_list.target_ip[ip[3]] = 1;
					break;
				case 2:
					printf("pass ip = %d\n",ip[3]);
					n_args->k_list.target_ip[ip[3]] = 0;
					break;
			}
		}
	}
	
	close(pipeFd);
}
